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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,D=3;
namespace G{
	const int N=::N*20*3,E=N*2+::N*20*3;//cout
	int fr[E],to[E],bro[E],head[N],e=0,n=0;
	int dfn[N],low[N],tim=0;
	int bln[N];
	int stk[N],ss=0;
	bool instk[N];
	inline int nn(){
		++n;
		head[n]=-1;
		dfn[n]=0;
		instk[n]=false;
		return n;
	}
	inline void ae(int u,int v){
		if(u==0||v==0)return;
		fr[e]=u,to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void tarjan(const int &x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				tarjan(v);
				apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],dfn[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--ss];
				instk[v]=false;
				bln[v]=x;
			}while(x!=v);
		}
	}
}
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int nd;
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
	void reset(node x){
		x->nd=0;
		if(x->l!=x->r){
			reset(x->lson);
			reset(x->rson);
		}
	}
	inline void cov(node x,int p,int v){//cov <= p
		while(true){
			if(x->nd==0)return;
			if(p==x->r)return G::ae(v,x->nd);
			if(p>x->m){
				G::ae(v,x->lson->nd);
				x=x->rson;
			}else{
				x=x->lson;
			}
		}
	}
	void ins(node x,int p,int v){
		if(x->l==x->r){
			assert(x->nd==0);
			x->nd=v;
		}else{
			ins(p<=x->m?x->lson:x->rson,p,v);
			x->nd=G::nn();
			G::ae(x->nd,x->lson->nd);
			G::ae(x->nd,x->rson->nd);
		}
	}
}
int lst[D][N],rnk[D][N],n;
template<int x>inline bool rnk_cmp(int a,int b){
	return rnk[x][a]<rnk[x][b];
}
template<int x>inline void rnk_init(){
	sort(lst[x]+1,lst[x]+n+1,rnk_cmp<x>);
	for(int i=1;i<=n;i++){
		rnk[x][lst[x][i]]=i;
	}
}
template<int a,int b>inline void build_G(){
	seg::reset(seg::rt);
	for(int i=1;i<=n;i++){
		const int x=lst[a][i];
		const int r=rnk[b][x];
		seg::cov(seg::rt,r,x);
		seg::ins(seg::rt,r,x);
	}
}
bool ind[G::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("san.in","r",stdin);
	freopen("san.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		G::nn();
		for(int j=0;j<D;j++){
			lst[j][i]=i,rnk[j][i]=ni;
		}
	}
	rnk_init<0>();
	rnk_init<1>();
	rnk_init<2>();
	seg::rt=seg::build(1,n);
	build_G<0,1>();
	build_G<1,2>();
	build_G<2,0>();
	for(int i=1;i<=n;i++){
		if(G::dfn[i]==0){
			G::tarjan(i);
		}
	}
	using G::bln;
	memset(ind,0,sizeof(ind));
	for(int i=0;i<G::e;i++){
		using namespace G;
		if(dfn[fr[i]]&&bln[fr[i]]!=bln[to[i]]){
			ind[bln[to[i]]]=true;
		}
	}
	for(int i=1;i<=n;i++){
		putchar('0'+!ind[bln[i]]),putchar('\n');
	}
	return 0;
}
