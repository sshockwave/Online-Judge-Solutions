#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=300010,INF=0x7f7f7f7f;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		bool del;
		int lend,rend;
		int p,v;
		int mxl,mxp,mnr,mnp;
		inline void chopl(int _lend){
			if(_lend<=lend)return;
			lend=_lend;
			assert(lend>=mxl);
			mxl=lend,mxp=mnp;
			p=mnp,v=mnr-lend;
		}
		inline void chopr(int _rend){
			if(_rend>=rend)return;
			rend=_rend;
			assert(rend<=mnr);
			mnr=rend;
			p=mxp,v=rend-mxl;
		}
		inline void up(){
			if(lson->del&&rson->del){
				del=true;
				return;
			}
			{//lend,rend
				lend=(!lson->del?lson:rson)->lend;
				rend=(!rson->del?rson:lson)->rend;
			}
			{//p,v
				v=INF;
				if(!lson->del&&lson->v<v){
					p=lson->p,v=lson->v;
				}
				if(!rson->del&&rson->v<v){
					p=rson->p,v=rson->v;
				}
			}
			{//mxl,mxp
				mxl=-INF;
				if(!lson->del&&lson->mxl>mxl){
					mxp=lson->mxp,mxl=lson->mxl;
				}
				if(!rson->del&&rson->mxl>mxl){
					mxp=rson->mxp,mxl=rson->mxl;
				}
			}
			{//mnr,mnp
				mnr=INF;
				if(!lson->del&&lson->mnr<mnr){
					mnp=lson->mnp,mnr=lson->mnr;
				}
				if(!rson->del&&rson->mnr<mnr){
					mnp=rson->mnp,mnr=rson->mnr;
				}
			}
		}
		inline void down(){
			if(del)return;
			if(!lson->del){
				lson->chopl(lend),lson->chopr(rend);
			}
			if(!rson->del){
				rson->chopl(lend),rson->chopr(rend);
			}
		}
	}pool[N];
	node rt,lst[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->del=false;
		if(l==r){
			x->lend=ni,x->rend=ni;
			x->p=l,x->v=x->rend-x->lend;
			x->mxp=l,x->mxl=x->lend;
			x->mnp=r,x->mnr=x->rend;
			lst[l]=x;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void chopl(node x,int l,int v){
		if(x->del)return;
		if(x->lend>=v)return;
		if(l==x->l&&x->mxl<=v)return x->chopl(v);
		x->down();
		if(l>x->m){
			chopl(x->rson,l,v);
		}else{
			chopl(x->lson,l,v);
			chopl(x->rson,x->m+1,v);
		}
		x->up();
	}
	void chopr(node x,int r,int v){
		if(x->del)return;
		if(x->rend<=v)return;
		if(r==x->r&&x->mnr>=v)return x->chopr(v);
		x->down();
		if(r<=x->m){
			chopr(x->lson,r,v);
		}else{
			chopr(x->lson,x->m,v);
			chopr(x->rson,r,v);
		}
		x->up();
	}
	void upd(node x,int p){
		if(x->l==x->r)return;
		assert(!x->del);
		x->down();
		upd(p<=x->m?x->lson:x->rson,p);
		x->up();
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("snow.in","r",stdin);
	freopen("snow.out","w",stdout);
#endif
	int len=ni,n=ni;
	seg::rt=seg::build(1,n);
	for(int i=1;i<=n;i++){
		int x=seg::rt->p;
		seg::upd(seg::rt,x);
		int lend=seg::lst[x]->lend,rend=seg::lst[x]->rend;
		seg::lst[x]->del=true;
		seg::upd(seg::rt,x);
		seg::chopr(seg::rt,x,lend);
		seg::chopl(seg::rt,x,rend);
		printf("%d\n",x);
	}
	return 0;
}
