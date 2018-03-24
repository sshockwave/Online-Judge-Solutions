#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=10010,INF=0x7f7f7f7f;
int deg[N];
bool vis[N];
int ecnt;
bool hasin;
namespace G{
	const int E=(100010+N)<<1;
	int to[E],bro[E],val[E],cap[E],head[N],e=0,s,t,n;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w,int c){
		to[e]=v,bro[e]=head[u],val[e]=w,cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int w,int c){
		ae(u,v,w,c),ae(v,u,-w,0);
	}
	int dis[N],que[N];
	bool inque[N];
	inline void spfa(){
		memset(dis+1,127,n*sizeof(dis[0]));
		memset(inque+1,0,n*sizeof(inque[0]));
		int qh=0,qt=0;
		dis[s]=0;
		inque[s]=true,que[qt++]=s;
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i];
					if(!inque[v]){
						inque[v]=true,que[qt++]=v;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
			inque[x]=false;
		}
	}
	int tag[N],tim=0;
	inline int aug(int x,int a){
		if(x==t||a==0)return a;
		tag[x]=tim;
		int r=a,d;
		for(int i=head[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+val[i]&&tag[v]<tim){
				d=aug(v,min(cap[i],r));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	inline int mcmf(){
		int cost=0;
		for(;spfa(),dis[t]<0;tim++,cost+=dis[t]*aug(s,INF));
		return cost;
	}
	void dfs(int x){
		if(vis[x])return;
		vis[x]=true;
		hasin|=deg[x]!=0;
		for(int i=head[x];~i;i=bro[i]){
			ecnt++;
			dfs(to[i]);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("draw.in","r",stdin);
	freopen("draw.out","w",stdout);
#endif
	int n=ni,m=ni;
	G::init(),G::s=n+1,G::t=n+2,G::n=n+2;
	for(int i=1;i<=m;i++){
		int u=ni,v=ni;
		deg[u]++,deg[v]--;
		G::ae(u,v,0,0);
		G::ae(v,u,0,ni);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(deg[i]>0){
			G::add(i,G::t,-1,deg[i]>>1);
			if(deg[i]&1){
				G::add(i,G::t,0,1);
			}
			ans+=deg[i];
		}else if(deg[i]<0){
			G::add(G::s,i,-1,(-deg[i])>>1);
			if((-deg[i])&1){
				G::add(G::s,i,0,1);
			}
		}
	}
	ans+=G::mcmf();
	for(int i=G::head[G::s];~i;i=G::bro[i]){
		deg[G::to[i]]-=G::cap[i^1]*G::val[i]*2;
	}
	for(int i=G::head[G::t];~i;i=G::bro[i]){
		deg[G::to[i]]+=G::cap[i]*G::val[i^1]*2;
	}
	vis[G::s]=vis[G::t]=true;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		ecnt=0,hasin=false;
		G::dfs(i);
		ans+=ecnt&&!hasin;
	}
	printf("%d\n",ans);
	return 0;
}
