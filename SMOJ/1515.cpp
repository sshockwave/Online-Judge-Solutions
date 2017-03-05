#include <iostream>
#include <cstdio>
#include <cstring>
#define N 300010
#define INF 2147483647
#define clr(x,y) memset((x),y,sizeof(x))
using namespace std;
namespace tree{
	int to[N<<1],bro[N<<1],head[N];
}
int main(){
//	freopen("1515.in","r",stdin);
//	freopen("1515.out","w",stdout);
	int n,m,u,v;
	scanf("%d%d",&n,&m);
	clr(head,-1);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		tree::add_edge(u,v);
		tree::add_edge(v,u);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
