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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,O=1e9+7;
namespace gmath{
	const int N=::N<<1;
	int fac[N],ifac[N];
	inline int fpow(int x,int n){
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
		assert(k<=n);
		if(k<0)return 0;
		return (lint)fac[n]*ifac[k]%O*ifac[n-k]%O;
	}
}
using gmath::C;
inline int calc(int r,int t){
	return C(r+t+1,r);
}
inline int Main(int l,int r,int k){
	int ans=calc(k+r-l,l-k);
	if(k){
		ans=(ans+O-calc(k-1,l-k))%O;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("m.in","r",stdin);
	freopen("m.out","w",stdout);
#endif
	gmath::main();
	ni;
	int ans=1;
	for(int tot=ni;tot--;){
		int l=ni,r=ni,k=ni;
		ans=(lint)ans*Main(l,r,k)%O;
	}
	printf("%d\n",ans);
	return 0;
}
