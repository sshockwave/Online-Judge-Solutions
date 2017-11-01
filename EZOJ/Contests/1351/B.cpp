#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],dep[N],size[N],top[N];
	int dfn[N],idx[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		fa[1]=size[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		dep[x]=dep[fa[x]]+1;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	void dfs2(int x){
		idx[dfn[x]=++tim]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]){
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					dfs2(v);
				}
			}
		}
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline int fly(int x,int n){
		assert(x);
		for(int d;d=dep[x]-dep[fa[top[x]]],d<=n;n-=d,x=fa[top[x]]);
		return idx[dfn[x]-n];
	}
	inline int work(int u,int v,int n){
		if(u==v){
			return n;
		}
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		int w=lca(u,v);
		int dis=dep[u]+dep[v]-(dep[w]<<1);
		if(dis&1){
			return 0;
		}
		dis>>=1;
		assert(dis);
		if(dep[u]-dep[w]==dis){
			u=fly(u,dis-1);
			v=fly(v,dis-1);
			assert(u!=v&&fa[u]==fa[v]);
			return n-size[u]-size[v];
		}
		int p=fly(u,dis-1);
		return size[fa[p]]-size[p];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("equal.in","r",stdin);
	freopen("equal.out","w",stdout);
#endif
	T::init();
	int n=ni;
	for(int i=1;i<n;T::add(ni,ni),i++);
	T::dfs1(1),T::dfs2(1);
	for(int tot=ni;tot--;printf("%d\n",T::work(ni,ni,n)));
	return 0;
}
