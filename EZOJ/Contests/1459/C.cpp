#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
template<class T>inline int sgn(const T &x){return x>0?1:x<0?-1:0;}
const int N=400010;
struct Pt{
#define Pt(x,y) ((Pt){x,y})
	lint x,y;
	inline friend lint crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
	inline friend lint dot(const Pt &a,const Pt &b){return a.x*b.x+a.y*b.y;}
};
namespace treap{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		unsigned pri;
		Pt vec;
		int size;
		int cnt,dt;
		lint sum;
		inline void addv(int v){
			if(this==null)return;
			cnt+=v,dt+=v,sum+=(lint)v*size;
		}
		inline void up(){
			assert(dt==0);
			size=lson->size+1+rson->size;
			sum=lson->sum+cnt+rson->sum;
		}
		inline void dn(){
			if(dt){
				lson->addv(dt);
				rson->addv(dt);
				dt=0;
			}
		}
	}pool[N],Null;
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n->pri=rand(),n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(u->pri>v->pri)return u->dn(),u->rson=mg(u->rson,v),u->up(),u;
		else return v->dn(),v->lson=mg(u,v->lson),v->up(),v;
	}
	template<bool sel(node)>void sp(node x,node &lhs,node &rhs){
		if(x==null)return lhs=rhs=null,void();
		x->dn();
		if(sel(x)){
			lhs=x;
			sp<sel>(x->rson,x->rson,rhs);
		}else{
			rhs=x;
			sp<sel>(x->lson,lhs,x->lson);
		}
		x->up();
	}
}
inline lint C2(int n){
	return ((lint)n*(n-1))>>1;
}
using treap::node;
Pt a,b,transb;
int qb;
inline int quad(const Pt &p){
	if(p.x>0&&p.y>=0)return 1;
	if(p.y>0&&p.x<=0)return 2;
	if(p.x<0&&p.y<=0)return 3;
	if(p.y<0&&p.x>=0)return 4;
	assert(false);
}
inline bool bet_sel(node x){
	//is between [a,b) ?
	const Pt &c=x->vec;
	const Pt transc=Pt(dot(a,c),crs(a,c));
	//is c<b?
	const int qc=quad(transc);
	return qb!=qc?qc<qb:(crs(c,b)>0);
}
inline bool dir_sel(node x){
	return crs(b,x->vec)==0&&dot(b,x->vec)>0;
}
inline bool y_sel(node x){
	return crs(b,x->vec)>0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("philosopher.in","r",stdin);
	freopen("philosopher.out","w",stdout);
#endif
	treap::init();
	node rt=treap::null,las=treap::null;
	lint ans=0;
	for(int tot=ni;tot--;){
		const node x=treap::nn();
		x->vec=Pt(ni,ni);
		node lhs,rhs,para,oppo;
		using treap::sp;
		using treap::mg;
		if(rt!=treap::null){
			a=las->vec;
			b=x->vec,transb=Pt(dot(a,b),crs(a,b)),qb=quad(transb);
			sp<bet_sel>(rt,lhs,rhs);
			rt=mg(rhs,lhs);
		}
		las=x;
		sp<dir_sel>(rt,para,lhs);
		sp<y_sel>(lhs,lhs,oppo);
		b=Pt(-b.x,-b.y);
		sp<dir_sel>(oppo,oppo,rhs);
		x->cnt=para->size+lhs->size,x->up();
		rhs->addv(1);
		ans+=lhs->sum-C2(lhs->size)-(lint)lhs->size*oppo->size;
		rt=mg(x,mg(mg(para,lhs),mg(oppo,rhs)));
		printf("%lld\n",ans);
	}
	return 0;
}
