#include <iostream>
#include <cstdio>
#include <cstring>
#define N 60
using namespace std;
int to[N<<1],bro[N<<1],val[N<<1],head[N],ntop=0,
	n,tm;
inline void add_edge(int u,int v,int w){
	to[ntop]=v;
	bro[ntop]=head[u];
	val[ntop]=w;
	head[u]=ntop++;
}
bool dfs(int x,long long sum){
//	cout<<"At "<<x<<"\tsum="<<sum<<endl;
	if(sum==tm){
//		cout<<"OK!"<<endl;
		return x==n-1;
	}else if(sum>tm){
		return false;
	}
	for(int i=head[x];~i;i=bro[i]){
		if(dfs(to[i],sum+val[i])){
			return true;
		}
	}
	return false;
}
int main(){
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	int tot,m,u,v,w;
	for(scanf("%d",&tot);tot--;){
		memset(head,-1,sizeof(head));
		scanf("%d%d%d",&n,&m,&tm);
		while(m--){
			scanf("%d%d%d",&u,&v,&w);
			add_edge(u,v,w);
			add_edge(v,u,w);
		}
		if(dfs(0,0)){
			printf("Possible\n");
		}else{
			printf("Impossible\n");
		}
	}
}
