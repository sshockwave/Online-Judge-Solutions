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
const int N=2010,INF=0x7f7f7f7f;
int lnk[N];
bool vis[N];
namespace G{
	const int E=1010*1010*2;
	int to[E],bro[E],cap[E],head[N],e=0,s,t;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N];
	inline void bfs(){
		memset(dis+1,127,t<<2);
		int qh=0,qt=0;
		dis[t]=0,que[qt++]=t;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i^1]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1;
					que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t){
			return a;
		}
		int d,r=a;
		for(int i=head[x],v;r&&~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]-1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		if(r){
			dis[x]=INF;
		}
		return a-r;
	}
	inline void dinic(){
		int flow=0;
		for(;bfs(),dis[s]<INF;flow+=aug(s,INF));
	}
}
int que[N];
int tp[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cover.in","r",stdin);
	freopen("cover.out","w",stdout);
#endif
	int n=ni,m=ni;
	G::init();
	G::s=n+m+1,G::t=n+m+2;
	for(int i=1;i<=n;i++){
		G::add(G::s,i,1);
	}
	for(int i=n+1;i<G::s;i++){
		G::add(i,G::t,1);
	}
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G::add(u,v+n,1);
	}
	G::dinic();
	memset(lnk,0,sizeof(lnk));
	for(int x=1;x<=n;x++){
		for(int i=G::head[x];~i;i=G::bro[i]){
			if(G::to[i]!=G::s&&G::cap[i]==0){
				lnk[x]=G::to[i];
				lnk[G::to[i]]=x;
				break;
			}
		}
	}
	int qh=0,qt=0;
	memset(tp,0,sizeof(tp));
	for(int i=1;i<G::s;i++){
		if(lnk[i]==0){
			tp[i]=-1;
			que[qt++]=i;
		}
	}
	while(qh<qt){
		int x=que[qh++];
		if(tp[x]==1){
			if(tp[lnk[x]]==0){
				tp[lnk[x]]=-1;
				que[qt++]=lnk[x];
			}
		}else for(int i=G::head[x],v;~i;i=G::bro[i]){
			v=G::to[i];
			if(v!=G::s&&v!=G::t&&tp[v]==0){
				tp[v]=1;
				que[qt++]=v;
			}
		}
	}
	for(int i=1;i<G::s;i++){
		if(tp[i]==1){
			putchar('A');
		}else if(tp[i]==-1){
			putchar('N');
		}else{
			putchar('E');
		}
		if(i==n){
			putchar('\n');
		}
	}
	putchar('\n');
	return 0;
}
