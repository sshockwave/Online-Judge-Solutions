#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef vector<int>vi;
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
const int N=120010;
int a[N],pos[N];
struct Intv{
	int l,r;
	inline friend Intv operator + (const Intv &a,const Intv &b){
		return (Intv){min(a.l,b.l),max(a.r,b.r)};
	}
	inline friend bool operator == (const Intv &a,const Intv &b){
		return a.l==b.l&&a.r==b.r;
	}
}ext[N];
int dep[N];
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		Intv ext;
		inline void getinfo(){
			ext=::ext[m];
		}
		inline void up(){
			ext=lson->ext+rson->ext;
		}
	}pool[N];
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
	Intv ask_go(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->ext;
		if(r<=x->m)return ask_go(x->lson,l,r);
		if(l>x->m)return ask_go(x->rson,l,r);
		return ask_go(x->lson,l,x->m)+ask_go(x->rson,x->m+1,r);
	}
	void upd(node x,int p){
		if(x->l==x->r){
			x->getinfo();
		}else{
			upd(p<=x->m?x->lson:x->rson,p);
			x->up();
		}
	}
}
Intv qry[N];
lint ans[N];
/*
namespace T{
	vi vec[N];
	void build(int l,int r,int d){
		if(l==r)return;
		dep[l]=d;
		const Intv &cur=ext[l];
		assert(cur.r<=r);
		if(cur.l<l||cur.r==r){
			build(l,l,d+1),build(l+1,r,d+1);
		}else{
			build(l,cur.r,d+1),build(cur.r+1,r,d+1);
		}
	}
	treap::node work(int l,int r){
		using namespace treap;
		if(l==r)return null;
		const Intv &cur=ext[l];
		assert(cur.r<=r);
		int m=cur.l<l||cur.r==r?l:cur.r;
		const node lson=work(l,m),rson=work(m+1,r);
		for(vi::iterator it=vec[l].begin(),ti=vec[l].end();it!=ti;++it){
			int ql=qry[*it].l,qr=qry[*it].r;
			ans[*it]=ask_r(lson,m-ql+1)+ask_l(rson,qr-m);
		}
		const node x=mg(lson,rson);
		add_l(x),add_r(x);
		return x;
	}
}*/
lint all_ans=0;
inline lint n2(int n){
	return (lint)n*(n+1)/2;
}
void solve(int l,int r){
	if(l==r)return;
	bool blk=false;
	for(;l<r;){
		const Intv &cur=ext[l];
		if(cur.r<r){
			//cout
		}
	}
	ans+=blk;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	if(n==1){
		for(int tot=ni;tot--;){
			puts("1");
		}
		return 0;
	}
	seg::node rt=seg::build(1,n-1);
	for(;;){
		bool haschange=false;
		for(int i=1;i<n;i++){
			Intv cur=ext[i];
			Intv nxt=seg::ask_go(rt,cur.l,cur.r-1);
			if(!(cur==nxt)){
				haschange=true;
				seg::upd(rt,i);
			}
		}
		if(!haschange)break;
	}
	solve(1,n),ans_all+=n;
	for(int tot=ni;tot--;){
		int l=ni,r=ni;
		if(l==1&&r==n){
			printf("%lld\n",all_ans);
			continue;
		}
	}
	/*
	T::build(1,n,1);
	for(int i=1;i<n;i++){
		seg::upd(rt,i);
	}
	const int q=ni;
	for(int i=1;i<=q;i++){
		qry[i]=(Intv){ni,ni};
		T::vec[seg::ask_pos(qry[i].l,qry[i].r-1)].push_back(i);
	}
	T::work(1,n);
	for(int i=1;i<=q;i++){
		printf("%lld\n",ans[i]);
	}
	*/
	return 0;
}
