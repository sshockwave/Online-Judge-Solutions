#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
#define INF 2147483647
using namespace std;
int to[N],dfn[N],low[N],stk[N],bln[N],size[N],dtop=0,stop=0;
bool instk[N];
void dfs(int x){
	dfn[x]=low[x]=dtop++;
	stk[stop++]=x;
	instk[x]=true;
	if(dfn[to[x]]==-1){
		dfs(to[x]);
		if(low[to[x]]<low[x]){
			low[x]=low[to[x]];
		}
	}else if(instk[to[x]]){
		low[x]=dfn[to[x]];
	}
	if(low[x]==dfn[x]){
		int v;
		do{
			v=stk[--stop];
			instk[v]=false;
			bln[v]=x;
			size[x]++;
		}while(v!=x);
	}
}
int main(){
	int n,ans=INF;
	memset(size,0,sizeof(size));
	memset(dfn,-1,sizeof(dfn));
	memset(instk,0,sizeof(instk));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",to+i);
	}
	for(int i=1;i<=n;i++){
		if(dfn[i]==-1){
			dfs(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(size[bln[i]]<ans&&size[bln[i]]>1){
			ans=size[bln[i]];
		}
	}
	printf("%d",ans);
}
