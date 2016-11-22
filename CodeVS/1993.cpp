#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 250
#define INF 2147483647
using namespace std;
int c[N][N],n,que[N],qhead,qtail,dis[N];
inline void bfs(){
	memset(dis,-1,sizeof(dis));
	dis[n]=0;
	qhead=qtail=0;
	que[qtail++]=n;
	while(qhead<qtail){
		int x=que[qhead++];
		for(int i=1;i<=n;i++){
			if(dis[i]==-1&&c[i][x]){
				dis[i]=dis[x]+1;
				que[qtail++]=i;
			}
		}
	}
}
int dfs(int x,int allo){
	if(x==n){
		return allo;
	}
	int flow=0;
	for(int i=1,delta;i<=n&&allo;i++){
		if(dis[i]==dis[x]-1){
			delta=dfs(i,min(allo,c[x][i]));
			c[x][i]-=delta,c[i][x]+=delta;
			flow+=delta,allo-=delta;
		}
	}
	return flow;
}
int main(){
	int m,u,v,w,delta,flow=0;
	scanf("%d%d",&m,&n);
	memset(c,0,sizeof(c));
	while(m--){
		scanf("%d%d%d",&u,&v,&w);
		c[u][v]+=w;
	}
	while(bfs(),delta=dfs(1,INF)){
		flow+=delta;
	}
	printf("%d",flow);
}
