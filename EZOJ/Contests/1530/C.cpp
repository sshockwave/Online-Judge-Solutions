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
const int N=1000010;
lint a[N];
inline int acmp(int i,int j){
	return a[i]!=a[j]?a[i]<a[j]:i<j;
}
inline int amax(int i,int j){
	return acmp(j,i)?i:j;
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mxpos;
		lint v2;
		inline void up(){
			mxpos=amax(lson->mxpos,rson->mxpos);
			v2=max(lson->v2,rson->v2);
		}
	}pool[N<<1];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->mxpos=x->m;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	int ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mxpos;
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return amax(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r));
	}
	void upd_pos(node x,int p){
		if(x->l!=x->r){
			upd_pos(p<=x->m?x->lson:x->rson,p);
			x->up();
		}
	}
	void upd_v2(node x,int p,lint v){
		if(x->l==x->r){
			x->v2=v;
		}else{
			upd_v2(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	int prbig(node x,int p){
		const int FAIL=x->l-1;
		if(p<=x->l)return FAIL;
		if(!acmp(p,x->mxpos))return FAIL;
		if(x->l==x->r)return x->m;
		if(p<=x->m+1)return prbig(x->lson,p);
		const int ans=prbig(x->rson,p);
		return ans>x->m?ans:prbig(x->lson,p);
	}
	int nxbig(node x,int p){
		const int FAIL=x->r+1;
		if(p>=x->r)return FAIL;
		if(!acmp(p,x->mxpos))return FAIL;
		if(x->l==x->r)return x->m;
		if(p>=x->m)return nxbig(x->rson,p);
		const int ans=nxbig(x->lson,p);
		return ans<=x->m?ans:nxbig(x->rson,p);
	}
}
seg::node rt;
int n,k;
inline void work(int x){
	lint v=0;
	if(x>1){
		const int xl=seg::prbig(rt,x);
		if(xl+1<x){
			apmax(v,a[seg::ask(rt,max(x-k,xl+1),x-1)]);
		}
	}
	if(x<n){
		const int xr=seg::nxbig(rt,x);
		if(xr-1>x){
			apmax(v,a[seg::ask(rt,x+1,min(x+k,xr-1))]);
		}
	}
	seg::upd_v2(rt,x,a[x]+v);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	n=ni,k=ni;
	int tot=ni,tp=ni;
	for(int i=1;i<=n;i++){
		a[i]=next_num<lint>();
	}
	rt=seg::build(1,n);
	for(int i=1;i<=n;i++){
		work(i);
	}
	for(;printf("%lld\n",rt->v2),tot--;){
		const int x=next_num<lint>()^(tp*rt->v2);
		a[x]=next_num<lint>()^(tp*rt->v2);
		seg::upd_pos(rt,x);
		work(x);
		work(seg::ask(rt,max(1,x-k),x));
		work(seg::ask(rt,x,min(n,x+k)));
	}
	return 0;
}
