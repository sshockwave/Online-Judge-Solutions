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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		unsigned mx,orsum,v;
		inline void operator |=(unsigned t){
			assert((v&t)==0);
			mx|=t,orsum|=t,v|=t;
		}
		inline void operator &=(unsigned t){
			mx&=t,orsum&=t,v&=t;
		}
		inline void up();
		inline void dn(){
			*lson|=v,*rson|=v,v=0;
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->mx=x->orsum=x->v=next_num<unsigned>();
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->v=0,x->up();
		}
		return x;
	}
	void alt_and(node x,unsigned v){
		unsigned t=~((x->orsum^x->v)&~v);
		*x&=v,v=t;
		if(v==~0u)return;
		alt_and(x->lson,v);
		alt_and(x->rson,v);
		x->up();
	}
	void alt_and(node x,int l,int r,unsigned v){
		v=~(x->orsum&~v);
		if(v==~0u)return;
		if(x->l==l&&x->r==r)return alt_and(x,v);
		x->dn();
		if(r<=x->m){
			alt_and(x->lson,l,r,v);
		}else if(l>x->m){
			alt_and(x->rson,l,r,v);
		}else{
			alt_and(x->lson,l,x->m,v);
			alt_and(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	void alt_or(node x,int l,int r,unsigned v){
		v&=~x->v;
		if(v==0)return;
		if(x->l==l&&x->r==r)return alt_and(x,~v),*x|=v;
		if(r<=x->m){
			alt_or(x->lson,l,r,v);
		}else if(l>x->m){
			alt_or(x->rson,l,r,v);
		}else{
			alt_or(x->lson,l,x->m,v);
			alt_or(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	void Node::up(){
		assert(l!=r);
		if(lson->v&rson->v){
			const unsigned t=lson->v&rson->v;
			alt_and(lson,~t),alt_and(rson,~t);
			v|=t;
		}
		mx=max(lson->mx,rson->mx)|v;
		orsum=lson->orsum|rson->orsum|v;
		assert((v&(lson->orsum|rson->orsum))==0);
	}
	unsigned ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mx;
		if(r<=x->m)return ask(x->lson,l,r)|x->v;
		if(l>x->m)return ask(x->rson,l,r)|x->v;
		return max(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r))|x->v;
	}
	void dfs(node x){
		if(x==0)return;
		cout<<"["<<x->l<<","<<x->r<<"]:mx="<<x->mx<<",orsum="<<x->orsum<<",v="<<x->v<<endl;
		dfs(x->lson);
		dfs(x->rson);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int n=ni,q=ni;
	seg::node rt=seg::build(1,n);
	while(q--){
		int op=ni,l=ni,r=ni;
		if(op==3){
			printf("%u\n",seg::ask(rt,l,r));
		}else{
			unsigned x=next_num<unsigned>();
			if(op==1){
				alt_and(rt,l,r,x);
			}else{
				alt_or(rt,l,r,x);
			}
		}
	}
	return 0;
}
