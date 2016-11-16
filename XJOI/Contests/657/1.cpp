#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 1010
#define K 12
#define INF 0x7f7f7f7f
using namespace std;
int mat[N][N],spotx[K],spoty[K],dis[N][N][K],n,m,k,mx[4]={0,0,1,-1},my[4]={1,-1,0,0};
bool inq[N][N][K];
struct state{
	int x,y,p;
};
queue<state>q;
int main(){
	memset(dis,127,sizeof(dis));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&mat[i][j]);
		}
	}
	for(int i=0;i<k;i++){
		scanf("%d%d",spotx+i,spoty+i);
		mat[spotx[i]][spoty[i]]=2;
	}
	int x0,y0,p0,x,y,p=0;
	scanf("%d%d",&x,&y);
	if(x==spotx[p]&&y==spoty[p]){
		p++;
	}
	dis[x][y][p]=0;
	inq[x][y][p]=true;
	q.push((state){x,y,p});
	while(!q.empty()){
		x0=q.front().x,y0=q.front().y,p0=q.front().p;
		q.pop();
		if(p==k){
			continue;
		}
		if(dis[x0][y0][p0]>dis[spotx[k-1]][spoty[k-1]][k]){
			continue;
		}
		for(int i=0;i<4;i++){
			x=x0+mx[i],y=y0+my[i],p=p0;
			if(x>=1&&y>=1&&x<=n&&y<=m){
				if(x==spotx[p]&&y==spoty[p]){
					p++;
				}
				if(mat[x][y]==0||(mat[x][y]==2&&p!=p0)){
					if(dis[x][y][p]>dis[x0][y0][p0]+1){
						dis[x][y][p]=dis[x0][y0][p0]+1;
						if(!inq[x][y][p]){
							inq[x][y][p]=true;
							q.push((state){x,y,p});
						}
					}
				}
			}
		}
		inq[x0][y0][p0]=false;
	}
	if(dis[spotx[k-1]][spoty[k-1]][k]==INF){
		printf("%d",-1);
	}else{
		printf("%d",dis[spotx[k-1]][spoty[k-1]][k]);
	}
	return 0;
}
