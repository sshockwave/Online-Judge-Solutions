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
const int N=100010,O=998244353;
namespace arr{
	int pool[N<<2],*pt=pool;
	inline void init(){
		memset(pool,0,sizeof(pool));
	}
	inline int* New(int n){
		return (pt+=n)-n;
	}
}
int pval[N];
lint ans=0;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dep[N]={-1},son[N];
	void dfs1(int x,int fa){
		dep[x]=son[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs1(v,x);
				apmax(dep[x],dep[v]+1);
				if(dep[v]>dep[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	int sum[N],cnt[N],tim=0;
	void dfs2(int x,int fa,int f[],int g[]){
		int dfn=++tim;
		int *sum=T::sum+dfn,*cnt=T::cnt+dfn;
		sum[0]=pval[x],cnt[0]=1;
		if(son[x]==0)return;
		sum[0]=cnt[0]=0;
		dfs2(son[x],x,f,g);
		f+=dep[x],g+=dep[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa||v==son[x])continue;
			int *nf=arr::New((dep[v]+1)<<1),*ng=arr::New((dep[v]+1)<<1);
			int *nsum=T::sum+tim,*ncnt=T::cnt+tim;
			dfs2(v,x,nf,ng);
			nf+=dep[v],ng+=dep[v];
			//Combine info
			for(int d=1;d<=dep[v]+1;d++){
				ans+=(lint)nf[d]*sum[d-1]%O;
				ans+=(lint)ng[d]*cnt[d-1]%O;
				ans+=(lint)f[d]*nsum[d]%O;
				ans+=(lint)g[d]*ncnt[d]%O;
			}
			for(int d=0;d<=dep[v]+1;d++){
				f[d]=(f[d]+nf[d+1]+(lint)sum[d]*ncnt[d]%O+(lint)nsum[d]*cnt[d]%O)%O;
				g[d]=(g[d]+ng[d+1]+(lint)sum[d]*nsum[d])%O;
				if(d){
					sum[d]=(sum[d]+nsum[d])%O;
					cnt[d]=(cnt[d]+ncnt[d])%O;
				}
			}
		}
		ans+=(lint)f[0]*pval[x]%O+g[0];
		sum[0]=pval[x],cnt[0]=1;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=(ni,ni);
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	arr::init();
	T::dfs1(1,0);
	int *f=arr::New(T::dep[1]<<1);
	int *g=arr::New(T::dep[1]<<1);
	T::dfs2(1,0,f,g);
	printf("%lld\n",ans%O);
	return 0;
}
