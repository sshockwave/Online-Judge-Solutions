#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define clr(x) memset(x,0,sizeof(x))
#define N 10010
#define M 50010
#define INF 1000000
using namespace std;
struct edge{
	int u,v,w;
}e[M];
bool found[N];
inline bool edgecmp(const edge &a,const edge &b){
	return a.w>b.w;
}
inline void apmin(int &a,int b){
	if(a>b){
//		cout<<"Apply min"<<endl; 
		a=b;
	}
}
namespace unif{
	int fa[N],rank[N];
	int getroot(int x){
		if(fa[x]==x){//fa[x]==x:return fa[x]=getroot(fa[x]) => now
			return x;
		}
		return fa[x]=getroot(fa[x]);
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
//		cout<<"DFS:"<<x<<endl;
//		cout<<"\twalk 1 to "<<walk[x][0]<<"\tmin="<<f[x][0]<<endl;
		for(int i=1;walk[x][i-1];i++){
			walk[x][i]=walk[walk[x][i-1]][i-1];
			f[x][i]=min(f[x][i-1],f[walk[x][i-1]][i-1]);
//			cout<<"\twalk "<<(1<<i)<<" to "<<walk[x][i]<<"\tmin="<<f[x][i]<<endl;
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
//		cout<<"Query:("<<u<<","<<v<<")"<<endl;
		int ans=INF;
		for(int i=14;i>=0;i--){
			if(walk[u][i]&&dep[walk[u][i]]>=dep[v]){
//				cout<<"\tWalk up to "<<walk[u][i]<<endl;
				apmin(ans,f[u][i]);
				u=walk[u][i];
			}
		}
		if(u==v){
			return ans;
		}
		for(int i=14;i>=0;i--){
			if(walk[u][i]&&walk[v][i]&&walk[u][i]!=walk[v][i]){
				apmin(ans,f[u][i]);
				apmin(ans,f[v][i]);
				u=walk[u][i],v=walk[v][i];
			}
		}
		apmin(ans,f[u][0]);
		apmin(ans,f[v][0]);
		return ans;
	}
}
int main(){
	int n,m,q,a,b;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	}
	sort(e,e+m,edgecmp);
	for(int i=1;i<=n;i++){
		unif::fa[i]=i;
	}
	clr(unif::rank),clr(tree::head);
	for(int i=0;i<m;i++){
		if(unif::getroot(e[i].u)!=unif::getroot(e[i].v)){
			tree::add_edge(e[i].u,e[i].v,e[i].w);
			tree::add_edge(e[i].v,e[i].u,e[i].w);
			unif::join(e[i].u,e[i].v);
		}
	}
	clr(tree::walk),clr(tree::f),clr(tree::dep),clr(found);
	for(int i=1;i<=n;i++){
		if(!found[unif::getroot(i)]){
			found[unif::fa[i]]=true;
			tree::dfs(unif::fa[i]);//i  =>  fa[i]
		}
	}
	for(scanf("%d",&q);q--;){
		scanf("%d%d",&a,&b);
		if(unif::fa[a]==unif::fa[b]){
			cout<<tree::query(a,b)<<endl;
		}else{
			cout<<-1<<endl;
		}
	}
}
