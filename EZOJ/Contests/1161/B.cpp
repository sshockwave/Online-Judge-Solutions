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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=55,V=50010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
int lval[N],rval[N];
bool np[V];
int mu[V],prime[V],ps=0;
inline void sieve(){
	memset(np,0,sizeof(np));
	mu[1]=1;
	for(int i=2;i<V;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
		}
		for(int j=0,cur=2;j<ps&&i*cur<V;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=-mu[i];
			}
		}
	}
}
inline int lownum(int x,int p){
	int a=x/p,b=a*p;
	return b>=x?b:b+p;
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	inline void join_ans(int f[],int nf[],int g[],int fl,int fr,int nfl,int nfr){
		memset(g+fl,0,(fr-fl+1)<<2);
		for(int i=1;i<=nfr;i++){
			if(mu[i]){
				int sum=0;
				for(int j=lownum(nfl,i);j<=nfr;j+=i){
					apadd(sum,nf[j]);
				}
				if(sum){
					if(mu[i]<0){
						sum=MOD-sum;
					}
					for(int j=lownum(fl,i);j<=fr;j+=i){
						apadd(g[j],sum);
					}
				}
			}
		}
		for(int i=fl;i<=fr;i++){
			apmul(f[i],g[i]);
		}
	}
	int f[N][V],g[N][V];
	void dfs1(int x,int fa){
		for(int i=lval[x];i<=rval[x];i++){
			f[x][i]=1;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs1(v,x);
			}
		}
		if(fa){
			join_ans(f[fa],f[x],g[x],lval[fa],rval[fa],lval[x],rval[x]);
		}
	}
	int tmp[V];
	void dfs2(int x,int fa){
		if(fa){
			for(int i=lval[fa];i<=rval[fa];i++){
				g[x][i]=mul(f[fa][i],inv(g[x][i]));
			}
			join_ans(f[x],g[x],tmp,lval[x],rval[x],lval[fa],rval[fa]);
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs2(v,x);
			}
		}
	}
}
inline void Main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		lval[i]=ni;
	}
	for(int i=1;i<=n;i++){
		rval[i]=ni;
	}
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1,0),T::dfs2(1,0);
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=lval[i];j<=rval[i];j++){
			apadd(sum,mul(j,T::f[i][j]));
		}
		printf("%d ",sum);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("net.in","r",stdin);
	freopen("net.out","w",stdout);
#endif
	sieve();
	for(int tot=ni;tot--;Main());
	return 0;
}
