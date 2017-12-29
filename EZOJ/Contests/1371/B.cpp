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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=410;
namespace G{
	const int N=410*410*4,E=N<<2;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		if(u&&v){
			ae(u,v,w),ae(v,u,w);
		}
	}
	inline int nn(){
		static int n=0;
		return ++n;
	}
	struct stat{
		int x;
		lint d;
		inline friend bool operator < (const stat &a,const stat &b){
			return a.d>b.d;
		}
	};
	priority_queue<stat>q;
	lint dis[N];
	bool vis[N];
	inline void psh(int x,lint d){
		if(dis[x]>d){
			assert(!vis[x]);
			q.push((stat){x,dis[x]=d});
		}
	}
	inline void dij(int s){
		memset(vis,0,sizeof(vis));
		memset(dis,127,sizeof(dis));
		psh(s,0);
		while(!q.empty()){
			int x=q.top().x;
			assert(q.top().d>=dis[x]);
			q.pop();
			if(vis[x])continue;
			vis[x]=true;
			for(int i=head[x];~i;i=bro[i]){
				psh(to[i],dis[x]+val[i]);
			}
		}
	}
}
int n,m;
int city[N][N];
bool rouhor[N][N],rouver[N][N];
inline bool valid(int x,int y){
	return x>=0&&x<=n&&y>=0&&y<=m;
}
namespace G2{
	int hor[N][N],ver[N][N];
	lint dis[N][N];
	int vis[N][N];
	struct stat{
		int x,y;
		lint d;
		inline friend bool operator < (const stat &a,const stat &b){
			return a.d>b.d;
		}
	};
	priority_queue<stat>q;
	inline void psh(int x,int y,lint d){
		if(d<dis[x][y]){
			q.push((stat){x,y,dis[x][y]=d});
		}
	}
	inline bool reach(int x,int y,lint d);
	void dfs(int x,int y){
		lint d=dis[x][y];
		vis[x][y]=city[x][y];
		if(reach(x-1,y,d+ver[x][y])){
			rouver[x][y]=true;
			vis[x][y]=true;
		}
		if(reach(x+1,y,d+ver[x+1][y])){
			rouver[x+1][y]=true;
			vis[x][y]=true;
		}
		if(reach(x,y-1,d+hor[x][y])){
			rouhor[x][y]=true;
			vis[x][y]=true;
		}
		if(reach(x,y+1,d+hor[x][y+1])){
			rouhor[x][y+1]=true;
			vis[x][y]=true;
		}
	}
	inline bool reach(int x,int y,lint d){
		if(!valid(x,y))return false;
		if(d>dis[x][y])return false;
		if(vis[x][y]==0){
			dfs(x,y);
		}
		return vis[x][y]==1;
	}
	inline void Main(){
		assert(q.empty());
		memset(dis,127,sizeof(dis));
		memset(vis,0,sizeof(vis));
		psh(0,0,0);
		while(!q.empty()){
			int x=q.top().x,y=q.top().y;
			lint d=q.top().d;
			q.pop();
			if(vis[x][y])continue;
			vis[x][y]=true;
			x>0?psh(x-1,y,d+ver[x][y]):void();
			x<n?psh(x+1,y,d+ver[x+1][y]):void();
			y>0?psh(x,y-1,d+hor[x][y]):void();
			y<m?psh(x,y+1,d+hor[x][y+1]):void();
		}
		memset(vis,0,sizeof(vis));
		dfs(0,0);
	}
}
int node[N][N][4];
int main(){
#ifndef ONLINE_JUDGE
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
#endif
	n=ni,m=ni;
	G::init();
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int d=0;d<4;d++){
				node[i][j][d]=G::nn();
			}
		}
	}
	node[0][0][1]=0;
	memset(city,0,sizeof(city));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ni){
				city[i-1][j-1]=true;
				node[i][j-1][0]=0;
				node[i][j][1]=0;
				node[i-1][j][2]=0;
				node[i-1][j-1][3]=0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			G2::ver[i][j]=ni;
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=m;j++){
			G2::hor[i][j]=ni;
		}
	}
	G2::Main();
	for(int i=0;i<=n;i++){
		G::add(node[i][0][1],node[i][0][2],0);
		G::add(node[i][m][0],node[i][m][3],0);
	}
	for(int j=0;j<=m;j++){
		G::add(node[0][j][1],node[0][j][0],0);
		G::add(node[n][j][2],node[n][j][3],0);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			G::add(node[i-1][j][2],node[i][j][1],G2::ver[i][j]);
			G::add(node[i-1][j][3],node[i][j][0],G2::ver[i][j]);
			if(!rouver[i][j]){
				G::add(node[i-1][j][2],node[i-1][j][3],0);
				G::add(node[i][j][1],node[i][j][0],0);
			}
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=m;j++){
			G::add(node[i][j-1][0],node[i][j][1],G2::hor[i][j]);
			G::add(node[i][j-1][3],node[i][j][2],G2::hor[i][j]);
			if(!rouhor[i][j]){
				G::add(node[i][j-1][3],node[i][j-1][0],0);
				G::add(node[i][j][1],node[i][j][2],0);
			}
		}
	}
	G::dij(node[0][0][0]);
	printf("%lld\n",G::dis[node[0][0][2]]);
	return 0;
}
