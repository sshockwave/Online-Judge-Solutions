#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <bitset>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=20010,INF=0x7f7f7f7f;
struct Graph{
	static const int N=N*2,E=N*3;
	int to[E],bro[E],cap[E],head[N*2],etop,s,t,n;
	Graph(){
		memset(head,-1,sizeof(head));
		n=etop=0;
		s=nn(),t=nn();
	}
	inline int nn(){
		return ++n;
	}
	inline void add_edge(int u,int v,int c){
		to[etop]=v;
		bro[etop]=head[u];
		cap[etop]=c;
		head[u]=etop++;
	}
	inline void add(int u,int v,int c){
		if(u&&v){
			add_edge(u,v,c);
			add_edge(v,u,0);
		}
	}
	int que[N],dis[N];
	inline bool bfs(){
		int qhead=0,qtail=0;
		memset(dis+1,INF,n<<2);
		dis[s]=0;
		que[qtail++]=s;
		while(qhead<qtail){
			int x=que[qhead++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1;
					if(v==t){
						return true;
					}
					que[qtail++]=v;
				}
			}
		}
		return false;
	}
	int aug(int x,int alloc){
		if(x==t){
			return alloc;
		}
		int rest=alloc,delta;
		for(int i=head[x],v;rest&&(~i);i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				delta=aug(v,min(rest,cap[i]));
				cap[i]-=delta,cap[i^1]+=delta;
				rest-=delta;
			}
		}
		if(rest==alloc){
			dis[x]=INF;
		}
		return alloc-rest;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs();flow+=aug(s,INF));
		return flow;
	}
}G;
int node[2][N];
bool invalid[2][N],okay[2][N];
int main(){
	int n=ni,k=ni;
	int prime[2],ptop=0,div=n;
	for(int i=2;i*i<=div;i++){
		if(div%i==0){
			prime[ptop++]=i;
			for(;div%i==0;div/=i);
		}
	}
	if(div>1){
		prime[ptop++]=div;
	}
	if(ptop<2){
		puts(k==0?"0":"-1");
		return 0;
	}
	assert(prime[0]<prime[1]);
	int p1=n/prime[0],p2=n/prime[1];
	memset(invalid,0,sizeof(invalid));
	for(int i=0;i<k;i++){
		int cur=ni;
		invalid[0][cur%p1]=true;
		invalid[1][cur%p2]=true;
	}
	int ans=0;
	memset(node,0,sizeof(node));
	for(int i=0;i<p1;i++){
		if(!invalid[0][i]){
			G.add(G.s,node[0][i]=G.nn(),prime[0]);
			ans+=prime[0];
		}
	}
	for(int i=0;i<p2;i++){
		if(!invalid[1][i]){
			G.add(node[1][i]=G.nn(),G.t,prime[1]);
			ans+=prime[1];
		}
	}
	for(int i=0;i<n;i++){
		G.add(node[0][i%p1],node[1][i%p2],INF);
	}
	ans-=G.dinic();
	printf("%d\n",ans);
	memset(okay,0,sizeof(okay));
	for(int j=0;j<p1;j++){
		if(!invalid[0][j]){
			for(int i=G.head[node[0][j]];~i;i=G.bro[i]){
				if(G.to[i]==G.s){
					okay[0][j]=G.cap[i]!=prime[0];
					break;
				}
			}
		}
	}
	for(int j=0;j<p2;j++){
		if(!invalid[1][j]){
			for(int i=G.head[node[1][j]];~i;i=G.bro[i]){
				if(G.to[i]==G.t){
					okay[1][j]=G.cap[i];
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(okay[0][i%p1]&&okay[1][i%p2]){
			printf("%d ",i);
		}
	}
}
