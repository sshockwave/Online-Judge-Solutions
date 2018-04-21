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
const int N=400010,INF=0x7f7f7f7f;
int qrys,qryt;
inline int in_bound(int x){
	if(qrys<=qryt)return qrys<=x&&x<=qryt;
	else return qrys<=x||x<=qryt;
}
namespace lct{
	namespace splay{
		struct Node;
		typedef Node* node;
		node null;
		struct Node{
			//Variables
			union{
				struct{node lson,rson;};
				node son[2];
			};
			node fa;
			int v,mx,size;
			//Functions
			inline int sd(){
				return fa->lson==this?0:fa->rson==this?1:-1;
			}
			inline void up(){
				size=lson->size+1+rson->size;
				mx=max(v,max(lson->v,rson->v));
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
				for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
			}
		}pool[N],Null;
		inline void init(){
			memset(null=&Null,0,sizeof(Null));
			null->fa=null->lson=null->rson=null;
			null->mx=-INF;
		}
		inline node nn(node x=null){
			static node n=pool;
			return *n=*x,n->up(),n++;
		}
		inline node kth(node x,int k){
			if(x==null)return null;
			if(k==0||k>x->size)return null;
			assert(x->fa==null);
			while(true){
				if(k<=x->lson->size){
					x=x->lson;
				}else if(k>x->lson->size+1){
					k-=x->lson->size+1;
					x=x->rson;
				}else break;
			}
			x->spa();
			return x;
		}
		inline node ins_rig(node x,node v){
			if(x==null){
				v->fa=v->lson=v->rson=null,v->up();
				return v;
			}
			assert(x->fa==null);
			for(;x->rson!=null;x=x->rson);
			x->spa();
			v->fa=x,v->lson=v->rson=null,v->up();
			x->rson=v,x->up();
			return x;
		}
		int preval;
		inline node shval(node x,int v){
			assert(x->fa=null);
			assert(x!=null);
			for(;x->lson!=null;x=x->lson);
			x->spa();
			assert(x->v>v);
			node t=x;
			x=x->rson;
			x->fa=null;
			preval=t->v,t->v=v;
			return ins_rig(x,t);
		}
		inline node fir_big(node x,int v){//first to be bigger than v
			assert(x->fa==null);
			node lastnode=null;
			while(x!=null){
				lastnode=x;
				if(x->rson->mx>v){
					x=x->rson;
				}else if(x->v<=v){
					x=x->lson;
				}else break;
			}
			if(lastnode!=null){
				lastnode->spa();
			}
			return x;
		}
	}
	struct Node;
	typedef Node* node;
	node null;
	void draw(node);
	struct Node{
		//Variables
		union{
			struct{node lson,rson;};
			node son[2];
		};
		node fa;
		splay::node rt;
		int size;
		int pos,mxpos;
		//Functions
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void up(){
			size=lson->size+1+rson->size;
			mxpos=lson!=null?lson->pos:pos;
		}
		inline void dn(){
			if(lson!=null){
				lson->rt=rt;
			}
			if(rson!=null){
				rson->rt=rt;
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
	void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa);
		}
		x->dn();
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
		splay::init(),null->rt=splay::null;
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n->up(),n++;
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			assert(x->rt->sd()==-1);
			x->rt=splay::kth(x->rt,x->lson->size+1),x->rt->spa();
			assert(x->rt!=splay::null);
			if(x->rson!=null){
				assert(x->rt->rson!=splay::null);
				x->rt->rson->fa=splay::null;
				x->rson->rt=x->rt->rson;
				assert(x->rson->rt->sd()==-1);
			}
			if(s!=null){
				assert(s->rt!=splay::null);
				assert(s->rt->fa==splay::null);
				s->rt->fa=x->rt,s->rt->up();
			}
			assert(x->rt->sd()==-1);
			x->rt->rson=s->rt,x->rt->up();
			x->rson=s,x->up();
		}
	}
	inline node fir_out(node x){
		assert(x->fa==null);
		node lastnode=null;
		while(x!=null){
			x->dn();
			if(x->rson!=null&&!in_bound(x->rson->mxpos)){
				x=x->rson;
			}else if(in_bound(x->pos)){
				x=x->lson;
			}else break;
		}
		if(lastnode!=null){
			lastnode->spa();
		}
		return x;
	}
	inline node kth(node x,int k){
		assert(x->fa==null);
		if(x==null)return null;
		if(k==0||k>x->size)return null;
		while(true){
			x->dn();
			if(k<=x->lson->size){
				x=x->lson;
			}else if(k>x->lson->size+1){
				k-=x->lson->size+1;
				x=x->rson;
			}else break;
		}
		x->spa();
		return x;
	}
}
lct::node nd[N];
inline lct::node gfir(int p,int v){//fir > v
	using namespace lct;
	node x=nd[p];
	acc(x),x->spa();
	x->rt=splay::kth(x->rt,x->lson->size+1),x->rt->spa();
	if(x->rt->v>v)return x;
	splay::node t=splay::fir_big(x->rt,v);
	if(t==splay::null)return null;
	x->rt=t,x->rt->spa();
	x=kth(x,x->rt->lson->size+1),x->spa();
	return x;
}
inline void build_node(int n){
	using namespace lct;
	for(int i=1;i<=n;i++){
		nd[i]=nn();
		nd[i]->pos=i;
		nd[i]->rt=splay::nn();
		nd[i]->rt->v=ni;
		nd[i]->rt->up();
	}
	for(int i=n-1;i>=1;i--){
		nd[i]->fa=gfir(i+1,nd[i]->rt->v);
	}
	for(int i=n;i>=1;i--){
		node x=nd[i];
		acc(x),x->spa();
		if(x->lson!=null)continue;
		assert(x->rt->v==x->rt->mx);
		node t=gfir(i<n?i+1:1,x->rt->v);
		acc(x),x->spa(),x->fa=t;
	}
}
inline int Main(){
	qrys=ni,qryt=ni;
	int v=ni;
	lct::node x=gfir(qrys,v);
	if(x==lct::null)return v;
	lct::acc(x),x->spa();
	lct::node y=lct::fir_out(x);
	if(y==lct::null){//sh on x
		x->spa();
		x->rt=lct::splay::shval(x->rt,v);
	}else if(y->rson!=lct::null){//sh on y->rson
		x=y;
		x->spa();
		x->rt=lct::splay::kth(x->rt,x->lson->size+1);
		x->rt->spa();
		x->rson->rt=x->rt->rson;
		x->rt->rson=lct::splay::null;
		x->rson->rt->fa=lct::splay::null;
		x->rson->rt=lct::splay::shval(x->rson->rt,v);
		x->rt->rson=x->rson->rt,x->rt->up();
	}else return v;//no bigger value in [s,t]
	//has val bigger than x
	assert(x->fa==lct::null);
	lct::node t=gfir(x->mxpos,x->rt->mx);
	x->spa(),x->fa=t;
	return lct::splay::preval;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sushi.in","r",stdin);
	freopen("sushi.out","w",stdout);
#endif
	int n=ni,q=ni;
	lct::init();
	build_node(n);
	for(int i=1;i<=q;i++){
		printf("%d\n",Main());
	}
	return 0;
}
