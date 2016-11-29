#include <iostream>
#include <cstdio>
#include <cstring>
#define N 210
using namespace std;
int to[N],n,m,ans;
bool mat[N][N],vis[N];
bool dfs(int x){
	for(int i=1;i<=m;i++){
		if(mat[x][i]&&!vis[i]){
			vis[i]=true;
			if(to[i]==-1||dfs(to[i])){
				to[i]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	while(scanf("%d%d",&n,&m)){
		memset(to,-1,sizeof(to));
		memset(mat,0,sizeof(mat));
		for(int i=1,s,t;i<=n;i++){
			for(scanf("%d",&s);s--;){
				scanf("%d",&t);
				mat[i][t]=true;
			}
		}
		ans=0;
		for(int i=1;i<=n;i++){
			memset(vis,0,sizeof(vis));
			if(dfs(i)){
				ans++;
			}
		}
		printf("%d\n",ans);
	}
}
