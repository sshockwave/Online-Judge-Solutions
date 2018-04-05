#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,E=200010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int prod[N],prods;
int ls;
namespace lct{
	const int N=::N+::E;
	struct Node;
	typedef Node* node;
	node lst[N];
	struct mapper{
		node *pt;
		int *val,size;
		inline int& operator [] (node x){
			int l=0,r=size-1;
			while(l<r){
				int m=(l+r)>>1;
				if(pt[m]<x){
					l=m+1;
				}else{
					r=m;
				}
			}
			return val[l];
		}
		inline void init(){
			pt=new node[ls];
			size=ls;
			for(int i=0;i<ls;i++){
				pt[i]=lst[i];
			}
			sort(pt,pt+ls);
			val=new int[ls];
			for(int i=0;i<ls;i++){
				this->operator[](lst[i])=i;
			}
		}
	};
	node null;
	void draw(node);
	struct Node{
		//Variables
		node fa;
		union{
			struct{node lson,rson;};
			node son[2];
		};
		node lpt,rpt;
		node ldg,rdg;
		bool rev;
		int *_prod,*_invprod,ringsize;
		mapper idx;
		bool isbi,hasbi;
		int val;
		//Functions
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void putrev(){
			if(this==null)return;
			rev^=1;
			swap(lson,rson);
			swap(lpt,rpt);
			swap(ldg,rdg);
		}
		inline int qry(node _u,node _v){
			assert(_u!=_v);
			assert(idx.find(_u)!=idx.end());
			assert(idx.find(_v)!=idx.end());
			int u=idx[_u],v=idx[_v];
			if(u>v)swap(u,v);
			const static int inv2=inv(2);
			int ans=(lint)_prod[ringsize-1]*_invprod[v]%O*_prod[u]%O;
			ans=(ans+(lint)_prod[v]*_invprod[u])%O;
			return (lint)ans*inv2%O;
		}
		inline void dn(){
			if(rev){
				lson->putrev();
				rson->putrev();
				rev=false;
			}
		}
		inline void up(){
			bool ispt=ringsize==0,isdg=!ispt;
			lpt=lson->lpt!=null?lson->lpt:ispt?this:rson->lpt;
			rpt=rson->rpt!=null?rson->rpt:ispt?this:lson->rpt;
			ldg=lson->ldg!=null?lson->ldg:isdg?this:rson->ldg;
			rdg=rson->rdg!=null?rson->rdg:isdg?this:lson->rdg;
			assert(!rev);
			hasbi=isbi||lson->hasbi||rson->hasbi;
			val=(lint)lson->val*rson->val%O;
			if(ispt){
				if(lson->rpt!=null&&lson->rdg!=null){
					val=(lint)val*lson->rdg->qry(lson->rpt,this)%O;
				}
				if(rson->lpt!=null&&rson->ldg!=null){
					val=(lint)val*rson->ldg->qry(rson->lpt,this)%O;
				}
			}else if(lson->rpt!=null&&rson->lpt!=null){
				val=(lint)val*qry(lson->rpt,rson->lpt)%O;
			}
		}
		inline void rot(){
			assert(sd()!=-1);
			bool d=!sd();
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			int g=fa->sd();
			fa=fa->fa,son[d]->fa=this;
			if(g!=-1){
				fa->son[g]=this;
			}
			son[d]->up(),up();
		}
		inline void spa(){
			draw(this);
			for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
		}
	}pool[N],Null;
	node pol=pool;
	inline node nn(node x=null){
		static node &n=pol;
		return *n=*x,n++;
	}
	inline void init(){
		null=&Null;
		null->fa=null->lson=null->rson=null;
		null->lpt=null->rpt=null;
		null->ldg=null->rdg=null;
		null->rev=false;
		null->isbi=null->hasbi=0,null->val=1;
	}
	void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa);
		}
		x->dn();
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			x->rson=s;
			x->up();
		}
	}
	inline void chr(node x){
		acc(x),x->spa(),x->putrev();
	}
	void putall(node x,node nfa){
		if(x==null)return;
		x->dn();
		putall(x->lson,nfa);
		assert(!x->hasbi);
		bool ispt=x->ringsize==0;
		if(ispt){
			lct::lst[ls++]=x;
		}else{
			assert(x->ringsize==2);
			prod[prods++]=x->_prod[0];
		}
		putall(x->rson,nfa);
		if(ispt){
			x->fa=nfa;
			x->lson=x->rson=null;
			x->up();
		}
	}
}
inline void getprod(int* &p,int* &invprod){
	lint pw=1;
	p=new int[prods];
	invprod=new int[prods];
	for(int i=0;i<prods;i++){
		pw=pw*prod[i]%O,p[i]=pw,invprod[i]=inv(pw);
	}
}
lct::node nd[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
#endif
	int n=ni,tot=ni,tp=ni;
	lct::init();
	for(int i=1;i<=n;i++){
		nd[i]=lct::nn();
		nd[i]->up();
	}
	for(int ans=0;tot--;){
		int op=ni;
		lct::node u,v;
		{
			int x=ni,y=ni;
			if(tp){
				x=(x+ans)%n+1,y=(y+ans)%n+1;
			}
			u=nd[x],v=nd[y];
		}
		if(op==1){//add edge
			int w=ni;
			lct::chr(u),lct::acc(v),v->spa();
			bool flag;
			if(u==v){//self-loop
				flag=true;
			}else if(u->sd()==-1){//create new edge
				flag=true;
				lct::node e=lct::nn();
				ls=0,lct::lst[ls++]=u,lct::lst[ls++]=v;
				e->idx.init();
				prods=0,prod[prods++]=w,prod[prods++]=w;
				e->ringsize=prods;
				getprod(e->_prod,e->_invprod);
				u->fa=e,e->fa=v;
				e->up();
			}else if(!v->hasbi){//create new ring
				flag=true;
				lct::node e=lct::nn();
				e->isbi=true;
				prods=0;
				prod[prods++]=w;
				ls=0,lct::putall(v,e);
				e->ringsize=prods;
				getprod(e->_prod,e->_invprod);
				e->idx.init();
				e->up();
			}else{
				flag=false;
			}
			putchar('0'+flag),putchar('\n');
		}else{//query
			lct::chr(u),lct::acc(v),v->spa();
			ans=u->sd()==-1?0:v->val;
			printf("%d\n",ans);
		}
	}
	return 0;
}
