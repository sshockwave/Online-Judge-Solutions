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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
int O;
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
int overall;
namespace sieve{
	const int N=1000010;
	int n;
	int pri[N],ps=0;
	bool np[N];
	int *mu;
	inline void main(int _n){
		n=min(N-1,_n);
		memset(np,0,sizeof(np));
		mu[0]=0,mu[1]=1;
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
			mu[i]+=mu[i-1];
		}
	}
}
struct DuSieve{
	int a[sieve::N],b[sieve::N];
	bool vis[sieve::N];
	DuSieve(){
		memset(vis,0,sizeof(vis));
	}
	inline virtual int _dirchlet(int n){return -1;}
	inline virtual int _g(int n){return -1;}
	inline int operator [] (int n){
		if(n<=sieve::n)return a[n];
		int dv=overall/n;
		int &ans=b[dv];
		if(vis[dv])return ans;
		vis[dv]=true;
		ans=_dirchlet(n);
		int cur,last=_g(1);
		for(int l=2,r,t;l<=n;l=r+1,last=cur){
			r=n/(t=n/l);
			cur=_g(r);
			ans=(ans-(lint)(cur-last)*operator[](t))%O;
		}
		return ans;
	}
};
struct MuSieve:DuSieve{
	inline virtual int _dirchlet(int n){
		return 1;
	}
	inline virtual int _g(int n){
		return n;
	}
}_mu;
inline int _n(int n){
	return (((lint)n*(n+1))>>1)%O;
}
struct calcClass{
	int a[sieve::N],b[sieve::N];
	bool vis[sieve::N];
	inline void init(){
		using sieve::n;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++){
			int m=sieve::mu[i]-sieve::mu[i-1];
			for(int j=m,t=i;t<=n;j+=m,t+=i){
				a[t]=(a[t]+j)%O;
			}
			a[i]=(a[i]+a[i-1])%O;
		}
	}
	inline int operator () (int n){
		if(n<=sieve::n)return a[n];
		int dv=overall/n,&ans=b[dv];
		if(vis[dv])return ans;
		vis[dv]=true;
		int cur,last=0;
		for(int l=1,r,t;l<=n;l=r+1,last=cur){
			r=n/(t=n/l);
			cur=_mu[r];
			ans=(ans+(lint)(cur-last)*_n(t))%O;
		}
		return ans;
	}
}calc;
inline int solve(int n){//okay
	lint ans=0;
	int cur,last=0;
	for(int l=1,r,t;l<=n;l=r+1,last=cur){
		r=n/(t=n/l);
		cur=calc(r);
		ans+=(lint)(cur-last)*t%O*t%O*t%O;
	}
	return ans;
}
inline int solve2(int n){//okay
	lint ans=0;
	int cur,last=0;
	for(int l=1,r,t;l<=n;l=r+1,last=cur){
		r=n/(t=n/l);
		cur=calc(r);
		ans+=(lint)(cur-last)*t%O*t%O;
	}
	return (ans-_n(n))>>1;
}
inline int solve4(int n){//okay
	return _n(n);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	int n=ni;
	O=ni;
	overall=n;
	sieve::mu=_mu.a,sieve::main(n);
	calc.init();
	lint ans=solve2(n);
	ans+=(solve(n)+2ll*solve4(n))*inv(3)%O;
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
