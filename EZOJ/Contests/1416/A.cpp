#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=100010;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,cnt,dt;
		inline void dn(){
			if(dt){
				lson->mn+=dt,lson->dt+=dt;
				rson->mn+=dt,rson->dt+=dt;
				dt=0;
			}
		}
		inline void up(){
			assert(dt==0);
			mn=min(lson->mn,rson->mn);
			cnt=0;
			if(lson->mn==mn){
				cnt+=lson->cnt;
			}
			if(rson->mn==mn){
				cnt+=rson->cnt;
			}
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->mn=0,x->cnt=1,x->dt=0;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void add(node x,int l,int r,int v){
		if(x->l==l&&x->r==r){
			x->mn+=v,x->dt+=v;
			return;
		}
		x->dn();
		if(r<=x->m){
			add(x->lson,l,r,v);
		}else if(l>x->m){
			add(x->rson,l,r,v);
		}else{
			add(x->lson,l,x->m,v);
			add(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	int ask(node x,int l,int r){
		if(x->mn>0)return 0;
		if(x->l==l&&x->r==r)return x->cnt;
		x->dn();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
int n;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int cnt[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(cnt,0,sizeof(cnt));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int fa[N],son[N],size[N],dep[N],top[N],dfn[N],dfe[N],idx[N],tim=0;
	void dfs1(int x){
		size[x]=1;
		dep[x]=dep[fa[x]]+1;
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
		dfe[x]=tim;
	}
	inline int fly(int x,int n){
		for(int d;d=dep[x]-dep[fa[top[x]]],d<=n;x=fa[top[x]],n-=d);
		return idx[dfn[x]-n];
	}
}
struct Query{
	int y,l,r,v;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.y<b.y;
	}
}qry[N*40];
int qs=0;
inline void add_op(int x1,int x2,int y1,int y2){
	if(x1>x2||y1>y2)return;
	qry[++qs]=(Query){y1,x1,x2,1};
	qry[++qs]=(Query){y2+1,x1,x2,-1};
}
inline void add_op(int x,int y){
	using namespace T;
	if(dfn[x]>dfn[y]){
		swap(x,y);
	}
	if(dfn[x]<=dfn[y]&&dfn[y]<=dfe[x]){
		int z=fly(y,dep[y]-dep[x]-1);
		add_op(1,dfn[z]-1,dfn[y],dfe[y]);
		add_op(dfn[y],dfe[y],dfe[z]+1,n);
	}else{
		add_op(dfn[x],dfe[x],dfn[y],dfe[y]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	n=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	for(int i=1;i<=n;i++){
		for(int j=i<<1;j<=n;j+=i){
			add_op(i,j);
		}
	}
	sort(qry+1,qry+qs+1);
	seg::node rt=seg::build(1,n);
	lint ans=0;
	for(int v=1,j=1;v<=n;v++){
		for(;j<=qs&&qry[j].y==v;j++){
			seg::add(rt,qry[j].l,qry[j].r,qry[j].v);
		}
		if(v>1){
			ans+=seg::ask(rt,1,v-1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
