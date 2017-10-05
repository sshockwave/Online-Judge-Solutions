#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,E=100010;
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}e[E];
namespace lct{
	const int N=100010+100010;
	struct Node;
	typedef Node* node;
	struct Node{
		node fa;
		union{
			node son[2];
			struct{
				node lson,rson;
			};
		};
		Edge *e,*mxe;
		bool tag;
		inline int side(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void rev(){
			tag=!tag,swap(lson,rson);
		}
		inline void down(){
			if(tag){
				lson->rev(),rson->rev(),tag=false;
			}
		}
		inline void up(){
			mxe=e;
			if(lson->mxe->w>mxe->w){
				mxe=lson->mxe;
			}
			if(rson->mxe->w>mxe->w){
				mxe=rson->mxe;
			}
		}
		inline void draw(){
			if(~side()){
				fa->draw();
			}
			down();
		}
		inline void rot(){
			fa->down(),down();
			if(~fa->side()){
				fa->fa->son[fa->side()]=this;
			}
			bool d=!side();
			fa->son[!d]=son[d],son[d]->fa=fa,son[d]=fa,fa=fa->fa,son[d]->fa=this;
			son[d]->up(),up();
		}
		inline void splay(){
			draw();
			while(~side()){
				if(fa->side()==-1){
					rot();
				}else if(fa->side()==side()){
					fa->rot(),rot();
				}else{
					rot(),rot();
				}
			}
		}
	}pool[N],null=(Node){&null,&null,&null,e,e,false};
	inline void init(int n){
		e[0].w=0;
		for(int i=1;i<=n;i++){
			pool[i]=null;
		}
	}
	inline void acc(node x){
		for(node s=&null;x!=&null;x->splay(),x->rson=s,x->up(),s=x,x=s->fa);
	}
	inline void chr(node x){
		acc(x),x->splay(),x->rev();
	}
	inline void lnk(node u,node v){
		chr(v),v->fa=u;
	}
	inline void cut(node u,node v){
		chr(u),acc(v),u->fa=v->lson=&null;
	}
	inline node rot(node x){
		acc(x),x->splay();
		for(;x->lson!=&null;x=x->lson);
		x->splay();
		return x;
	}
}
int tim;
namespace seg{
	const int N=E;
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int sum,tag;
		inline void up(){
			sum=lson->sum+rson->sum;
		}
	}*rt[N];
	inline node renew(node x){
		static node n=new Node[N*30];
		return x->tag==tim?x:(*n=*x,n->tag=tim,n++);
	}
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->sum=x->tag=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	node alt(node x,int p){
		x=renew(x);
		if(x->l==x->r){
			x->sum=e[p].w-x->sum;
		}else{
			if(p<=x->m){
				x->lson=alt(x->lson,p);
			}else{
				x->rson=alt(x->rson,p);
			}
			x->up();
		}
		return x;
	}
	int ask(node x,int l,int r){
		if(x->l==l&&x->r==r){
			return x->sum;
		}
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("build.in","r",stdin);
	freopen("build.out","w",stdout);
#endif
	int n=ni,es=ni,ol=ni,ans=0;
	lct::init(n+es);
	for(int i=1;i<=es;i++){
		e[i]=(Edge){ni,ni,ni};
		lct::pool[i+n].e=e+i;
		lct::pool[i+n].mxe=e+i;
	}
	sort(e+1,e+es+1);
	tim=es+1;
	seg::rt[es+1]=seg::build(1,es);
	for(tim=es;tim>=1;tim--){
		int u=e[tim].u,v=e[tim].v;
		seg::rt[tim]=seg::rt[tim+1];
		if(lct::rot(lct::pool+u)==lct::rot(lct::pool+v)){
			lct::chr(lct::pool+u),lct::acc(lct::pool+v),lct::pool[v].splay();
			lct::node t=lct::pool[v].mxe-e+n+lct::pool;
			lct::cut(lct::pool+t->e->u,t);
			lct::cut(lct::pool+t->e->v,t);
			seg::rt[tim]=seg::alt(seg::rt[tim],t->e-e);
		}
		lct::lnk(lct::pool+u,lct::pool+n+tim);
		lct::lnk(lct::pool+v,lct::pool+n+tim);
		seg::rt[tim]=seg::alt(seg::rt[tim],tim);
	}
	for(int tot=ni,l,m,r;tot--;){
		int lo=ni-ans*ol,hi=ni-ans*ol;
		for(l=1,r=es+1;l<r;m=(l+r)>>1,(e[m].w<lo)?(l=m+1):(r=m));
		lo=l;
		for(l=0,r=es;l<r;m=((l+r)>>1)+1,(e[m].w>hi)?(r=m-1):(l=m));
		hi=l;
		printf("%d\n",ans=lo<=hi?seg::ask(seg::rt[lo],lo,hi):0);
	}
	return 0;
}
