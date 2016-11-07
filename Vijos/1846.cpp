#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 35
#define S 810000
#define INF 2147483647
using namespace std;
bool mat[N][N];
int tx,ty,ans,dis[S],mx[4]={0,1,0,-1},my[4]={1,0,-1,0},n,m;
bool inque[S];
inline int abs(int a){
	return a>0?a:-a;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m&&mat[x][y];
}
struct state{
	int ex,ey,sx,sy,hash,exp;
	state(int a,int b,int c,int d){
		ex=a,ey=b,sx=c,sy=d;
		hash=sy-1+30*(sx-1+30*(ey-1+30*(ex-1)));
		exp=abs(tx-sx)+abs(ty-sy);
	}
}cur(0,0,0,0);
bool operator < (state a,state b){
	return dis[a.hash]+a.exp>dis[b.hash]+b.exp;
}
priority_queue<state>q;
int main(){
	int qry,ex,ey,sx,sy,shash,tmp;
	scanf("%d%d%d",&n,&m,&qry);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&tmp);
			mat[i][j]=(tmp==1);
		}
	}
	while(qry--){
		scanf("%d%d%d%d%d%d",&ex,&ey,&sx,&sy,&tx,&ty);
		ans=INF;
		memset(dis,127,sizeof(dis));
		memset(inque,0,sizeof(inque));
		dis[sy-1+30*(sx-1+30*(ey-1+30*(ex-1)))]=0;
		q.push(state(ex,ey,sx,sy));
		while(!q.empty()){
			cur=q.top();
			cout<<"ex="<<cur.ex<<"\tey="<<cur.ey<<"\tsx="<<cur.sx<<"\tsy="<<cur.sy<<endl;
			q.pop();
			inque[cur.hash]=false;
			if(sx==tx&&sy==ty){
				apmin(ans,dis[cur.hash]);
				continue;
			}
			if(dis[cur.hash]>=ans){
				continue;
			}
			for(int i=0;i<4;i++){
				ex=cur.ex+mx[i],ey=cur.ey+my[i];
				if(!valid(ex,ey)){
					continue;
				}
				if(ex==cur.sx&&ey==cur.sy){
					sx=cur.ex,sy=cur.ey;
				}else{
					sx=cur.sx,sy=cur.sy;
				}
				shash=sy-1+30*(sx-1+30*(ey-1+30*(ex-1)));
				if(dis[shash]>dis[cur.hash]+1){
					dis[shash]=dis[cur.hash]+1;
					if(!inque[shash]&&dis[shash]<ans){
						inque[shash]=true;
						q.push(state(ex,ey,sx,sy));
					}
				}
			}
		}
		if(ans==INF){
			printf("-1\n");
		}else{
			printf("%d\n",ans);
		}
	}
}
