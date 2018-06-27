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
const int N=100010,M=710,INF=0x7f7f7f7f;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],dfe[N],tim=0;
	inline void init(int n){
		mset(head+1,-1,n);
		fa[1]=0,son[0]=0,size[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		dep[x]=dep[fa[x]]+1;
		son[x]=0;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x])continue;
			fa[v]=x;
			dfs1(v);
			size[x]+=size[v];
			if(size[v]>size[son[x]]){
				son[x]=v;
			}
		}
	}
	void dfs2(int x){
		dfn[x]=++tim;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]){
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])==fa[x]||v==son[x])continue;
				dfs2(v);
			}
		}
		dfe[x]=tim;
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline bool is_up(int a,int b){
		return dfn[b]<=dfn[a]&&dfn[a]<=dfe[b];
	}
	inline bool is_up(int a,int b,int c){
		return is_up(a,b)&&is_up(b,c);
	}
	inline bool ints(int a,int b,int c,int d){
		const int u=lca(a,b),v=lca(c,d);
		int w;
		if(w=lca(a,c),is_up(a,w,u)&&is_up(c,w,v))return true;
		if(w=lca(a,d),is_up(a,w,u)&&is_up(d,w,v))return true;
		if(w=lca(b,c),is_up(b,w,u)&&is_up(c,w,v))return true;
		if(w=lca(b,d),is_up(b,w,u)&&is_up(d,w,v))return true;
		return false;
	}
}
namespace G{
	const int N=::M*2,E=(::M*::M+::M*2)*2;
	int to[E],bro[E],cap[E],head[N],e=0,n=0,s,t;
	inline int nn(){
		return ++n,head[n]=-1,n;
	}
	inline void init(){
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		mset(dis+1,127,n);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		for(;qh<qt;){
			const int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t||a==0)return a;
		int r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		if(r){
			dis[x]=INF;
		}
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,INF));
		return flow;
	}
}
struct Route{
	int u,v;
}lin1[M],lin2[M];
int nd1[M],nd2[M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("twocomp.in","r",stdin);
	freopen("twocomp.out","w",stdout);
#endif
	const int n=ni,m1=ni,m2=ni;
	T::init(n),G::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	int sum=0;
	for(int i=1;i<=m1;i++){
		nd1[i]=G::nn();
		lin1[i]=(Route){ni,ni};
		const int v=ni;
		sum+=v;
		G::add(G::s,nd1[i],v);
	}
	for(int i=1;i<=m2;i++){
		nd2[i]=G::nn();
		lin2[i]=(Route){ni,ni};
		const int v=ni;
		sum+=v;
		G::add(nd2[i],G::t,v);
	}
	for(int i=1;i<=m1;i++){
		for(int j=1;j<=m2;j++){
			if(T::ints(lin1[i].u,lin1[i].v,lin2[j].u,lin2[j].v)){
				G::add(nd1[i],nd2[j],INF);
			}
		}
	}
	printf("%d\n",sum-G::dinic());
	return 0;
}
