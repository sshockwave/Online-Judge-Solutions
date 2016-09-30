#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 250
using namespace std;
int c[N][N],f[N][N],to[N],dis[N],m;
inline bool bfs(){
	memset(dis,-1,sizeof(dis));
	queue<int>point;
	point.push(m);
	dis[m]=0;
	int cur;
	while(!point.empty()){
		cur=point.front();
		point.pop();
		for(int i=1;i<=m;i++){
			if(c[i][cur]>f[i][cur]&&dis[i]==-1){
				point.push(i);
				dis[i]=dis[cur]+1;
			}
		}
	}
	return dis[1]!=-1;
}
inline int dfs(int x,int high){
	if(x==m){
		return high;
	}
	int tmp,sum=0;
	for(int i=1;i<=m;i++){
		if(dis[i]==dis[x]-1&&c[x][i]>f[x][i]){
			tmp=dfs(i,min(high,c[x][i]-f[x][i]));
			f[x][i]+=tmp;
			f[i][x]-=tmp;//ADD THIS
			high-=tmp;
			sum+=tmp;
			if(high==0){
				break;
			}
		}
	}
	return sum;
}
int main(){
	int n,a,b,flow=0;
	cin>>n>>m;
	memset(c,0,sizeof(c));
	for(int i=0;i<n;i++){
		cin>>a>>b;
		cin>>c[a][b];
	}
	memset(f,0,sizeof(f));
	while(bfs()){
		flow+=dfs(1,2147482647);
	}
	cout<<flow;
}
