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
lint a[N],f[N];
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
			x->v2=0;
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
	void upd(node x,int p){
		if(x->l==x->r){
			x->v2=f[x->m];
		}else{
			upd(p<=x->m?x->lson:x->rson,p);
			x->up();
		}
	}
}
seg::node rt;
int n,k;
struct pii{
	int l,r;
};
inline pii getp(int x){
	const int tl=max(1,x-k),tr=min(n,x+k);
	pii ans;
	ans.l=tl<x?seg::ask(rt,tl,x-1):0;
	ans.r=x<tr?seg::ask(rt,x+1,tr):0;
	return ans;
}
inline void setf(int x,lint v){
	if(v!=f[x]){
		f[x]=v,seg::upd(rt,x);
	}
}
inline void work(int x){
	pii pp=getp(x);
	const int p=amax(pp.l,pp.r);
	setf(x,acmp(p,x)?a[p]+a[x]:0);
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
		const pii xx=getp(x);
		int p=amax(xx.l,xx.r);
		if(acmp(p,x)){
			setf(xx.l,0),setf(xx.r,0);
			f[x]=a[x]+a[p],seg::upd(rt,x);
		}else{
			f[x]=0,seg::upd(rt,x);
			work(xx.l),work(xx.r);
		}
	}
	return 0;
}
