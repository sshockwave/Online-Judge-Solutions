#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=1010,INF=0x7f7f7f7f;
int n,s,t;
namespace G2{
	const int E=499500<<1;
	int to[E],bro[E],cap[E],head[N],e=0;
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
	inline bool bfs(){
		memset(dis,127,sizeof(dis));
		dis[t]=0;
		int qh=0,qt=0;
		que[qt++]=t;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i^1]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1;
					que[qt++]=v;
				}
			}
		}
		return dis[s]<INF;
	}
	int cur[N];
	int aug(int x,int a){
		if(x==t){
			return a;
		}
		int d,r=a;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]-1){
				d=aug(v,min(cap[i],r));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0){
					break;
				}
			}
		}
		if(r){
			dis[x]=INF;
		}
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		while(bfs()){
			for(int i=1;i<=n;i++){
				cur[i]=head[i];
			}
			flow+=aug(s,INF);
		}
		return flow;
	}
}
namespace G1{
	const int E=499500<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int dis[N];
	struct state{
		int x,d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d>b.d;
		}
	};
	priority_queue<state>q;
	bool vis[N];
	inline void dijkstra(){
		memset(dis,127,sizeof(dis));
		memset(vis,0,sizeof(vis));
		dis[s]=0;
		q.push((state){s,0});
		while(!q.empty()){
			int x=q.top().x;
			q.pop();
			if(x==t){
				break;
			}
			if(vis[x]){
				continue;
			}
			vis[x]=true;
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>dis[x]+val[i]){
					assert(!vis[v]);
					dis[v]=dis[x]+val[i];
					q.push((state){v,dis[v]});
				}
			}
		}
	}
	int que[N];
	inline void dp(){
		memset(vis,0,sizeof(vis));
		int qh=0,qt=0;
		que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]==dis[x]+val[i]){
					G2::add(x,v,1);
					if(!vis[v]){
						vis[v]=true;
						que[qt++]=v;
					}
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("greendam.in","r",stdin);
	freopen("greendam.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	s=ni,t=ni;
	G1::init(),G2::init();
	while(tot--){
		int u=ni,v=ni;
		G1::add(u,v,ni);
	}
	G1::dijkstra(),G1::dp();
	printf("%d\n",G2::dinic());
	return 0;
}
