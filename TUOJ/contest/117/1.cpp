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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
int a[N],pos[N];
int end_l[N<<1],end_r[N<<1];
namespace G2{
	const int N=::N<<1,E=::N*40;
	int to[E],bro[E],head[N],e=0;
	int ind[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(ind+1,0,n);
	}
	inline void ae(int u,int v){
		++ind[v],to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int que[N];
	void topsort(int n){
		int qh=0,qt=0;
		for(int i=1;i<=n;i++){
			if(ind[i]==0){
				que[qt++]=i;
			}
		}
		for(;qh<qt;){
			const int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(--ind[v=to[i]]==0){
					que[qt++]=v;
				}
				apmin(end_l[v],end_l[x]);
				apmax(end_r[v],end_r[x]);
			}
		}
	}
}
namespace G{
	const int N=::N<<1,E=::N*40;
	int fr[E],to[E],bro[E],head[N],e=0;
	int dfn[N],low[N],bln[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(dfn+1,0,n);
	}
	inline void ae(int u,int v){
		fr[e]=u,to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void dfs(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				dfs(v);
				apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],dfn[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--ss],instk[v]=false;
				bln[v]=x;
			}while(v!=x);
		}
	}
	void main(const int n){
		for(int i=1;i<=n;i++){
			if(dfn[i]==0){
				dfs(i);
			}
		}
		for(int i=1;i<=n;i++){
			apmin(end_l[bln[i]],end_l[i]);
			apmax(end_r[bln[i]],end_r[i]);
		}
		G2::init(n);
		for(int i=0;i<e;i++){
			if(bln[fr[i]]!=bln[to[i]]){
				G2::ae(bln[to[i]],bln[fr[i]]);
			}
		}
		G2::topsort(n);
	}
}
namespace seg{
	const int N=::N<<1;
	inline int idx(int l,int r){
		return (l+r)|(l!=r);
	}
	int build(int l,int r){
		const int x=idx(l,r);
		end_l[x]=l,end_r[x]=r+1;
		if(l!=r){
			const int m=(l+r)>>1;
			G::ae(x,build(l,m));
			G::ae(x,build(m+1,r));
		}
		return x;
	}
	void ask(int l,int r,int a,int b,int &mn,int &mx){
		const int x=idx(l,r);
		if(l==a&&r==b){
			apmin(mn,end_l[G::bln[x]]);
			apmax(mx,end_r[G::bln[x]]);
			return;
		}
		const int m=(l+r)>>1;
		if(b<=m)return ask(l,m,a,b,mn,mx);
		if(a>m)return ask(m+1,r,a,b,mn,mx);
		ask(l,m,a,m,mn,mx);
		ask(m+1,r,m+1,b,mn,mx);
	}
	void add_edge(int l,int r,int y,int a,int b){
		const int x=idx(l,r);
		if(l==a&&r==b)return G::ae(y,x);
		const int m=(l+r)>>1;
		if(b<=m)return add_edge(l,m,y,a,b);
		if(a>m)return add_edge(m+1,r,y,a,b);
		add_edge(l,m,y,a,m);
		add_edge(m+1,r,y,m+1,b);
	}
}
namespace seg2{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,mx;
		inline void up(){
			mn=min(lson->mn,rson->mn);
			mx=max(lson->mx,rson->mx);
		}
	}pool[N<<1];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->mn=x->mx=pos[l];
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void ask(node x,int l,int r,int &mn,int &mx){
		if(x->l==l&&x->r==r){
			apmin(mn,x->mn);
			apmax(mx,x->mx);
			return;
		}
		if(r<=x->m)return ask(x->lson,l,r,mn,mx);
		if(l>x->m)return ask(x->rson,l,r,mn,mx);
		ask(x->lson,l,x->m,mn,mx);
		ask(x->rson,x->m+1,r,mn,mx);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		pos[a[i]=ni]=i;
	}
	if(n==1){
		for(int tot=ni;tot--;){
			puts("1 1");
		}
		return 0;
	}
	G::init(n*2);
	seg::build(1,n-1);
	const seg2::node rt2=seg2::build(1,n);
	for(int i=1;i<n;i++){
		int l=i,r=i+1;
		seg2::ask(rt2,min(a[i],a[i+1]),max(a[i],a[i+1]),l,r);
		seg::add_edge(1,n-1,seg::idx(i,i),l,r-1);
	}
	G::main(n*2);
	for(int tot=ni,tp=ni,l=0,r=0;tot--;){
		l=ni^(tp*l),r=ni^(tp*r);
		if(l<r){
			seg::ask(1,n-1,l,r-1,l,r);
		}
		printf("%d %d\n",l,r);
	}
	return 0;
}
