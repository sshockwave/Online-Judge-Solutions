#include <iostream>
#include <cstdio>
#include <cstring>
//#include <cassert>
#include <cctype>
#define assert
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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=55,INF=0x7f7f7f7f;
namespace G{
	const int N=6010,E=N*10;//tochange
	int to[E],bro[E],cap[E],head[N],etop=0,ntop=0;
	int s,t;
	inline void init(){
		memset(head,-1,sizeof(head));
		s=++ntop,t=++ntop;
	}
	inline void add_edge(int u,int v,int c){
		to[etop]=v;
		bro[etop]=head[u];
		cap[etop]=c;
		head[u]=etop++;
	}
	inline void add(int u,int v,int c){
		add_edge(u,v,c);
		add_edge(v,u,0);
	}
	inline void add(int u,int v){
		add(u,v,INF);
	}
	int sum=0;
	inline int nn(int val){
		ntop++;
		if(val>0){
			sum+=val;
			add(s,ntop,val);
		}else if(val<0){
			add(ntop,t,-val);
		}
		return ntop;
	}
	int dis[N],que[N];
	inline void bfs(){
		int qhead=0,qtail=0;
		memset(dis,127,sizeof(dis));
		dis[s]=0;
		que[qtail++]=s;
		while(qhead<qtail){
			int x=que[qhead++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1;
					que[qtail++]=v;
				}
			}
		}
	}
	int aug(int x,int alloc){
		if(x==t){
			return alloc;
		}
		int rest=alloc,delta;
		for(int i=head[x],v;(~i)&&rest;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				if(delta=aug(v,min(rest,cap[i]))){
					cap[i]-=delta,cap[i^1]+=delta;
					rest-=delta;
				}
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
	inline int work(){
		return sum-dinic();
	}
}
int n,m;
int mat[N][N];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline int todi(int x){
	return -x-1;
}
int node[N][N];
int main(){
	n=ni,m=ni;
	G::init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mat[i][j]=ni;
		}
	}
	memset(node,0,sizeof(node));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int d=todi(mat[i][j]);
			if(d==0||d==1){
				assert(dy[d]==0);
				d=dx[d];
				node[i][j]=G::nn(0);
				int last=node[i][j],lval=0;
				for(int x=i,y=j;x+=d,valid(x,y);){
					assert(mat[x][y]>=0);
					assert(node[x][y]==0);
					G::add(node[x][y]=G::nn(mat[x][y]-lval),last);
					last=node[x][y];
					lval=mat[x][y];
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int d=todi(mat[i][j]);
			if(d==2||d==3){
				assert(dx[d]==0);
				d=dy[d];
				assert(node[i][j]==0);
				int last=G::nn(0),lval=0;
				for(int x=i,y=j;y+=d,valid(x,y);){
					assert(mat[x][y]>=0);
					int cur=G::nn(lval-mat[x][y]);
					G::add(last,cur);
					lval=mat[x][y];
					last=cur;
					if(node[x][y]){
						G::add(node[x][y],cur);
					}
				}
				G::add(last,G::nn(lval));
			}
		}
	}
	printf("%d\n",G::work());
}
