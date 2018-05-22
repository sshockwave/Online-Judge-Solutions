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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=55,INF=0x7f7f7f7f;
namespace G{
	const int N=::N*::N*2,E=(N+N+N+N)*2;//cout
	int to[E],bro[E],cap[E],head[N],e=0,n=0,s,t;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		mset(dis+1,127,n);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t||a==0)return a;
		int r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		if(r){
			dis[x]=INF;
		}
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,INF));
		return flow;
	}
}
namespace mincut{
	lint pval[G::N],baseval=0;
	inline void init(){
		memset(pval,0,sizeof(pval));
	}
	inline int main(){
		using namespace G;
		for(int i=1;i<=n;i++){
			if(pval[i]>0){
				baseval+=pval[i];
				add(s,i,pval[i]);
			}else if(pval[i]<0){
				add(i,t,-pval[i]);
			}
		}
		return baseval-G::dinic();
	}
}
int n,m;
int mat[N][N],nd_ud[N][N],nd_lr[N][N];
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline void work_lr(int x,int y,int dy){
	using namespace mincut;
	for(int lastnd=nd_lr[x][y],lastv=0;y+=dy,y>=1&&y<=m;lastnd=nd_lr[x][y],lastv=mat[x][y]){
		assert(mat[x][y]>=0);
		const int cur=nd_lr[x][y];
		G::add(cur,lastnd,INF);
		G::add(cur,nd_ud[x][y],INF);
		pval[cur]=mat[x][y]-lastv;
	}
}
void work_ud(int x,int y,int dx){
	using namespace mincut;
	for(int nx,curv=0;;x=nx,curv=mat[x][y]){
		nx=x+dx;
		assert(mat[nx][y]>=0);
		if(nx>=1&&nx<=n){
			G::add(nd_ud[x][y],nd_ud[nx][y],INF);
			pval[nd_ud[nx][y]]=curv-mat[nx][y];
		}else{
			baseval+=curv;
			break;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cti.in","r",stdin);
	freopen("cti.out","w",stdout);
#endif
	n=ni,m=ni;
	G::init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mat[i][j]=ni;
			nd_ud[i][j]=G::nn();
			nd_lr[i][j]=G::nn();
		}
	}
	mincut::init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]<0){
				int c=-mat[i][j]-1;
				const static int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
				if(c>=2){
					work_lr(i,j,dy[c]);
				}else{
					work_ud(i,j,dx[c]);
				}
			}
		}
	}
	printf("%d\n",mincut::main());
	return 0;
}
