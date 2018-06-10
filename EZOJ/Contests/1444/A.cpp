#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=100010;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		lint sum,dt;
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->sum=x->dt=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void add(node x,int l,int r,int v){
		assert(v==1||v==-1);
		x->sum+=(r-l+1)*v;
		if(x->l==l&&x->r==r){
			x->dt+=v;
		}else if(r<=x->m)return add(x->lson,l,r,v);
		else if(l>x->m)return add(x->rson,l,r,v);
		else{
			add(x->lson,l,x->m,v);
			add(x->rson,x->m+1,r,v);
		}
	}
	lint ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->sum;
		const lint dt=(lint)(r-l+1)*x->dt;
		if(r<=x->m)return ask(x->lson,l,r)+dt;
		if(l>x->m)return ask(x->rson,l,r)+dt;
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r)+dt;
	}
}
seg::node rt;
struct intv{
	int l,r;
	inline friend bool operator < (const intv &a,const intv &b){
		return a.l<b.l;
	}
	inline void alt(int v)const{
		seg::add(rt,l,r,v);
	}
};
typedef set<intv>si;
typedef si::iterator iter;
inline void cov(si &s,int l,int r){
	iter it=s.lower_bound((intv){l,r});
	iter pr=it;
	pr--;
	if(pr->r>=l-1){
		l=pr->l;
		apmax(r,pr->r);
		pr->alt(-1),s.erase(pr);
	}
	for(iter nx;it->l<=r+1;it=nx){
		apmax(r,it->r);
		nx=it,++nx;
		it->alt(-1),s.erase(it);
	}
	const intv tmp=(intv){l,r};
	tmp.alt(1),s.insert(tmp);
}
si st[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("confidence.in","r",stdin);
	freopen("confidence.out","w",stdout);
#endif
	const int n=ni;
	rt=seg::build(0,n);
	for(int i=0;i<=n;i++){
		st[i].insert((intv){-1,-1});
		st[i].insert((intv){n+2,n+2});
	}
	for(int tot=ni;tot--;){
		const int op=ni,l=ni,r=ni;
		if(op==0){
			cov(st[ni],l,r);
		}else{
			printf("%lld\n",seg::ask(rt,l,r));
		}
	}
	return 0;
}
