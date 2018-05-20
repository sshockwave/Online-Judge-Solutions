#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef long double db;
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
int n;
db a[N],b[N];
namespace seg2{
	const int N=::N*20;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		db sum;
		int cnt;
		inline void up(){
			cnt=lson->cnt+rson->cnt;
			sum=lson->sum+rson->sum;
		}
	}pool[N],Null;
	node pt[N],*ppt=pt;
	inline node nn(node x=null){
		return **ppt=*x,*(ppt++);
	}
	inline void del(node x){
		*--ppt=x;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		for(int i=0;i<N;i++){
			pt[i]=pool+i;
		}
	}
	node ins(node x,int p,int l=1,int r=n){
		x=nn(x);
		if(l==r){
			x->sum=p,x->cnt=1;
		}else{
			int m=(l+r)>>1;
			if(p<=m){
				x->lson=ins(x->lson,p,l,m);
			}else{
				x->rson=ins(x->rson,p,m+1,r);
			}
			x->up();
		}
		return x;
	}
	node mg(node u,node v,int l=1,int r=n){
		if(u==null||v==null)return u!=null?u:v;
		assert(l!=r);
		u->lson=mg(u->lson,v->lson);
		u->rson=mg(u->rson,v->rson);
		u->up();
		del(v);
		return u;
	}
	void sp(node x,int k,node &lhs,node &rhs,int l=1,int r=n){
		if(k==0||k==x->cnt)return (k?lhs=x,rhs=null:lhs=null,rhs=x),void();
		assert(x!=null);
		assert(l<r);
		node y=nn();
		int m=(l+r)>>1;
		if(k<=x->lson->cnt){
			y->rson=x->rson,x->rson=null;
			sp(x->lson,k,x->lson,y->lson,l,m);
		}else{
			sp(x->rson,k-x->lson->cnt,x->rson,y->rson);
		}
		x->up(),y->up();
		lhs=x,rhs=y;
	}
	db ask(node x,int k,int l=1,int r=n){
		if(k==0)return 0;
		if(k==x->cnt)return x->sum;
		assert(l!=r);
		int m=(l+r)>>1;
		if(k<=x->lson->cnt)return ask(x->lson,k,l,m);
		return x->lson->sum+ask(x->rson,k-x->lson->cnt,m+1,r);
	}
}
int rnk[N];
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		seg2::node rt;
		db sum;
		int d;
		inline void dn(){
			if(rt==seg2::null)return;
			if(d){//inc
				seg2::sp(rt,m-l+1,lson->rt,rson->rt);
			}else{//dec
				seg2::sp(rt,r-m,rson->rt,lson->rt);
			}
			rt=seg2::null;
			lson->d=rson->d=d;
			lson->sum=lson->rt->sum;
			rson->sum=rson->rt->sum;
		}
		inline void up(){
			assert(rt==seg2::null);
			sum=lson->sum+rson->sum;
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->rt=seg2::ins(seg2::null,rnk[x->m]);
			x->sum=x->rt->sum;
		}else{
			x->rt=seg2::null;
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	seg2::node get_intv(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->rt;
		x->dn();
		if(r<=x->m)return get_intv(x->lson,l,r);
		if(l>x->m)return get_intv(x->rson,l,r);
		return seg2::mg(get_intv(x->lson,l,x->m),get_intv(x->rson,x->m+1,r));
	}
	void set_intv(node x,int l,int r,seg2::node rt,int d){
		if(x->l==l&&x->r==r){
			x->rt=rt,x->d=d,x->sum=rt->sum;
			return;
		}
		assert(x->rt==seg2::null);
		if(r<=x->m){
			set_intv(x->lson,l,r,rt,d);
		}else if(l>x->m){
			set_intv(x->rson,l,r,rt,d);
		}else{
			seg2::node a,b;
			if(d){
				seg2::sp(rt,x->m-l+1,a,b);
			}else{
				seg2::sp(rt,r-x->m,b,a);
			}
			set_intv(x->lson,l,x->m,a,d);
			set_intv(x->rson,x->m+1,r,b,d);
		}
		x->up();
	}
	db ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->sum;
		if(x->rt!=seg2::null){
			l-=x->l-1,r-=x->l-1;
			if(x->d==0){
				const int len=x->r-x->l+1;
				l=len+1-l,r=len+1-r;
				swap(l,r);
			}
			return seg2::ask(x->rt,r)-seg2::ask(x->rt,l-1);
		}
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
db pwlst[11];
inline bool lcmp(int x,int y){
	return a[x]<a[y];
}
int lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("zkb.in","r",stdin);
	freopen("zkb.out","w",stdout);
#endif
	n=ni;
	int m=ni;
	for(int i=1;i<10;i++){
		pwlst[i]=log10((db)i);
	}
	for(int i=1;i<=n;i++){
		a[i]=b[i]=log10((db)ni);
		lst[i]=i;
	}
	sort(b+1,b+n+1);
	sort(lst+1,lst+n+1,lcmp);
	for(int i=1;i<=n;i++){
		rnk[lst[i]]=i;
	}
	seg2::init();
	seg::node rt=seg::build(1,n);
	for(int tot=m;tot--;){
		int op=ni,l=ni,r=ni;
		if(op==1){//sort
			seg::set_intv(rt,l,r,seg::get_intv(rt,l,r),ni);
		}else{//ask
			db ans=seg::ask(rt,l,r);
			ans-=floor(ans);
			int d=9;
			const static db EPS=1e-10;
			for(;pwlst[d]>ans+EPS;d--);
			putchar('0'+d),putchar('\n');
		}
	}
	return 0;
}
