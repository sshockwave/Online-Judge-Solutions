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
const int N=2010,INF=0x7f7f7f7f;
namespace G{
	const int N=2010*2,E=N<<3;
	int to[E],bro[E],cap[E],val[E],head[N],e=0,n=0,s,t;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c,int w){
		to[e]=v,bro[e]=head[u],cap[e]=c,val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int c,int w){
		if(u==0||v==0)return;
		ae(u,v,c,w),ae(v,u,0,-w);
	}
	int dis[N],pre[N],que[N];
	bool inque[N];
	inline void spfa(){
		memset(dis+1,127,n<<2);
		memset(inque+1,0,n);
		int qh=0,qt=0;
		dis[que[qt++]=s]=0,pre[s]=-1;
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			inque[x]=false;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i],pre[v]=i;
					if(!inque[v]){
						inque[v]=true;
						que[qt++]=v;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
		}
	}
	int flow=0,cost=0;
	inline void mcmf(){
		while(spfa(),dis[t]<INF){
			int dt=INF;
			for(int i=pre[t];~i;i=pre[to[i^1]]){
				apmin(dt,cap[i]);
			}
			for(int i=pre[t];~i;i=pre[to[i^1]]){
				cap[i]-=dt,cap[i^1]+=dt;
			}
			flow+=dt,cost+=dis[t]*dt;
		}
	}
}
inline int rot(int x){
	return (x>>1)|((x&1)<<3);
}
int a[N][N],node[N][N][4],cost[N][N][4];
int bitcnt[1<<4];
inline void putedge(int i,int j,int x,int c,int w){
	using namespace G;
	if((i+j)&1){
		add(x,t,c,w);
	}else{
		add(s,x,c,w);
	}
}
inline int Main(){
	int n=ni,m=ni;
	memset(node,0,sizeof(node));
	memset(cost,127,sizeof(cost));
	G::init();
	bitcnt[0]=0;
	for(int i=1;i<16;i++){
		bitcnt[i]=bitcnt[i^(i&-i)]+1;
	}
	int sum[2]={0,0};
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int cur=ni;
			if(cur){
				int * const C=cost[i][j];
				int * const N=node[i][j];
				sum[(i+j)&1]+=bitcnt[cur];
				bool flag=bitcnt[cur]==2&&rot(rot(cur))!=cur;
				if(flag){
					putedge(i,j,N[0]=N[2]=G::nn(),1,0);
					putedge(i,j,N[1]=N[3]=G::nn(),1,0);
				}else{
					putedge(i,j,N[0]=N[1]=N[2]=N[3]=G::nn(),bitcnt[cur],0);
				}
				if(rot(rot(cur))==cur){
					for(int d=0;d<4;d++){
						C[d]=(cur>>d)&1?0:INF;
					}
				}else if(bitcnt[cur]==1){
					int d=0;
					for(;((cur>>d)&1)==0;d++);
					C[d]=0,C[(d+1)&3]=3,C[(d+2)&3]=6,C[(d+3)&3]=3;
				}else if(bitcnt[cur]==3){
					int d=0;
					for(;(cur>>d)&1;d++);
					C[d]=4,C[(d+1)&3]=1,C[(d+2)&3]=-2,C[(d+3)&3]=1;
				}else for(int d=0;d<4;d++){
					C[d]=(cur>>d)&1?0:3;
				}
			}
		}
	}
	if(sum[0]!=sum[1])return -1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)&1)continue;
			for(int d=0;d<4;d++){
				const static int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
				int x=i+dx[d],y=j+dy[d];
				if(cost[i][j][d]<INF&&cost[x][y][(d+2)&3]<INF){
					G::add(node[i][j][d],node[x][y][(d+2)&3],1,cost[i][j][d]+cost[x][y][(d+2)&3]);
				}
			}
		}
	}
	G::mcmf();
	if(G::flow!=sum[0])return -1;
	return G::cost/3;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ring.in","r",stdin);
	freopen("ring.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
