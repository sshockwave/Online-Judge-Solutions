#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=100010,C=1000010,INF=0x7f7f7f7f;
int pval[N],ett[N<<1];
bool vis[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	typedef int arr[N];
	arr fa,son,size,dep,top;
	arr dfn,dfe;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int tim=0;
	void dfs(int x){
		ett[dfn[x]=++tim]=x;
		son[x]=0,size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
		ett[dfe[x]=++tim]=x;
	}
	inline void prep(){
		for(int i=1;i<=tim;i++){
			int x=ett[i];
			top[x]=son[fa[x]]==x?top[fa[x]]:x;
		}
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
}
struct Query{
	int l,r,k,ext,ans;
}q[N];
int lst[N],rt;
inline bool lcmp(int a,int b){
	int al=q[a].l/rt,bl=q[b].l/rt;
	return al!=bl?al<bl:q[a].r<q[b].r;
}
int cnt[C],sum[N];
inline void alt(int x){
	if(vis[x]){
		sum[cnt[pval[x]]--]--;
	}else{
		sum[++cnt[pval[x]]]++;
	}
	vis[x]=!vis[x];
}
inline int scan(int l,int r,int v){
	while(l<r){
		int m=((l+r)>>1)+1;
		if(sum[m]>=v){
			l=m;
		}else{
			r=m-1;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(1),T::prep();
	for(int i=1;i<=tot;i++){
		lst[i]=i;
		int u=ni,v=ni;
		if(T::dfn[u]<=T::dfn[v]&&T::dfe[v]<=T::dfe[u]){
			q[i]=(Query){T::dfn[u],T::dfn[v],ni,0};
		}else{
			if(T::dfn[u]>T::dfn[v]){
				swap(u,v);
			}
			q[i]=(Query){T::dfe[u],T::dfn[v],ni,T::lca(u,v)};
		}
	}
	for(rt=0;rt*rt<tot;rt++);
	sort(lst+1,lst+tot+1,lcmp);
	memset(vis,0,sizeof(vis));
	memset(sum,0,sizeof(sum));
	memset(cnt,0,sizeof(cnt));
	sum[0]=INF;
	alt(ett[1]);
	for(int i=1,l=1,r=1;i<=tot;i++){
		const Query &cur=q[lst[i]];
		for(;l<cur.l;alt(ett[l++]));
		for(;r>cur.r;alt(ett[r--]));
		for(;l>cur.l;alt(ett[--l]));
		for(;r<cur.r;alt(ett[++r]));
		if(cur.ext){
			alt(cur.ext);
		}
		q[lst[i]].ans=scan(0,n,cur.k);
		assert(cur.ans==q[lst[i]].ans);
		if(cur.ext){
			alt(cur.ext);
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",q[i].ans);
	}
	return 0;
}
