#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
using namespace std;
int to[N],minc=2147483647,dfn[N],dtop=0;
bool vis[N],inedge[N];
void dfs(int x){
	dfn[x]=dtop++;
	
}
int main(){
	int n;
	scanf("%d",&n);
	memset(inedge,0,sizeof(inedge));
	for(int i=1;i<=n;i++){
		scanf("%d",to+i);
		inedge[to[i]]=true;
	}
	
}
