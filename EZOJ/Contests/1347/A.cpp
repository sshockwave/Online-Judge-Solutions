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
int n;
lint calc(int n){
	lint tmp=n;
	tmp*=(n-1);
	tmp/=2;
	return tmp+n;
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],idx[N],tim=0;
	lint f[N],g[N],h[N],hsum[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(f,0,sizeof(f));
		memset(son,0,sizeof(son));
		fa[1]=0,g[1]=0,dep[1]=1;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		dep[x]=dep[fa[x]]+1;
		size[x]=f[x]=1;
		h[x]=calc(n);
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				f[x]+=f[v]+size[v];
				h[x]-=calc(size[v]);
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
		h[x]-=calc(n-size[x]);
	}
	void dfs2(int x){
		idx[dfn[x]=++tim]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		hsum[x]=h[x];
		if(son[x]){
			g[son[x]]=g[x]+(n-size[x])+f[x]-(f[son[x]]+size[son[x]]);
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					g[v]=g[x]+(n-size[x])+f[x]-(f[v]+size[v]);
					dfs2(v);
				}
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]){
					hsum[x]+=f[v]*(n-size[v]);
				}
			}
		}
		hsum[x]+=g[x]*size[x];
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline int fly(int x,int n){
		assert(n>=0);
		for(int d;d=dep[x]-dep[fa[top[x]]],d<=n;n-=d,x=fa[top[x]]);
		return idx[dfn[x]-n];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("happy.in","r",stdin);
	freopen("happy.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	T::dfs1(1),T::dfs2(1);
	while(tot--){
		using namespace T;
		int u=ni,v=ni,w=lca(u,v);
		if(u==v){
			printf("%.7Lf\n",((long double)hsum[u]/h[u]));
			continue;
		}
		int dis=dep[u]+dep[v]-(dep[w]<<1);
		if(dep[u]>dep[v]){
			swap(u,v);
		}
		if(u==w){
			int s=fly(v,dep[v]-dep[u]-1);
			assert(fa[s]==u);
			printf("%.7Lf\n",(dis-1+(long double)g[s]/(n-size[s])+(long double)f[v]/size[v]));
		}else{
			printf("%.7Lf\n",(dis-1+(long double)f[u]/size[u]+(long double)f[v]/size[v]));
		}
	}
	return 0;
}
