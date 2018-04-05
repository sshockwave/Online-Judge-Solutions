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
namespace lct{
	const int N=::N*4;
	struct Node;
	typedef Node* node;
	node null;
	void draw(node);
	struct Node{
		//Variables
		node fa;
		union{
			struct{node lson,rson;};
			node son[2];
		};
		bool rev;
		node lpt,rpt;
		node lend,rend;
		bool isring,hasring;
		int *_prod,*_invprod,ringsize;
		int idx;
		int val;
		//Functions
		inline int ask(node _u,node _v){
			int u=_u->idx,v=_v->idx;
			assert(u!=-1&&v!=-1);
			if(u>v){
				swap(u,v);
			}
			int ans=(lint)_prod[v]*_invprod[u]%O;
			ans=(ans+(lint)_prod[ringsize-1]*_invprod[v]%O*_prod[u])%O;
			const static int inv2=inv(2);
			return (lint)ans*inv2%O;
		}
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void putrev(){
			if(this==null)return;
			rev^=1;
			swap(lson,rson);
			swap(lpt,rpt);
			swap(lend,rend);
		}
		inline void dn(){
			if(rev){
				lson->putrev();
				rson->putrev();
				rev=false;
			}
		}
		inline void up(){
			lend=lson!=null?lson->lend:this;
			rend=rson!=null?rson->rend:this;
			bool ispt=idx!=-1;
			lpt=lson->lpt!=null?lson->lpt:ispt?this:rson->lpt;
			rpt=rson->rpt!=null?rson->rpt:ispt?this:lson->rpt;
			hasring=isring||lson->hasring||rson->hasring;
			val=(lint)lson->val*rson->val%O;
			if(ispt){
				if(lson->rend->ringsize&&lson->rpt!=null){
					val=(lint)val*lson->rend->ask(lson->rpt,this)%O;
				}
				if(rson->lend->ringsize&&rson->lpt!=null){
					val=(lint)val*rson->lend->ask(rson->lpt,this)%O;
				}
			}else if(ringsize&&lson->rpt!=null&&rson->lpt!=null){
				assert(lson->rend->idx!=-1);
				assert(rson->lend->idx!=-1);
				val=(lint)val*ask(lson->rpt,rson->lpt)%O;
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
	node pts[N],*ps=pts;
	inline node nn(node x=null){
		assert(ps-pts<N);
		return **ps=*x,*(ps++);
	}
	inline void del(node x){
		*--ps=x;
		delete[] x->_prod;
		delete[] x->_invprod;
	}
	inline void init(){
		for(int i=0;i<N;i++){
			pts[i]=pool+i;
		}
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
		null->lpt=null->rpt=null;
		null->lend=null->rend=null;
		null->idx=-1;
		null->val=1;
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
	void putall(node x,node efa,int* &prod,int &tim){
		if(x==null)return;
		x->dn();
		putall(x->lson,efa,prod,tim);
		bool isedg=x->ringsize,istmp=x->idx!=-1,ispt=!isedg&&!istmp;
		if(isedg){
			assert(x->ringsize==2);
			prod++[0]=x->_prod[0];
		}else if(ispt){
			node t=nn();
			t->idx=tim++;
			t->fa=efa,x->fa=t;
		}
		putall(x->rson,efa,prod,tim);
		if(ispt){
			x->lson=x->rson=null;
			x->up();
		}else{
			del(x);
		}
	}
}
lct::node nd[N];
int prod[N];
inline void work(int n,lct::node x){
	x->_prod=new int[n],x->_invprod=new int[n],x->ringsize=n;
	lint w=1;
	for(int i=0;i<n;i++){
		w=w*prod[i]%O;
		x->_prod[i]=w;
		x->_invprod[i]=inv(w);
	}
}
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
		lct::chr(u),lct::acc(v),v->spa();
		if(op==1){
			bool flag;
			int w=ni;
			if(u==v){
				flag=true;
			}else if(u->sd()==-1){//add edge
				flag=true;
				lct::node e=lct::nn();
				lct::node d1=lct::nn(),d2=lct::nn();
				d1->fa=d2->fa=e;
				d1->idx=0,d2->idx=1;
				u->fa=d1,v->putrev(),v->fa=d2;
				prod[0]=w,prod[1]=w;
				work(2,e);
				d1->up(),d2->up(),e->up();
			}else if(v->hasring){
				flag=false;
			}else{//add ring
				flag=true;
				lct::node e=lct::nn();
				int len=0,*p=prod;
				p++[0]=w;
				lct::putall(v,e,p,len);
				work(len,e);
				e->isring=true,e->up();
			}
			putchar('0'+flag),putchar('\n');
		}else{//query
			ans=u==v||u->sd()!=-1?v->val:0;
			printf("%d\n",ans);
		}
	}
	return 0;
}
