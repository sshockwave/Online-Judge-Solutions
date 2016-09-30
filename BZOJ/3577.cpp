#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 100010
#define A 10010
#define INF 2147483647
using namespace std;
namespace net{
	int ntop=0,head[N],con[N<<1],bro[N<<1],c[N<<1],f[N<<1],rev[N<<1],ltop=0,s,t,dis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline int new_node(){
		return ntop++;
	}
	inline bool bfs(){
		queue<int>points;
		memset(dis,-1,sizeof(dis));
		dis[t]=0;
		points.push(t);
		int cur;
		while(!points.empty()){
			cur=points.front();
			points.pop();
			for(int i=head[cur];~i;i=bro[i]){
				if(c[i]>f[i]&&dis[con[i]]==-1){
					dis[con[i]]=dis[cur]+1;
					points.push(con[i]);
				}
			}
		}
		return dis[s]!=-1;
	}
	inline void add_edge(int u,int v,int cap){
		con[ltop]=v;
		bro[ltop]=head[u];
		c[ltop]=cap;
		f[ltop]=0;
		rev[ltop]=ltop+1;
		head[u]=ltop++;
		con[ltop]=u;
		bro[ltop]=head[v];
		c[ltop]=0;
		f[ltop]=0;
		rev[ltop]=ltop-1;
		head[v]=ltop++;
	}
	int dfs(int x,int high){
		int delta,sum=0;
		for(int i=head[x];~i;i=bro[i]){
			if(dis[con[i]]==dis[x]-1&&c[i]>f[i]){
				delta=dfs(con[i],min(high,c[i]-f[i]));
				f[i]+=delta;
				f[rev[i]]-=delta;
				sum+=delta;
				high-=delta;
				if(high==0){
					break;
				}
			}
		}
		return sum;
	}
	inline int dinic(int start,int to){
		s=start,t=to;
		int flow=0;
		while(bfs()){
			flow+=dfs(s,INF);
		}
		return flow;
	}
}
inline int log2(int x){
	int cnt=-1;
	for(;x;cnt++,x>>=1);
	return cnt;
}
int stnodea[65][65][8],stnodeb[65][65][8],nodea[A],nodeb[A];
int main(){
	net::init();
	int r,c,a,b,tmp,x1,y1,x2,y2,s=net::new_node(),end=net::new_node();
	cin>>r>>c>>a>>b;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			stnodea[i][j][0]=net::new_node();
			stnodeb[i][j][0]=net::new_node();
			cin>>tmp;
			net::add_edge(stnodea[i][j][0],stnodeb[i][j][0],tmp);
		}
	}
	for(int t=1;(1<<t)<=r||(1<<t)<=c;t++){
		for(int i=1;i<=r;i++){
			for(int j=1;j<=c;j++){
				stnodea[i][j][t]=net::new_node();
				net::add_edge(stnodea[i][j][t],stnodea[i][j][t-1],INF);
				net::add_edge(stnodea[i][j][t],stnodea[i+(1<<t-1)][j][t-1],INF);
				net::add_edge(stnodea[i][j][t],stnodea[i][j+(1<<t-1)][t-1],INF);
				net::add_edge(stnodea[i][j][t],stnodea[i+(1<<t-1)][j+(1<<t-1)][t-1],INF);
				stnodeb[i][j][t]=net::new_node();
				net::add_edge(stnodeb[i][j][t-1],stnodeb[i][j][t],INF);
				net::add_edge(stnodeb[i+(1<<t-1)][j][t-1],stnodeb[i][j][t],INF);
				net::add_edge(stnodeb[i][j+(1<<t-1)][t-1],stnodeb[i][j][t],INF);
				net::add_edge(stnodeb[i+(1<<t-1)][j+(1<<t-1)][t-1],stnodeb[i][j][t],INF);
			}
		}
	}
	for(int i=1;i<=a;i++){
		nodea[i]=net::new_node();
		cin>>tmp>>x1>>y1>>x2>>y2;
		net::add_edge(s,nodea[i],tmp);
		tmp=log2(x2-x1+1);
		net::add_edge(nodea[i],stnodea[x1][y1][tmp],INF);
		net::add_edge(nodea[i],stnodea[x1][y2-(1<<tmp)+1][tmp],INF);
		net::add_edge(nodea[i],stnodea[x2-(1<<tmp)+1][y1][tmp],INF);
		net::add_edge(nodea[i],stnodea[x2-(1<<tmp)+1][y2-(1<<tmp)+1][tmp],INF);
	}
	for(int i=1;i<=b;i++){
		nodeb[i]=net::new_node();
		cin>>tmp>>x1>>y1>>x2>>y2;
		net::add_edge(nodeb[i],end,tmp);
		tmp=log2(x2-x1+1);
		net::add_edge(stnodea[x1][y1][tmp],nodeb[i],INF);
		net::add_edge(stnodea[x1][y2-(1<<tmp)+1][tmp],nodeb[i],INF);
		net::add_edge(stnodea[x2-(1<<tmp)+1][y1][tmp],nodeb[i],INF);
		net::add_edge(stnodea[x2-(1<<tmp)+1][y2-(1<<tmp)+1][tmp],nodeb[i],INF);
	}
	cout<<net::dinic(s,end);
}
