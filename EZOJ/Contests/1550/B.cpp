#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=12000000,M=25,O=998244353;
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
int f[N];
inline void getf(const int n){
	gmath::main(n);
	for(int i=0;i<=n;i++){
		f[i]=(i&1)==(n&1)?gmath::C(n,(n-i)>>1):0;
	}
	for(int i=n-1;i>=0;i--){
		f[i]=(f[i]+f[i+1])%O;
	}
	const int r=O-inv_pow(fpow(2,n));
	for(int i=0;i<n;i++){
		f[i]=1+(lint)(f[i]+f[i+1])*r%O;
	}
	f[n]=1+(lint)f[n]*r%O;
}
int n,m;
lint pos[M];
inline int calc(const lint x){
	int a=1;
	for(int i=1;i<=m;i++){
		lint t=cabs(pos[i]-x);
		if(t<=n){
			a=(lint)a*f[t]%O;
		}
	}
	return 1-a;
}
struct Intv{
	lint l,r;
}lst[M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("exodus.in","r",stdin);
	freopen("exodus.out","w",stdout);
#endif
	n=ni,m=ni;
	getf(n);
	for(int i=1;i<=m;i++){
		pos[i]=next_num<lint>();
	}
	sort(pos+1,pos+m+1);
	int ls=0;
	for(int i=1;i<=m;i++){
		if(ls&&lst[ls].r>=pos[i]-n){
			lst[ls].r=pos[i]+n;
		}else{
			lst[++ls]=(Intv){pos[i]-n,pos[i]+n};
		}
	}
	lint ans=0;
	for(int i=1;i<=ls;i++){
		for(lint j=lst[i].l;j<=lst[i].r;j++){
			ans+=calc(j);
		}
	}
	ans=(ans%O+O)%O;
	printf("%lld\n",ans);
	return 0;
}
