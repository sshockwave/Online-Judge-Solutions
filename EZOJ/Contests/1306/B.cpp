#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010,INF=0x7f7f7f7f;
namespace G{
	const int E=N*3;
	int to[E],bro[E],cap[E],head[N],e=0,s,t;
	inline void init(int n){
		memset(head,-1,sizeof(head));
		s=n+1,t=n+2;
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N];
	inline void bfs(){
		memset(dis,127,sizeof(dis));
		dis[s]=0;
		int qh=0,qt=0;
		que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1;
					que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int alloc){
		if(x==t){
			return alloc;
		}
		int rest=alloc,delta;
		for(int i=head[x],v;~i&&rest;i=bro[i]){
			v=to[i];
			if(cap[i]&&dis[v]==dis[x]+1){
				delta=aug(v,min(rest,cap[i]));
				cap[i]-=delta,cap[i^1]+=delta,rest-=delta;
			}
		}
		if(rest){
			dis[x]=INF;
		}
		return alloc-rest;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,INF));
		return flow;
	}
}
typedef map<int,int> mii;
mii mat[N];
int x[N],y[N],cost[N],nxt[N];
int main(){
	ni,ni;
	int n=ni,head=-1;
	G::init(n);
	for(int i=1;i<=n;i++){
		x[i]=ni,y[i]=ni;
		cost[i]=ni;
		mat[x[i]][y[i]]=i;
		if((x[i]&1)&&((x[i]>>1)&1)!=(y[i]&1)){
			nxt[i]=head;
			head=i;
		}else{
			G::add(i,G::t,cost[i]);
		}
	}
	for(int i=head;~i;i=nxt[i]){
		mii::iterator it;
		#define ifvis(x,y) if((it=mat[x].find(y))!=mat[x].end())
		ifvis(x[i]+1,y[i]){
			G::add(G::s,i,min(cost[i],cost[it->second]));
			#define go(x,y) ifvis(x,y)G::add(i,it->second,INF)
			go(x[i]-1,y[i]);
			go(x[i],y[i]-1);
			go(x[i],y[i]+1);
			go(x[i]+1,y[i]-1);
			go(x[i]+1,y[i]+1);
			go(x[i]+2,y[i]);
		}
	}
	printf("%d\n",G::dinic());
}