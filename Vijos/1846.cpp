#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 35
#define INF 2139062143
using namespace std;
int mx[4]={0,0,1,-1},my[4]={1,-1,0,0},n,m,bdis[N][N],bro[N*N*16],val[N*N*16],head[N][N][4],etop=0,dis[N][N][4];
//string direction[4]={"Right","Left","Down","Up"};
bool mat[N][N],inq[N][N][4];
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m&&mat[x][y];
}
struct coor{
	int x,y;
	coor(int a,int b){
		x=a,y=b;
	}
};
struct state{
	int x,y,d;
	state(){}
	state(int a,int b,int c){
		x=a,y=b,d=c;
	}
}to[N*N*16];
queue<coor>q;
queue<state>qs;
inline void bfs(int sx,int sy){
//	cout<<"New bfs from ("<<sx<<","<<sy<<")"<<endl;
	q.push(coor(sx,sy));
	memset(bdis,-1,sizeof(bdis));
	bdis[sx][sy]=0;
	int x,y;
	while(!q.empty()){
		coor cur=q.front();
		q.pop();
//		cout<<"\t("<<cur.x<<","<<cur.y<<")="<<bdis[cur.x][cur.y]<<endl;
		for(int i=0;i<4;i++){
			x=cur.x+mx[i];
			y=cur.y+my[i];
			if(valid(x,y)&&bdis[x][y]==-1){
				bdis[x][y]=bdis[cur.x][cur.y]+1;
				q.push(coor(x,y));
			}
		}
	}
}
inline void add_edge(state u,state v,int w){
//	cout<<"Add edge:("<<u.x<<","<<u.y<<")"<<direction[u.d]<<"\t==>\t("<<v.x<<","<<v.y<<")->"<<direction[v.d]<<"\tlength="<<w<<endl;
	to[etop]=v;
	bro[etop]=head[u.x][u.y][u.d];
	val[etop]=w;
	head[u.x][u.y][u.d]=etop++;
}
int main(){
	memset(head,-1,sizeof(head));
	int tot,tmp,ex,ey,sx,sy,tx,ty;
	scanf("%d%d%d",&n,&m,&tot);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&tmp);
			mat[i][j]=(tmp==1);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]){
				mat[i][j]=false;
				for(int k=0;k<4;k++){
					if(valid(i+mx[k],j+my[k])){
						add_edge(state(i,j,k),state(i+mx[k],j+my[k],k^1),1);
						bfs(i+mx[k],j+my[k]);
						for(int l=0;l<4;l++){
							if(l!=k&&bdis[i+mx[l]][j+my[l]]!=-1){
								add_edge(state(i,j,k),state(i,j,l),bdis[i+mx[l]][j+my[l]]);
							}
						}
					}
				}
				mat[i][j]=true;
			}
		}
	}
	while(tot--){
		memset(dis,127,sizeof(dis));
		memset(inq,0,sizeof(inq));
		scanf("%d%d%d%d%d%d",&ex,&ey,&sx,&sy,&tx,&ty);
//		cout<<"SPFA"<<endl;
		mat[sx][sy]=false;
		bfs(ex,ey);
		mat[sx][sy]=true;
		for(int i=0;i<4;i++){
			if(bdis[sx+mx[i]][sy+my[i]]!=-1){
				dis[sx][sy][i]=bdis[sx+mx[i]][sy+my[i]];
				qs.push(state(sx,sy,i));
				inq[sx][sy][i]=true;
			}
		}
		while(!qs.empty()){
			state cur=qs.front();
			qs.pop();
//			cout<<"Current:("<<cur.x<<","<<cur.y<<")->"<<direction[cur.d]<<"\tdis="<<dis[cur.x][cur.y][cur.d]<<endl;
			for(int i=head[cur.x][cur.y][cur.d];~i;i=bro[i]){
				if(dis[to[i].x][to[i].y][to[i].d]>dis[cur.x][cur.y][cur.d]+val[i]){
					dis[to[i].x][to[i].y][to[i].d]=dis[cur.x][cur.y][cur.d]+val[i];
//					cout<<"\tUpdate ("<<to[i].x<<","<<to[i].y<<")->"<<direction[to[i].d]<<" dis="<<dis[to[i].x][to[i].y][to[i].d]<<endl;
					if(!inq[to[i].x][to[i].y][to[i].d]){
						inq[to[i].x][to[i].y][to[i].d]=true;
						qs.push(to[i]);
					}
				}
			}
		}
		int ans=INF;
		for(int i=0;i<4;i++){
			apmin(ans,dis[tx][ty][i]);
		}
		if(ans==INF){
			printf("-1\n");
		}else{
			printf("%d\n",ans);
		}
	}
}
