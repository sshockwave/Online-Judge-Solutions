#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,INF=0x7f7f7f7f;
multiset<int>edgset[N];
int iskey[N],keytim=0;
namespace T2{
	const int E=::N<<1;
	int to[E],bro[E],val[E],head[N],e;
	int tag[N],tim=0;
	inline void init(){
		++tim,e=0;
	}
	inline void ae(int u,int v,int w){
		if(tag[u]<tim){
			tag[u]=tim,head[u]=-1;
		}
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		assert(u&&v);
		assert(u!=v);
		ae(u,v,w),ae(v,u,w);
	}
	int f[E];//closest key point distance
	int tofa[N];
	void dfs1(int,int);
	void dfs2(int,int);
}
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mx1,mx2;//mx1:t+d mx2:t-d
		inline void up(){
			mx1=max(lson->mx1,rson->mx1);
			mx2=max(lson->mx2,rson->mx2);
		}
	}pool[N];
	node rt;
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void set(node x,int p,int v1,int v2){
		if(x->l==x->r){
			x->mx1=v1,x->mx2=v2;
		}else{
			set(p<=x->m?x->lson:x->rson,p,v1,v2);
			x->up();
		}
	}
	int ask1(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mx1;
		if(r<=x->m)return ask1(x->lson,l,r);
		if(l>x->m)return ask1(x->rson,l,r);
		return max(ask1(x->lson,l,x->m),ask1(x->rson,x->m+1,r));
	}
	int ask2(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mx2;
		if(r<=x->m)return ask2(x->lson,l,r);
		if(l>x->m)return ask2(x->rson,l,r);
		return max(ask2(x->lson,l,x->m),ask2(x->rson,x->m+1,r));
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int fa[N],son[N],size[N],dep[N],top[N],dfn[N],idx[N],tim=0;
	int tofa[N];
	int f[E];
	void dfs1(int x){
		son[x]=0;
		size[x]=1;
		dep[x]=dep[fa[x]]+1;
		if(fa[x]){
			f[tofa[x]^1]=1;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x,tofa[v]=i^1;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
				if(fa[x]){
					apmax(f[tofa[x]^1],f[i]+1);
				}
			}
		}
	}
	void dfs2(int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		idx[dfn[x]=++tim]=x;
		int mx1=0,mx2=0,mxp1=-1;
		for(int i=head[x];~i;i=bro[i]){
			if(f[i]>mx1){
				mx2=mx1,mx1=f[i];
				mxp1=i;
			}else if(f[i]>mx2){
				mx2=f[i];
			}
			edgset[x].insert(f[i]);
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				f[i^1]=(i!=mxp1?mx1:mx2)+1;
			}
		}
		if(fa[x]){
			multiset<int>&fs=edgset[fa[x]];
			fs.erase(fs.find(f[tofa[x]^1]));
			if(fa[fa[x]]){
				fs.erase(fs.find(f[tofa[fa[x]]]));
			}
			int t=!fs.empty()?*fs.rbegin():0;
			seg::set(seg::rt,dfn[x],t+dep[fa[x]],t-dep[fa[x]]);
			if(fa[fa[x]]){
				fs.insert(f[tofa[fa[x]]]);
			}
			fs.insert(f[tofa[x]^1]);
		}
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
	int lst[N];
	inline bool lcmp(int a,int b){
		return dfn[a]<dfn[b];
	}
	int stk[N],ss;
	inline void pshstk(int x){
		for(;dep[stk[ss]]>dep[x];){
			int u=stk[ss--];
			if(dep[stk[ss]]<dep[x]){
				stk[++ss]=x;
			}
			T2::add(stk[ss],u,dep[u]-dep[stk[ss]]);
		}
		if(x!=stk[ss]){
			stk[++ss]=x;
		}
	}
	inline int build_aux(int n){
		sort(lst+1,lst+n+1,lcmp);
		ss=0;
		stk[0]=0;
		stk[++ss]=lst[1];
		T2::init();
		keytim++;
		for(int i=1;i<=n;i++){
			iskey[lst[i]]=keytim;
		}
		for(int i=2;i<=n;i++){
			int u=stk[ss],v=lst[i],w=lca(u,v);
			pshstk(w),pshstk(v);
		}
		for(;ss>1;pshstk(stk[ss-1]));
		return stk[1];
	}
	inline int jmp(int x,int n){
		for(int d;d=dep[x]-dep[fa[top[x]]],d<=n;n-=d,x=fa[top[x]]);
		return idx[dfn[x]-n];
	}
	inline int stval(int x,int v){//x and y is on the same chain
		if(dep[v]<dep[x])return f[tofa[x]];
		return f[tofa[jmp(v,dep[v]-dep[x]-1)]^1];
	}
	template<int(*ask)(seg::node,int,int)>inline int flyask(int x,int d,int d2){
		if(d>d2)return -INF;
		int ans=-INF;
		assert(dep[x]>=d2);
		x=jmp(x,dep[x]-d2);
		for(;dep[fa[top[x]]]>=d;x=fa[top[x]]){
			apmax(ans,ask(seg::rt,dfn[top[x]],dfn[x]));
		}
		apmax(ans,ask(seg::rt,dfn[x]-(dep[x]-d),dfn[x]));
		return ans;
	}
}
int ans;
void T2::dfs1(int x,int fa){
	if(fa){
		f[tofa[x]^1]=INF;
	}
	if(tag[x]<tim){
		head[x]=-1,tag[x]=tim;
	}
	for(int i=head[x],v;~i;i=bro[i]){
		if((v=to[i])!=fa){
			tofa[v]=i^1;
			dfs1(v,x);
			if(fa){
				apmin(f[tofa[x]^1],f[i]+val[tofa[x]]);
			}
		}
	}
	if(fa&&iskey[x]==keytim){
		f[tofa[x]^1]=val[tofa[x]];
	}
	if(fa){
		assert(f[tofa[x]^1]<INF);
	}
}
void T2::dfs2(int x,int fa){
	multiset<int>&es=edgset[x];
	int mn1=INF,mn2=INF,mnp=-1;
	using T::stval;
	for(int i=head[x];~i;i=bro[i]){
		es.erase(es.find(stval(x,to[i])));
		if(f[i]<mn1){
			mn2=mn1,mn1=f[i],mnp=i;
		}else if(f[i]<mn2){
			mn2=f[i];
		}
	}
	if(iskey[x]==keytim){
		mn1=0,mnp=-1;
	}else{
		apmax(ans,mn1);
	}
	if(!es.empty()){
		assert(mn1<INF);
		apmax(ans,mn1+*es.rbegin());
	}
	for(int i=head[x];~i;i=bro[i]){
		es.insert(stval(x,to[i]));
	}
	if(mn2==INF){
		mn2=0;
	}
	for(int i=head[x],v;~i;i=bro[i]){
		if((v=to[i])!=fa){
			f[i^1]=(mnp!=i?mn1:mn2)+val[i];
			dfs2(v,x);
		}
	}
	if(fa){//on chain
		int da=T::dep[x]-f[tofa[x]];
		int db=T::dep[fa]+f[tofa[x]^1];
		apmax(ans,T::flyask<seg::ask1>(x,T::dep[fa]+2,min(((da+db)>>1)+1,T::dep[x]))-da);
		apmax(ans,T::flyask<seg::ask2>(x,max(((da+db+1)>>1)+1,T::dep[fa]+2),T::dep[x])+db);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("do.in","r",stdin);
	freopen("do.out","w",stdout);
#endif
	int n=ni,tot=ni;
	seg::rt=seg::build(1,n);
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	while(tot--){
		int ls=ni;
		for(int i=1;i<=ls;i++){
			T::lst[i]=ni;
		}
		if(ls==1){
			printf("%d\n",n>1?*edgset[T::lst[1]].rbegin():0);
		}else{
			int rt=T::build_aux(ls);
			ans=0;
			T2::dfs1(rt,0),T2::dfs2(rt,0);
			printf("%d\n",ans);
		}
	}
	return 0;
}
