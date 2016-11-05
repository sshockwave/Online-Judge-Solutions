#include <iostream>
#include <cstdio>
#include <cstring>
#define N 3010
#define INF 10000000
using namespace std;
int n,lim,f[N][N],val[N],size[N],fa[N],dep[N],
	to[N<<1],bro[N<<1],head[N],etop=0;
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
void dfs(int x){
	size[x]=1;
	dep[x]=dep[fa[x]]+1;
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=fa[x]){
			fa[to[i]]=x;
			dfs(to[i]);
			size[x]+=size[to[i]];
		}
	}
	for(int i=0;i<=size[x];i++){
		f[x][i]=-INF;
	}
	f[x][1]=val[x];
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=fa[x]){
			for(int j=size[x];j>1;j--){
				for(int k=min(size[to[i]],j-1);k>=0;k--){
					f[x][j]=max(f[x][j],f[x][j-k]+f[to[i]][k]);
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&lim);
	for(int i=1;i<=n;i++){
		scanf("%d",val+i);
	}
	memset(head,-1,sizeof(head));
	int u,v;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	fa[1]=dep[0]=0;
	memset(f,0,sizeof(f));
	dfs(1);
	printf("%d",f[1][lim]);
}
