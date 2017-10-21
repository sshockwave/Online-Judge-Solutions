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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=200010,INF=0x7f7f7f7f;
int ans=0;
namespace T{
	const int E=N<<2;
	int to[E],bro[E],mhead[N],dhead[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],idx[N],tim=0;
	inline void init(){
		memset(mhead,-1,sizeof(mhead));
		memset(dhead,-1,sizeof(dhead));
	}
	inline void ae(int u,int v,int *head){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v,int *head){
		ae(u,v,head),ae(v,u,head);
	}
	void dfs1(int x){
		size[x]=1;
		for(int i=mhead[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs1(v);
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
			for(int i=mhead[x],v;~i;i=bro[i]){
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
	inline int dis(int u,int v){
		return dep[u]+dep[v]-(dep[lca(u,v)]<<1);
	}
	inline int fly(int x,int n){
		int d=dep[x]-n;
		for(;dep[top[x]]>d;x=fa[top[x]]);
		return idx[dfn[x]-(dep[x]-d)];
	}
	inline int chase(int u,int v){
		return u==v?u:lca(u,v)==u?fly(v,dep[v]-dep[u]-1):fa[u];
	}
	int rel[N];
	void dfs3(int x,int fa,int dep){
		apmax(ans,dep+dis(x,rel[x]));
		if(rel[x]==x){
			return;
		}
		for(int i=dhead[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				if(dis(v,x)>2){
					throw -1;
				}
				rel[v]=chase(rel[x],v);
				dfs3(v,x,dep+1);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("deer.in","r",stdin);
	freopen("deer.out","w",stdout);
#endif
	int n=ni,rt=ni;
	T::rel[rt]=ni;
	T::init();
	for(int i=1;i<n;T::add(ni,ni,T::dhead),i++);
	for(int i=1;i<n;T::add(ni,ni,T::mhead),i++);
	T::dfs1(1),T::dfs2(1);
	try{
		T::dfs3(rt,0,0);
		printf("%d\n",ans<<1);
	}catch(int ans){
		printf("%d\n",ans);
	}
	return 0;
}
