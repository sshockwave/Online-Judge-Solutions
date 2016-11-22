#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
using namespace std;
int fa[N<<1];
int getroot(int x){
	if(fa[x]==0){
		return x;
	}
	return fa[x]=getroot(fa[x]);
}
int main(){
	memset(fa,0,sizeof(fa));
	int n,m,u,v,ans=0;
	scanf("%d%d",&n,&m);
	while(n--){
		scanf("%d%d",&u,&v);
		u=getroot(u),v=getroot(v);
		if(u!=v){
			ans++;
			fa[u]=v;
		}
	}
	printf("%d",ans);
}
