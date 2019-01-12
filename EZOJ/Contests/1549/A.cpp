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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(b));}
const int N=1e5+10,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
int a[N],soncnt[N],sump[N];
lint sumg[N];
int idx[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int a,b;//f=a*x+b
		inline void up(){
			a=(lint)lson->a*rson->a%O;
			b=((lint)lson->a*rson->b+lson->b)%O;
		}
		inline void getinfo(){
			const int x=idx[m];
			a=inv_pow(sump[x]+1),b=((lint)(soncnt[x]+1)*::a[x]+sumg[x])%O*a%O;
		}
	}pool[N<<1];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->getinfo();
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void alt_upd(node x,int p){
		if(x->l==x->r){
			x->getinfo();
		}else{
			alt_upd(p<=x->m?x->lson:x->rson,p);
			x->up();
		}
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],siz[N],top[N],dfn[N],dfe[N],tim=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int p[N];
	void dfs1(int x){
		soncnt[x]=0;
		sump[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x])continue;
			fa[v]=x;
			dfs1(v);
			++soncnt[x];
			sump[x]=(sump[x]+p[v])%O;
		}
		if(soncnt[x]){
			p[x]=(lint)sump[x]*inv_pow(sump[x]+1)%O;
		}else{
			p[x]=1;
		}
	}
	void dfs2(int x){
		siz[x]=1;
		son[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x])continue;
			dfs2(v);
			siz[x]+=siz[v];
			if(siz[v]>siz[son[x]]){
				son[x]=v;
			}
		}
	}
	seg::node rt[N];
	void dfs3(int x){
		sumg[x]=0;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dfn[x]=++tim,idx[tim]=x;
		if(son[x]){
			dfs3(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])==fa[x]||v==son[x])continue;
				dfs3(v);
			}
		}else{
			dfe[top[x]]=dfn[x];
		}
		if(x==top[x]){
			rt[x]=seg::build(dfn[x],dfe[x]);
			if(fa[x]){
				sumg[fa[x]]+=rt[x]->b;
			}
		}
	}
	inline void upd(int x){
		for(;x;x=fa[top[x]]){
			if(fa[top[x]]){
				sumg[fa[top[x]]]-=rt[top[x]]->b;
			}
			seg::alt_upd(rt[top[x]],dfn[x]);
			if(fa[top[x]]){
				sumg[fa[top[x]]]+=rt[top[x]]->b;
			}
		}
	}
}
inline int getans(){
	using namespace T;
	return (rt[1]->b-(lint)(1-p[1])*a[1])%O*inv_pow(p[1])%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("satisfy.in","r",stdin);
	freopen("satisfy.out","w",stdout);
#endif
	const int n=ni;
	T::init(n);
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::fa[1]=0,T::siz[0]=0,T::son[0]=0;
	T::dfs1(1),T::dfs2(1),T::dfs3(1);
	for(int tot=ni;printf("%d\n",getans()),tot--;){
		int u=ni;
		a[u]=ni;
		T::upd(u);
	}
	return 0;
}
