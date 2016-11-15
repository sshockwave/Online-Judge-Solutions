#include <iostream>
#include <cstdio>
#include <cstring>
#include  <queue>
#define MOD 1000000009
#define N 105
#define INF 2147483647
using namespace std;
int mat[N][N],ans,n,cnt,mx[4]={0,0,1,-1},my[4]={1,-1,0,0};
struct state{
	bool mat[N][N];
	int x,y,dis;
	state(){
		memset(mat,0,sizeof(mat));
	}
};
queue<state>q;
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=n&&x+y<=n+1;
}
int main(){
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
		ans=INF;
		state cur;
		cur.mat[1][1]=true;
		cur.x=1,cur.y=1;
		cur.dis=0;
		q.push(cur);
		while(!q.empty()){
			cur=q.front();
			q.pop();
			if(cur.dis>ans){
				continue;
			}
			if(cur.x+cur.y==n+1){
				if(cur.dis<ans){
					cnt=1;
					ans=cur.dis;
				}else{
					cnt=(cnt+1)%MOD;
				}
				continue;
			}
			for(int i=0,x=cur.x,y=cur.y;i<4;i++){
				cur.x=x+mx[i],cur.y=y+my[i];
				if(valid(cur.x,cur.y)&&!cur.mat[cur.x][cur.y]){
					cur.mat[cur.x][cur.y]=true;
					cur.dis+=mat[cur.x][cur.y];
					q.push(cur);
					cur.dis-=mat[cur.x][cur.y];
					cur.mat[cur.x][cur.y]=false;
				}
			}
		}
		printf("%d\n",cnt);
	}
}
