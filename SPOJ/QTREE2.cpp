#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=10010,logN=20;
struct Tree{
	const static int E=N*2;
	int to[E],bro[E],val[E],head[N],etop;
	inline void reset(){
		memset(head,-1,sizeof(head));
		memset(ldep,0,sizeof(ldep));
		memset(fa,0,sizeof(fa));
		etop=dep[1]=len[1]=0;
		dep[0]=-1;
	}
	inline void add_edge(int u,int v,int w){
		to[etop]=v;
		bro[etop]=head[u];
		val[etop]=w;
		head[u]=etop++;
	}
	int fa[N][logN],dep[N],ldep[N],len[N];
	void dfs(int x,int f){
		fa[x][0]=f;
		for(int &k=ldep[x];fa[x][k+1]=fa[fa[x][k]][k];k++);
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				dep[v]=dep[x]+1;
				len[v]=len[x]+val[i];
				dfs(v,x);
			}
		}
	}
	inline int lca(int u,int v){
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		for(int j=ldep[u];j>=0;j--){
			if(dep[u]-(1<<j)>=dep[v]){
				u=fa[u][j];
			}
		}
		if(u==v){
			return u;
		}
		for(int j=min(ldep[u],ldep[v]);j>=0;j--){
			if(fa[u][j]&&fa[v][j]&&fa[u][j]!=fa[v][j]){
				u=fa[u][j],v=fa[v][j];
			}
		}
		assert(fa[u][0]==fa[v][0]);
		return fa[u][0];
	}
	inline int dist(int u,int v){
		return len[u]-(len[lca(u,v)]<<1)+len[v];
	}
	inline int go(int u,int k){
		for(int j=ldep[u];j>=0;j--){
			if((k>>j)&1){
				u=fa[u][j];
			}
		}
		return u;
	}
	inline int go(int u,int v,int k){
		int w=lca(u,v);
		if(dep[u]-dep[w]>=k){
			return go(u,k);
		}
		return go(v,dep[u]+dep[v]-(dep[w]<<1)-k);
	}
}T;
int main(){
	for(int tot=ni;tot--;){
		T.reset();
		int n=ni;
		for(int i=1;i<n;i++){
			int u=ni,v=ni,w=ni;
			T.add_edge(u,v,w);
			T.add_edge(v,u,w);
		}
		T.dfs(1,0);
		char op[10];
		while(scanf("%s",op),op[1]!='O'){
			if(op[0]=='D'){
				printf("%d\n",T.dist(ni,ni));
			}else{
				int x=ni,y=ni,k=ni;
				printf("%d\n",T.go(x,y,k-1));
			}
		}
	}
}
