#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <cmath>
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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
inline lint lcm(const int &a,const int &b){return (lint)a/gcd(a,b)*b;}
const int N=1000010,logN=40,O=998244353;
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
	inline void init(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
}
int D;
namespace sieve{
	int pri[N],ps=0;
	bool np[N];
	int mu[N];
	inline void init(int n){
		memset(np,0,sizeof(np));
		mu[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				mu[i]=-1;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				if(i%p){
					mu[t]=-mu[i];
				}else{
					mu[t]=0;
					break;
				}
			}
		}
	}
	int pw[N];
	inline void gpow(int n,int e){
		pw[0]=0,pw[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pw[i]=fpow(i,e);
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				pw[t]=(lint)pw[i]*pw[p]%O;
				if(i%p==0)break;
			}
		}
	}
}
inline int newton(int f[],int n,int d){
	static int pre[N],nxt[N];
	pre[0]=1;
	for(int i=1;i<=d;i++){
		pre[i]=(lint)pre[i-1]*(n-i+1)%O;
	}
	nxt[d]=1;
	for(int i=d-1;i>=0;i--){
		nxt[i]=(lint)nxt[i+1]*(n-i-1)%O;
	}
	lint ans=0;
	for(int j=0;j<=d;j++){
		using gmath::invfac;
		int cur=(lint)f[j]*pre[j]%O*nxt[j]%O*invfac[j]%O*invfac[d-j]%O;
		if((d-j)&1){
			ans-=cur;
		}else{
			ans+=cur;
		}
	}
	return (ans%O+O)%O;
}
inline int powsum(int l,int r,int e){
	assert(l<=r);
	if(e==0)return r-l+1;
	if(e==1)return (((lint)r*(r+1)-(lint)l*(l-1))>>1)%O;
	if(r<=e*2){
		sieve::gpow(r,e);
		lint ans=0;
		for(int i=l;i<=r;i++){
			ans+=sieve::pw[i];
		}
		return ans%O;
	}
	static int f[N];
	sieve::gpow(e+1,e);
	f[0]=0;
	for(int i=1;i<=e+1;i++){
		f[i]=(f[i-1]+sieve::pw[i])%O;
	}
	return (newton(f,r,e+1)+O-newton(f,l-1,e+1))%O;
}
int f[logN],g[logN];
inline int rt_flr(int n,int e){
	int a=pow(n,1.0/e);
	for(;pow(a,e)<n;a++);
	for(;pow(a,e)>n;a--);
	return a;
}
inline int rt_cel(int n,int e){
	int a=pow(n,1.0/e);
	for(;pow(a,e)>n;a--);
	for(;pow(a,e)<n;a++);
	return a;
}
inline int Main(int n){
	if(n<2)return 0;
	using sieve::mu;
	int mxt=0;
	for(;(1<<(mxt+1))<=n;mxt++);//t=mxt*D
	int mxtd=mxt*D;
	{//get f
		memset(f+1,0,mxt*sizeof(f[0]));
		for(int k=1;k<=mxtd;k++){
			for(int b=1,kb;(kb=k*b)<=mxtd;b++){
				int dt=lcm(kb,D)/D;
				int rt=rt_flr(n,kb);
				for(int t=dt;t<=mxt;t+=dt){
					f[t]=(f[t]+mu[b]*powsum(rt_cel(1<<t,kb),rt,(lint)b*t*D/k%(O-1)))%O;
				}
			}
		}
	}
	{//get g
		memset(g+1,0,mxt*sizeof(g[0]));
		for(int e=1;e<=mxt;e++){//e=e*D
			int fp=mu[e]*fpow(e,D);
			for(int c=1,t;(t=c*e)<=mxt;c++){
				g[t]=(g[t]+mu[c]*fp)%O;
			}
		}
	}
	lint ans=0;
	for(int i=1;i<=mxt;i++){
		ans+=(lint)f[i]*g[i]%O;
	}
	return (ans%O+O)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("rad.in","r",stdin);
	freopen("rad.out","w",stdout);
#endif
	sieve::init(N-1);
	gmath::init(N-1);
	ni,D=ni;
	int l=ni,r=ni;
	printf("%d\n",(Main(r)+O-Main(l-1))%O);
	return 0;
}
