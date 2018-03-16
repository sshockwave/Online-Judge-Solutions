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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=2010,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace gmath{
	int fac[N],invfac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		if(k>n)return 0;
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
}
int f[N];
inline int gf(int n,int k){
	if(n<=k)return f[n];
	lint ans=0;
	for(int j=0;j<=k;j++){
		using gmath::C;
		lint cur=(lint)C(n-j-1,k-j)%O*f[j]%O*C(n,j)%O;
		if((k-j)&1){
			ans-=cur;
		}else{
			ans+=cur;
		}
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("four.in","r",stdin);
	freopen("four.out","w",stdout);
#endif
	int n=ni,k=ni,q=ni;
	for(int i=0;i<=k;i++){
		f[i]=ni;
	}
	gmath::main(n);
	lint ans=0,pw=1;
	for(int i=0;i<=n;i++,pw=pw*q%O){
		ans+=pw*gf(i,k)%O;
	}
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
