#include <iostream>
#include <cstdio>
#include <cstring>
#define N 3010
using namespace std;
int n,lim,f[N][N],val[N],
	to[N<<1],bro[N<<1],head[N],etop=0;
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
void dfs(int x,int fa){
	for(int i=head[x];~i;i=bro[i]){
		int v=to[i];
		if(v!=fa){
			for(int j=lim;j>=0;j--){
				f[v][j]=f[x][j];
			}
			dfs(v,x);
			for(int j=lim;j>0;j--){
				apmax(f[x][j],f[v][j-1]+val[v]);
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
	int u,v,ans=0;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	memset(f,0,sizeof(f));
	dfs(1,0);
	for(int i=0;i<lim;i++){
		apmax(ans,f[1][i]+val[1]);
	}
	printf("%d",ans);
}
