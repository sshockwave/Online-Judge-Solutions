#include <cstdio>
#include <cstring>
#define clr(x) memset(x,0,sizeof(x))
#define N 10010
#define M 50010
#define INF 1000000
using namespace std;
struct edge{
	int u,v,w;
}e[M];
inline bool edgecmp(const edge &a,const edge &b){
	return a.w>b.w;
}
namespace unif{
	int fa[N],rank[N];
	int getroot(int x){
		if(fa[x]){
			return fa[x]=getroot(fa[x]);
		}
		return x;
	}
	void join(int a,int b){
		a=getroot(a),b=getroot(b);
		if(rank[a]<rank[b]){
			swap(a,b);
		}
		fa[b]=a;
		if(rank[a]==rank[b]){
			rank[a]++;
		}
	}
}
namespace tree{
	int to[N<<1],bro[N<<1],val[N<<1],head[N],ntop=1,
		walk[N][15],f[N][15],dep[N];
	inline void add_edge(int u,int v,int va){
		to[ntop]=v;
		bro[ntop]=head[u];
		val[ntop]=va;
		head[u]=ntop++;
	}
	void dfs(int x){
		for(int i=1;walk[x][i-1];i++){
			walk[x][i]=walk[walk[x][i-1]][i-1];
			f[x][i]=min(f[x][i-1],f[walk[x][i-1]][i-1]);
		}
		for(int i=head[x];i;i=bro[i]){
			if(to[i]!=walk[x][0]){
				walk[to[i]][0]=x;
				f[to[i]][0]=val[i];
				dep[to[i]]=dep[x]+1;
				dfs(to[i]);
			}
		}
	}
	int query(int u,int v){
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		int ans=INF;
		for(int i=14;i>=0;i--){
			if(dep[walk[u][i]]>=dep[v]){
				ans=min(ans,f[u][i]);
				u=walk[u][i];
			}
		}
		if(u==v){
			return ans;
		}
		
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	}
	sort(edge,edge+m,edgecmp);
	clr(unif::fa),clr(unif::rank),clr(tree:head);
	for(int i=0;i<m;i++){
		if(unif::getroot(e[i].u)!=unif::getroot(e[i].v)){
			tree::add_edge(e[i].u,e[i].v);
			tree::add_edge(e[i].v,e[i].u);
			unif::join(e[i].u,e[i].v);
		}
	}
	clr(tree::walk),clr(tree::f),tree::dep[1]=tree::dep[0]=0;
	tree::dfs(1);
	
}
