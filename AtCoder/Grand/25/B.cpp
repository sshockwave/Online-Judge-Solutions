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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=300010,O=998244353;
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
namespace gmath{
	int fac[N],ifac[N];
	inline void main(int n){
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
int main(){
#ifndef ONLINE_JUDGE
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
#endif
	const int n=ni;
	gmath::main(n);
	const int a=ni,b=ni,g=gcd(a,b);
	const lint k=next_num<lint>();
	if(k%g){
		puts("0");
		return 0;
	}
	lint i=0;
	for(;(k-i*a)%b;i++);
	lint j=(k-i*a)/b;
	assert(j>=0);
	int ans=0;
	if(j>n){
		lint t=a/g;
		lint q=(j-n+t-1)/t;
		i+=b/g*q,j-=a/g*q;
	}
	for(;i<=n&&j>=0;i+=b/g,j-=a/g){
		ans=(ans+(lint)gmath::C(n,i)*gmath::C(n,j))%O;
	}
	printf("%d\n",ans);
	return 0;
}
