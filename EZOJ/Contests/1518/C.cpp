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
int n,m,tot;
namespace brute{
	const int N=2010;
	int mat[N][N];
	int main(){
		memset(mat,0,sizeof(mat));
		for(;tot--;){
			const int p=ni,x1=ni,y1=ni,x2=ni,y2=ni;
			if(p<=2){
				int dt=p==1?1:-1;
				for(int i=x1;i<=x2;i++){
					for(int j=y1;j<=y2;j++){
						mat[i][j]+=dt;
					}
				}
			}else{
				bool ok=true;
				ok&=mat[x1][y1]==mat[x2][y2];
				if(ok){
					for(int i=min(x1,x2);i<=max(x1,x2);i++){
						if(mat[i][y1]<mat[x1][y1]){
							ok=false;
							break;
						}
					}
					for(int j=min(y1,y2);j<=max(y1,y2);j++){
						if(mat[x2][j]<mat[x1][y1]){
							ok=false;
							break;
						}
					}
				}
				puts(ok?"Yes":"No");
			}
		}
		return 0;
	}
}
const int N=2010;
int curdt[N<<1];
namespace seg2{
	const int N=::N*::N*4;
	int mn[N],dt[N];
	inline int idx(int l,int r){
		return (l+r)|(l!=r);
	}
	inline void init(){
		memset(mn,0,sizeof(mn));
		memset(dt,0,sizeof(dt));
	}
	inline int newtree(){
		static int n=0;
		int t=n-2;
		n+=m*2-1;
		return t;
	}
	void putdt(int tr,int l,int r,int a,int b,int d,int tp){
		const int x=idx(l,r);
		d+=dt[tr+x];
		if(l==a&&r==b){
			curdt[x]+=d*tp;
			return;
		}
		const int m=(l+r)>>1;
		if(b<=m){
			putdt(tr,l,m,a,b,d,tp);
		}else if(a>m){
			putdt(tr,m+1,r,a,b,d,tp);
		}else{
			putdt(tr,l,m,a,m,d,tp);
			putdt(tr,m+1,r,m+1,b,d,tp);
		}
	}
	int askmin(int tr,int l,int r,int a,int b){
		if(l==a&&r==b){
			const int x=idx(l,r);
			return mn[tr+x]+curdt[x]-dt[tr+x];
		}
		const int m=(l+r)>>1;
		if(b<=m)return askmin(tr,l,m,a,b);
		if(a>m)return askmin(tr,m+1,r,a,b);
		return min(askmin(tr,l,m,a,m),askmin(tr,m+1,r,m+1,b));
	}
	inline void up(int tr,int l,int r){
		const int m=(l+r)>>1;
		const int x=idx(l,r),lson=idx(l,m),rson=idx(m+1,r);
		mn[tr+x]=min(mn[tr+lson],mn[tr+rson])+dt[tr+x];
	}
	void add(int tr,int l,int r,int a,int b,int v){
		assert(l<=r);
		assert(l<=a&&b<=r);
		if(l==a&&r==b){
			const int x=idx(l,r);
			mn[tr+x]+=v,dt[tr+x]+=v;
			return;
		}
		const int m=(l+r)>>1;
		if(b<=m){
			add(tr,l,m,a,b,v);
		}else if(a>m){
			add(tr,m+1,r,a,b,v);
		}else{
			add(tr,l,m,a,m,v);
			add(tr,m+1,r,m+1,b,v);
		}
		up(tr,l,r);
	}
	void upd_tr(int tr,int tr1,int tr2,int l,int r,int a,int b){
		if(l==a&&r==b){
			const int x=idx(l,r);
			mn[tr+x]=min(mn[tr1+x],mn[tr2+x])+dt[tr+x];
			return;
		}
		const int m=(l+r)>>1;
		if(b<=m){
			upd_tr(tr,tr1,tr2,l,m,a,b);
		}else if(a>m){
			upd_tr(tr,tr1,tr2,m+1,r,a,b);
		}else{
			upd_tr(tr,tr1,tr2,l,m,a,m);
			upd_tr(tr,tr1,tr2,m+1,r,m+1,b);
		}
		up(tr,l,r);
	}
}
namespace seg1{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int tr;
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->tr=seg2::newtree();
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void add(node x,int l,int r,int a,int b,int v){
		if(x->l==l&&x->r==r){
			seg2::add(x->tr,1,m,a,b,v);
			return;
		}
		if(r<=x->m){
			add(x->lson,l,r,a,b,v);
		}else if(l>x->m){
			add(x->rson,l,r,a,b,v);
		}else{
			add(x->lson,l,x->m,a,b,v);
			add(x->rson,x->m+1,r,a,b,v);
		}
		seg2::upd_tr(x->tr,x->lson->tr,x->rson->tr,1,m,a,b);
	}
	int ask(node x,int l,int r,int a,int b){
		seg2::putdt(x->tr,1,m,a,b,0,1);
		int ans;
		if(x->l==l&&x->r==r){
			ans=seg2::askmin(x->tr,1,m,a,b);
		}else if(r<=x->m){
			ans=ask(x->lson,l,r,a,b);
		}else if(l>x->m){
			ans=ask(x->rson,l,r,a,b);
		}else{
			ans=min(ask(x->lson,l,x->m,a,b),ask(x->rson,x->m+1,r,a,b));
		}
		seg2::putdt(x->tr,1,m,a,b,0,-1);
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
#endif
	n=ni,m=ni,tot=ni;
	if(n*m*tot<=27000000){
		return brute::main();
	}
	seg2::init();
	seg1::node rt=seg1::build(1,n);
	for(;tot--;){
		const int tp=ni,x1=ni,y1=ni,x2=ni,y2=ni;
		if(tp<=2){
			seg1::add(rt,x1,x2,y1,y2,tp==1?1:-1);
		}else{
#define A(a,b,c,d) seg1::ask(rt,a,b,c,d)
			const int v=A(x1,x1,y1,y1);
			bool ans=A(x2,x2,y2,y2)==v&&A(min(x1,x2),max(x1,x2),y1,y1)>=v&&A(x2,x2,min(y1,y2),max(y1,y2))>=v;
#undef A
			puts(ans?"Yes":"No");
		}
	}
	return 0;
}
