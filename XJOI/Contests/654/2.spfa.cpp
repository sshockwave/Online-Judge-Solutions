#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define MOD 1000000009
#define N 105
#define INF 2147483647
using namespace std;
int mat[N][N],ans,n,mx[4]={0,0,1,-1},my[4]={1,-1,0,0},dis[N][N],ways[N][N];
bool inq[N][N];
struct coor{
	int x,y;
};
queue<coor>q;
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=n&&x+y<=n+1;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int main(){
	memset(inq,0,sizeof(inq));
	while(scanf("%d",&n),n){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&mat[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;i+j<=n;j++){
				mat[i][j]+=mat[n+1-j][n+1-i];
			}
		}
		memset(dis,127,sizeof(dis));
		dis[1][1]=mat[1][1];
		inq[1][1]=true;
		q.push((coor){1,1});
		while(!q.empty()){
			int x=q.front().x,y=q.front().y;
			q.pop();
			inq[x][y]=false;
			for(int i=0,tx,ty;i<4;i++){
				tx=x+mx[i],ty=y+my[i];
				if(valid(tx,ty)){
					if(dis[tx][ty]>dis[x][y]+mat[tx][ty]){
						dis[tx][ty]=dis[x][y]+mat[tx][ty];
						if(!inq[tx][ty]){
							inq[tx][ty]=true;
							q.push((coor){tx,ty});
						}
					}
				}
			}
		}
		memset(ways,0,sizeof(ways));
		ways[1][1]=1;
		inq[1][1]=true;
		q.push((coor){1,1});
		while(!q.empty()){
			int x=q.front().x,y=q.front().y;
			q.pop();
			inq[x][y]=false;
			for(int i=0,tx,ty;i<4;i++){
				tx=x+mx[i],ty=y+my[i];
				if(valid(tx,ty)){
					if(dis[tx][ty]==dis[x][y]+mat[tx][ty]){
						(ways[tx][ty]+=ways[x][y])%=MOD;
						if(!inq[tx][ty]){
							inq[tx][ty]=true;
							q.push((coor){tx,ty});
						}
					}
				}
			}
		}
		int minv=INF,ans=0;
		for(int i=1;i<=n;i++){
			apmin(minv,dis[i][n+1-i]);
		}
		for(int i=1;i<=n;i++){
			if(dis[i][n+1-i]==minv){
				(ans+=ways[i][n+1-i])%=MOD;
			}
		}
		printf("%d\n",ans);
	}
}
