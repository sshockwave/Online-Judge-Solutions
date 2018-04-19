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
const int N=100010,INF=0x7f7f7f7f;
int a[N],n;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mx,ans;
		int lv,rv;
		bool tag;
		inline void gans(){
			ans=max(lv,max(rv,mx)+n)+l-1;
		}
		inline void cov(int lt,int rt){
			lv=lt,rv=rt;
			assert(mx<=lv);
			assert(mx<=rv);
			ans=max(lv,rv+n)+l-1;
			tag=true;
		}
		inline void dn(){
			if(tag){
				assert(mx==max(lson->mx,rson->mx));
				assert(lv>=mx);
				assert(rv>=mx);
				lson->cov(lv,rv);
				rson->cov(lv,rv);
				tag=false;
			}
		}
		inline void up(){
			assert(!tag);
			mx=max(lson->mx,rson->mx);
			ans=min(lson->ans,rson->ans);
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->lv=x->rv=-INF-1;
		if(l==r){
			x->mx=a[l]-l;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void setv(node x,int lv,int rv){
		if(x->lv==lv&&x->rv==rv)return;
		if(lv>=x->mx&&rv>=x->mx){
			x->cov(lv,rv);
			return;
		}
		if(x->l==x->r){
			x->lv=lv,x->rv=rv;
			x->gans();
		}else{
			x->dn();
			x->lv=lv,x->rv=rv;
			setv(x->lson,lv,max(x->rson->mx,rv));
			setv(x->rson,max(lv,x->lson->mx),rv);
			x->up();
		}
	}
	void upd(node x,int p){
		if(x->l==x->r){
			x->mx=a[p]-p;
			x->gans();
			return;
		}
		x->dn();
		if(p<=x->m){
			upd(x->lson,p);
			setv(x->rson,max(x->lv,x->lson->mx),x->rv);
		}else{
			upd(x->rson,p);
			setv(x->lson,x->lv,max(x->rson->mx,x->rv));
		}
		x->up();
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
#endif
	n=ni;
	int m=ni,p=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	seg::node rt=seg::build(1,n);
	seg::setv(rt,-INF,-INF);
	for(int i=1;printf("%d\n",rt->ans),i<=m;i++){
		int x=ni^(rt->ans*p),y=ni^(rt->ans*p);
		a[x]=y;
		seg::upd(rt,x);
	}
	return 0;
}
