#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
#define M 200010
using namespace std;
int to[M],bro[M],head[N],s,t;
bool vis[N],valid[N];
void dfs(int x){
	vis[x]=true;
	valid[x]=true;
	bool con=false;
	for(int i=head[x];~i;i=bro[i]){
		if(!vis[to[i]]){
			if(dfs(to[i])){
				con=true;
			}else{
				valid[x]=false;
			}
		}
	}
	vis[x]=false;
	if(x==t){
		con=true;
	}
	return con;
}
int main(){
	memset(head,-1,sizeof(head));
	int n,m,x;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",x,to[i]);
		bro[i]=head[x];
		head[x]=i;
	}
	scanf("%d%d",&s,&t);
	memset(vis,0,sizeof(vis));
	dfs(s);
}
