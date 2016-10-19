#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1010
#define M 100010
#define Q 100010
using namespace std;
int n,e[M][3],to[N<<1],bro[N<<1],val[N<<1],head[N],etop=0,dep[N],walk[N][12],f[N][12],logt[N];
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	head[u]=etop++;
}
namespace kruskal{
	struct edge{
		int u,v,w;
	}e[M];
	int ntop=0;
	int fa[N],rank[N];
	inline bool edgecmp(const edge &a,const edge &b){
		return a.w<b.w;
	}
	inline void add(int u,int v,int w){
		e[ntop].u=u;
		e[ntop].v=v;
		e[ntop].w=w;
		ntop++;
	}
	int getroot(int x){
		if(fa[x]==0){
			return x;
		}
		return fa[x]=getroot(fa[x]);
	}
	inline bool join(int a,int b){
		a=getroot(a),b=getroot(b);
		if(a==b){
			return false;
		}
		if(rank[a]<rank[b]){
			swap(a,b);
		}
		fa[b]=a;
		if(rank[a]==rank[b]){
			rank[a]++;
		}
		return true;
	}
	inline void work(){
		memset(fa,0,sizeof(fa));
		memset(rank,0,sizeof(rank));
		sort(e,e+ntop,edgecmp);
		for(int i=0;i<ntop;i++){
			if(join(e[i].u,e[i].v)){
				add_edge(e[i].u,e[i].v,e[i].w);
				add_edge(e[i].v,e[i].u,e[i].w);
			}
		}
	}
}
void dfs(int x){
	logt[x]=0;
	dep[x]=dep[walk[x][0]]+1;
	for(int &i=logt[x];walk[x][i];i++){
		walk[x][i+1]=walk[walk[x][i]][i];
		f[x][i+1]=max(f[x][i],f[walk[x][i]][i]);
	}
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=walk[x][0]){
			walk[to[i]][0]=x;
			f[to[i]][0]=val[i];
			dfs(to[i]);
		}
	}
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline int query(int a,int b){
	if(dep[a]<dep[b]){
		swap(a,b);
	}
	int ans=0;
	for(int i=logt[a];i>=0;i--){
		if(dep[walk[a][i]]>=dep[b]){
			apmax(ans,f[a][i]);
			a=walk[a][i];
		}
	}
	if(a==b){
		return ans;
	}
	for(int i=logt[a];i>=0;i--){
		if(walk[a][i]!=walk[b][i]){
			apmax(ans,f[a][i]);
			apmax(ans,f[b][i]);
			a=walk[a][i];
			b=walk[b][i];
		}
	}
	apmax(ans,f[a][0]);
	apmax(ans,f[b][0]);
	return ans;
}
int main(){
	memset(to,0,sizeof(to));
	memset(val,0,sizeof(val));
	memset(head,-1,sizeof(head));
	int m,q,a,b;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
		kruskal::add(e[i][0],e[i][1],e[i][2]);
	}
	kruskal::work();
	memset(f,0,sizeof(f));
	memset(walk,0,sizeof(walk));
	dep[0]=0;
	dfs(1);
	while(q--){
		scanf("%d%d",&a,&b);
		if(query(e[a][0],e[a][1])>=b){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	}
}
