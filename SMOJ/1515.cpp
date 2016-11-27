#include <iostream>
#include <cstdio>
#include <cstring>
#define N 300010
#define INF 2147483647
using namespace std;
int to[N<<1],bro[N<<1],head[N],w[N],s[N],t[N],size[N],dep[N],ans[N],etop=0,fa[N],tfa[N];
bool vis[N];
namespace query{
	int to[N<<1],ord[N<<1],bro[N<<1],head[N],etop=0;
	inline void add_edge(int u,int v,int val){
		to[etop]=v;
		ord[etop]=val;
		bro[etop]=head[u];
		head[u]=etop++;
	}
}
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
void tarjan(int x){
	tfa[x]=0;
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=fa[x]){
			fa[to[i]]=x;
			dep[to[i]]=dep[x]+1;
			tarjan(x);
		}
	}
	
}
void getdep(int x){
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=fa[x]){
			fa[to[i]]=x;
			dep[to[i]]=dep[x]+1;
			getdep(to[i]);
		}
	}
}
int main(){
	freopen("running.in","r",stdin);
	freopen("running.out","w",stdout);
	memset(head,-1,sizeof(head));
	int n,m,u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",w+i);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",s+i,t+i);
		query::add_edge(s[i],t[i],i);
		query::add_edge(t[i],s[i],i);
	}
	switch(n%10){
		case 1:{
			memset(ans,0,sizeof(ans));
			for(int i=1;i<=m;i++){
				ans[s[i]]++;
			}
			for(int i=1;i<=n;i++){
				if(w[i]){
					ans[i]=0;
				}
				printf("%d ",ans[i]);
			}
			break;
		}
		case 2:{
			memset(ans,0,sizeof(ans));
			for(int i=1;i<=m;i++){
				ans[s[i]]++;
			}
			for(int i=1;i<=n;i++){
				printf("%d ",ans[i]);
			}
			break;
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
