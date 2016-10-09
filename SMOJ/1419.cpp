#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
#define M 50010
using namespace std;
int to[M],bro[M],head[N],n,dfn[N],low[N],stk[N],ring[N],rtop=0,stop=0,dtop=0;
bool instk[N];
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
void dfs(int x){
	dfn[x]=low[x]=dtop++;
	instk[x]=true;
	stk[stop++]=x;
	int cur;
	for(int i=head[x];~i;i=bro[i]){
		cur=to[i];
		if(dfn[cur]==-1){
			dfs(cur);
			if(low[cur]<low[x]){
				low[x]=low[cur];
			}
		}else if(instk[cur]&&dfn[cur]<low[x]){
			low[x]=cur;
		}
	}
	if(dfn[x]==low[x]){
		ring[rtop++]=x;
		
	}
	instk[x]=false;
}
int main(){
//	freopen("1419.in","r",stdin);
//	freopen("1419.out","w",stdout);
	memset(head,-1,sizeof(head));
	memset(instk,0,sizeof(instk));
	memset(dfn,-1,sizeof(dfn));
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
	}
	for(int i=1;i<=n;i++){
		if(dfn[i]==-1){
			dfs(i);
		}
	}
}
