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
db a[N];
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		db sum;
		inline void up(){
			sum=lson->sum+rson->sum;
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->sum=a[x->m];
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void upd(node x,int l,int r){
		if(x->l==x->r){
			x->sum=a[x->m];
		}else{
			if(r<=x->m){
				upd(x->lson,l,r);
			}else if(l>x->m){
				upd(x->rson,l,r);
			}else{
				upd(x->lson,l,x->m);
				upd(x->rson,x->m+1,r);
			}
			x->up();
		}
	}
	db ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->sum;
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
inline bool a_greater(db a,db b){
	return a>b;
}
db pwlst[11];
int main(){
#ifndef ONLINE_JUDGE
	freopen("zkb.in","r",stdin);
	freopen("zkb.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<10;i++){
		pwlst[i]=log10((db)i);
	}
	for(int i=1;i<=n;i++){
		a[i]=log10((db)ni);
	}
	seg::node rt=seg::build(1,n);
	for(int tot=m;tot--;){
		int op=ni,l=ni,r=ni;
		if(op==1){
			if(ni){
				sort(a+l,a+r+1);
			}else{
				sort(a+l,a+r+1,a_greater);
			}
			seg::upd(rt,l,r);
		}else{
			db t=seg::ask(rt,l,r);
			t-=(lint)t;
			int d=9;
			const static db EPS=1e-10;
			for(;pwlst[d]>t+EPS;d--);
			putchar('0'+d);
			putchar('\n');
		}
	}
	return 0;
}
