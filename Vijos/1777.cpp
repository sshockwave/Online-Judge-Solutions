#include <iostream>
#include <cstdio>
#include <cstring>
#define N 510
using namespace std;
int height[N][N],m,n,mx[4]={0,1,0,-1},my[4]={1,0,-1,0},quex[N*N],quey[N*N],qhead,qtop;
bool vis[N][N];
inline void clearvis(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			vis[i][j]=false;
		}
	}
}
inline bool valid(int x,int y){
	return x>0&&x<=n&&y>0&&y<=n&&!vis[x][y];
}
inline int bfs(){
	
}
int main(){
	scanf("%d%d",&n,&m);
	qhead=qtail=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&height[i][j]);
		}
	}
	clearvis();
	for(int i=1;i<=n;i++){
		quex[qtail]=1;quey[qtail]=i;qtail++;
		vis[1][i]=true;
	}
	int tmp=bfs();
	if(tmp){
		printf("0\n%d",tmp);
		return 0;
	}
	
}
