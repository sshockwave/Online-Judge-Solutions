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
	static const int D=N*2,E=D*3;
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
	int que[D],dis[D];
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
bool invalid[2][N],forbid[N];
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
	memset(forbid,0,sizeof(forbid));
	for(int i=0;i<k;i++){
		int cur=ni;
		forbid[cur]=true;
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
	if(ans==0){
		puts("-1");
		return 0;
	}
	printf("%d\n",n-k-ans);
	for(int i=1;i<=n;i++){
		if(!forbid[i]&&(node[0][i%p1]==0||G.dis[node[0][i%p1]]==INF)&&(node[1][i%p2]==0||G.dis[node[1][i%p2]]<INF)){
			printf("%d ",i);
		}
	}
}
