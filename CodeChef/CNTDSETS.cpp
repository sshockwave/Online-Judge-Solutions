#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1010,O=1000000007;
inline int fpow(int x,int n,int O=::O){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
namespace gmath{
	int fac[N],ifac[N];
	inline void main(int n=N-1){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		return (lint)fac[n]*ifac[k]%O*ifac[n-k]%O;
	}
}
using gmath::C;
inline int calc(const int n,const int d){
	lint ans=0;
	for(int i=0;i<=n;i++){
		int cur=(lint)C(n,i)*fpow(2,(lint)fpow(d,i,O-1)*fpow(d-1,n-i,O-1)%(O-1))%O;
		if((n-i)&1){
			ans-=cur;
		}else{
			ans+=cur;
		}
	}
	return (ans%O+O)%O;
}
inline int Main(){
	const int n=ni,d=ni;
	return (calc(n,d+1)+O-calc(n,d))%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cntdsets.in","r",stdin);
	freopen("cntdsets.out","w",stdout);
#endif
	gmath::main();
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
