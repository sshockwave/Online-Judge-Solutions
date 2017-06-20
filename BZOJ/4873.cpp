#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=110,A=1010,INF=0x7f7f7f7f;
namespace G{
	const int N=7110,E=N*6;
	int n=0,e=0,s,t;
	inline int nn(){
		return ++n;
	}
	int to[E],bro[E],cap[E],head[N];
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c=INF){
		ae(u,v,c),ae(v,u,0);
	}
	int sum=0;
	inline void set(int x,int v){
		if(v>0){
			sum+=v;
			add(s,x,v);
		}else if(v<0){
			add(x,t,-v);
		}
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		s=nn(),t=nn();
	}
	int dis[N],que[N];
	inline void bfs(){
		memset(dis,127,sizeof(dis));
		int qh=0,qt=0;
		dis[s]=0;
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
		int rest=alloc,delta=0;
		for(int i=head[x],v;~i&&rest;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				delta=aug(v,min(cap[i],rest));
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
int node[N][N],nodea[N];
int main(){
	int n=ni;
	{//build graph
		G::init();
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				node[i][j]=G::nn();
			}
		}
		int m=ni;
		memset(nodea,0,sizeof(nodea));
		int a[N];
		for(int i=1;i<=n;i++){
			a[i]=ni;
			if(nodea[a[i]]==0){
				G::set(nodea[a[i]]=G::nn(),-m*a[i]*a[i]);
			}
			G::add(node[i][i],nodea[a[i]]);
		}
		for(int i=1;i<=n;i++){
			G::set(node[i][i],ni-a[i]);
			for(int j=i+1;j<=n;j++){
				G::set(node[i][j],ni);
				G::add(node[i][j],node[i+1][j]);
				G::add(node[i][j],node[i][j-1]);
			}
		}
	}
	printf("%d\n",G::sum-G::dinic());
}