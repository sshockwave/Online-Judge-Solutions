#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
#define M 200010
using namespace std;
int to[M<<1],bro[M<<1],head[N],etop=0,color[N];
bool flag=false;
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
void dfs(int x){
	for(int i=head[x];~i;i=bro[i]){
		if(color[to[i]]){
			if(color[to[i]]==color[x]){
				flag=true;
			}
		}else{
			color[to[i]]=-color[x];
			dfs(to[i]);
		}
		if(flag){
			return;
		}
	}
}
int main(){
	int n,m,u,v,q;
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof(head));
	while(m--){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	memset(color,0,sizeof(color));
	color[1]=1;
	dfs(1);
	scanf("%d",&q);
	if(flag){
		while(q--){
			printf("Yes\n");
		}
		return 0;
	}
	while(q--){
		scanf("%d%d",&u,&v);
		if(color[u]==color[v]){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
}
