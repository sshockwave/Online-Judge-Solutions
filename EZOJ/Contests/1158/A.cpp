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
const int N=260,INF=0x7f7f7f7f,WINF=1<<10;
namespace G{
	const int E=(N*2+8*(1<<(8-1)))<<1;
	int to[E],bro[E],cap[E],head[N],s,t;
	inline int nn(){
		static int n=0;
		return ++n;
	}
	inline void ae(int u,int v,int c){
		static int e=0;
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		s=nn(),t=nn();
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N];
	inline bool bfs(){
		memset(dis,-1,sizeof(dis));
		int qh=0,qt=dis[s]=0;
		que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==-1){
					dis[v]=dis[x]+1;
					if(v==t){
						return true;
					}
					que[qt++]=v;
				}
			}
		}
		return ~dis[t];
	}
	int aug(int x,int a){
		if(x==t){
			return a;
		}
		int d,r=a;
		for(int i=head[x],v;(~i)&&r;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		if(r){
			dis[x]=-1;
		}
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs();flow+=aug(s,INF));
		return flow;
	}
}
inline int lb(int x){
	return x&(-x);
}
inline int bitcnt(int x){
	int cnt=0;
	for(;x;x^=lb(x),cnt++);
	return cnt;
}
int node[N];
int wj[2][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ram.in","r",stdin);
	freopen("ram.out","w",stdout);
#endif
	int n=1<<ni,m=1<<ni;
	G::init();
	{//graph
		static int div[N],u[N];
		for(int i=0;i<n;i++){
			div[i]=ni;
		}
		for(int i=0;i<n;i++){
			u[i]=ni;
		}
		for(int i=0;i<n;i++){
			node[i]=G::nn();
		}
		for(int i=0;i<n;i++){
			int a=-WINF,b=-WINF;
			for(int j=0;j<div[i];j++){
				int t=ni;
				if(t>a){
					a=t,wj[0][i]=j;
				}
			}
			for(int j=div[i];j<m;j++){
				int t=ni;
				if(t>b){
					b=t,wj[1][i]=j;
				}
			}
			if(bitcnt(i)&1){
				G::add(G::s,node[i],WINF-b);
				G::add(node[i],G::t,WINF-a);
				for(int j=1;j<n;j<<=1){
					G::add(node[i],node[i^j],u[i]^u[i^j]);
				}
			}else{
				G::add(G::s,node[i],WINF-a);
				G::add(node[i],G::t,WINF-b);
			}
		}
	}
	{//flow
		G::dinic();
		for(int i=0;i<n;i++){
			printf("%d ",wj[(bitcnt(i)&1)==(G::dis[node[i]]==-1)][i]);
		}
		putchar('\n');
	}
	return 0;
}
