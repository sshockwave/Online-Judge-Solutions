#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=22,N2=N*N,INF=0x7f7f7f7f;
namespace G{
	const int N=::N2*4,E=(::N2*::N2*2+::N2+::N2*2)*2;
	int to[E],bro[E],cap[E],head[N],e,n=0,s,t;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head+1,-1,n*sizeof(head[0]));
		e=0;
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		memset(dis+1,127,n*sizeof(dis[0]));
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
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,INF));
		return flow;
	}
}
struct Pt{
	int x,y,t;
}boy[N2],girl[N2];
char mat[N][N];
int mpid[N][N],mpid2[N][N];
int bid[N2],gid[N2];
int n,m;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int quex[N2],quey[N2],dis[N][N],vis[N][N],tim=0;
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m&&mat[x][y]=='.'&&vis[x][y]<tim;
}
inline void bfs(int x,int y,int nd,lint v,int flag){
	int qh=0,qt=0;
	quex[qt]=x,quey[qt]=y,dis[x][y]=0,vis[x][y]=++tim,qt++;
	while(qh<qt){
		x=quex[qh],y=quey[qh],qh++;
		if(dis[x][y]>v)break;
		if(flag==1){
			G::add(nd,mpid[x][y],1);
		}else{
			G::add(mpid2[x][y],nd,1);
		}
		for(int d=0;d<4;d++){
			int tx=x+dx[d],ty=y+dy[d];
			if(valid(tx,ty)){
				quex[qt]=tx,quey[qt]=ty,dis[tx][ty]=dis[x][y]+1,vis[tx][ty]=tim,qt++;
			}
		}
	}
}
inline bool check(int k,lint v){
	G::init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='.'){
				G::add(mpid[i][j],mpid2[i][j],1);
			}
		}
	}
	for(int i=1;i<=k;i++){
		G::add(G::s,bid[i],1),bfs(boy[i].x,boy[i].y,bid[i],v/boy[i].t,1);
		G::add(gid[i],G::t,1),bfs(girl[i].x,girl[i].y,gid[i],v/girl[i].t,2);
	}
	return G::dinic()==k;
}
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dance.in","r",stdin);
	freopen("dance.out","w",stdout);
#endif
	n=ni,m=ni;
	int k=ni;
	G::s=G::nn(),G::t=G::nn();
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='.'){
				mpid[i][j]=G::nn();
				mpid2[i][j]=G::nn();
			}
		}
	}
	int mxt=0;
	for(int i=1;i<=k;i++){
		boy[i]=(Pt){ni,ni,ni};
		if(mat[boy[i].x][boy[i].y]=='#'){
			puts("-1");
			return 0;
		}
		apmax(mxt,boy[i].t);
		bid[i]=G::nn();
	}
	for(int i=1;i<=k;i++){
		girl[i]=(Pt){ni,ni,ni};
		if(mat[girl[i].x][girl[i].y]=='#'){
			puts("-1");
			return 0;
		}
		apmax(mxt,girl[i].t);
		gid[i]=G::nn();
	}
	lint l=0,r=(lint)mxt*n*m+1;
	while(l<r){
		lint mi=(l+r)>>1;
		if(check(k,mi)){
			r=mi;
		}else{
			l=mi+1;
		}
	}
	printf("%lld\n",l>(lint)mxt*n*m?-1:l);
	return 0;
}
