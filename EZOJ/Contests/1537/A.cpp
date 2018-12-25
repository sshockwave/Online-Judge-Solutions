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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=55,V=1e6+10,O=1e9+7;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
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
namespace powsum{
	const int N=::N;
	int n;
	int x[N],y[N];
	int poly[N];
	int f[N];
	inline void lagrange(int n){
		mset(poly,0,n+1);
		poly[0]=1;
		for(int i=0;i<=n;i++){
			for(int j=i+1;j>=0;j--){
				lint cur=(lint)poly[j]*(O-x[i]);
				if(j){
					cur+=poly[j-1];
				}
				poly[j]=cur%O;
			}
		}
		for(int i=0;i<=n;i++){
			int k=1;
			for(int j=0;j<=n;j++){
				if(i!=j){
					k=(lint)k*(x[i]+O-x[j])%O;
				}
			}
			k=(lint)inv_pow(k)*y[i]%O;
			assert(poly[n+1]==1);
			int r=1;
			for(int j=n;j>=0;j--){
				apadd(f[j],(lint)r*k);
				r=(poly[j]+(lint)r*x[i])%O;
			}
		}
	}
	inline int ask(int x){
		int ans=0;
		for(int i=n+1;i>=0;i--){
			ans=((lint)ans*x+f[i])%O;
		}
		return ans;
	}
	inline void main(int _n){
		n=_n;
		x[0]=0,y[0]=0;
		for(int i=1;i<=n+1;i++){
			x[i]=i,y[i]=(y[i-1]+fpow(i,n))%O;
		}
		lagrange(n+1);
		for(int i=0;i<=n+1;i++){
			assert(ask(i)==y[i]);
		}
	}
}
struct DuSieve{
	const static int N=V;
	virtual int _g(int n)=0;
	virtual int _prod(int n)=0;
	int a[N],b[N],overall,precalc;
	DuSieve(){
		memset(b,-1,sizeof(b));
	}
	inline int sum(int n){
		if(n<=precalc)return a[n];
		const int idx=overall/n;
		if(b[idx]!=-1)return b[idx];
		int ans=0;
		int cur,last=_g(1);
		for(int l=2,r,d;l<=n;l=r+1){
			r=n/(d=n/l);
			cur=_g(r);
			ans=(ans+(lint)sum(d)*(cur+O-last))%O;
			last=cur;
		}
		return b[idx]=(_prod(n)+O-ans)%O;
	}
};
struct Mu:DuSieve{
	virtual int _g(int n){
		return n;
	}
	virtual int _prod(int){
		return 1;
	}
}mu;
namespace sieve{
	const int N=V;
	int pri[N],ps=0;
	bool np[N];
	inline void main(int n=N-1){
		mu.a[1]=1;
		mu.precalc=n;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				mu.a[i]=-1;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				if(i%p){
					mu.a[t]=-mu.a[i];
				}else{
					mu.a[t]=0;
					break;
				}
			}
			mu.a[i]=(mu.a[i-1]+mu.a[i]+O)%O;
		}
	}
}
int a[N],k=0;
int pri[30];
int dfs(int ps,int n){
	if(ps==0)return powsum::ask(n);
	return (dfs(ps-1,n)+O-dfs(ps-1,n/pri[ps]))%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int len=ni,n=ni;
	int g=0;
	for(int i=1;i<=len;i++){
		a[i]=ni;
		k+=a[i]==-1;
		if(a[i]!=-1){
			g=gcd(g,a[i]);
		}
	}
	powsum::main(k);
	int ans=0;
	if(g==0){
		sieve::main();
		mu.overall=n;
		int cur,last=0;
		for(int l=1,r,d;l<=n;l=r+1){
			r=n/(d=n/l);
			cur=mu.sum(r);
			ans=(ans+(lint)powsum::ask(d)*(cur+O-last))%O;
			last=cur;
		}
	}else{
		int ps=0;
		for(int i=2;i*i<=g;i++){
			if(g%i==0){
				pri[++ps]=i;
				for(;g%i==0;g/=i);
			}
		}
		if(g!=1){
			pri[++ps]=g;
		}
		ans=dfs(ps,n);
	}
	printf("%d\n",ans);
	return 0;
}
