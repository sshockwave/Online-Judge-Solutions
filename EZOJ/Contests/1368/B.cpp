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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=300010;
int ans=0;
namespace T{
	struct Node;
	typedef Node* node;
	struct Node{
		node fa;
		union{
			struct{
				node lson,rson;
			};
			node son[2];
		};
		int size,vac;
		node lch,rch;
		inline void up();
		inline int side();
		inline void rot(){//tocheck
			assert(~side());
			bool d=!side();
			son[d]->fa=fa,fa->son[!d]=son[d],son[d]=fa;
			int fd=fa->side();
			if(~fd){
				fa->fa->son[fd]=this;
			}
			fa=fa->fa,son[d]->fa=this;
			son[d]->up(),up();
		}
		inline void splay(){
			for(int d,fd;d=side(),~d;){
				fd=fa->side();
				if(fd==-1)return rot();
				else if(fd==d){
					fa->rot(),rot();
				}else{
					rot(),rot();
				}
			}
		}
		inline void gvac();
	}pool[N];
	node null;
	inline void Node::up(){
		size=lson->size+rson->size+1;
		lch=lson==null?this:lson->lch;
		rch=rson==null?this:rson->rch;
	}
	inline int Node::side(){
		return fa->lson==this?0:fa->rson==this?1:-1;
	}
	inline void Node::gvac(){
		splay();
		if(rson!=null){
			node tmp=rson;
			rson=null,up();
			if((tmp->rch->vac!=0)^(tmp->size&1)){
				vac++;
				tmp=tmp->lch;
				tmp->splay();
				tmp->rson=null,tmp->up();
			}
		}
	}
	inline void init(){
		null=new Node;
		null->fa=null->lson=null->rson=null->rch=null;
		null->size=null->vac=0;
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void work(node x){
		x->splay();
		for(node f;f=x->fa,f!=null;){
			f->gvac();
			assert(x->side()==-1);
			if(f->vac){
				f->vac++;
				for(;x->lson!=null;x=x->lson);
				x->splay();
				x->rson=null,x->up();
				return;
			}else if(f->lson==null){
				ans++;
				f->rson=x,f->up();
				if(f->fa!=null){
					f->fa->gvac();
					assert(f->fa->vac);
					f->fa->vac--;
					if(f->fa->vac==0){
						ans--;
						x=f->fa;
						continue;
					}
				}
				return;
			}else{
				f->rson=x,f->up();
				x=f;
			}
		}
		pool->splay();
		assert((pool->rson->size&1)==0);
		pool->rson=null,pool->up();
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
#endif
	int n=ni,type=ni;
	using namespace T;
	init(),nn();
	int last=0;
	for(int i=1;i<=n;i++){
		node p=nn();
		p->fa=pool+(ni^(type*last));
		p->up();
		work(p);
		printf("%d\n",last=i+1-ans);
	}
	return 0;
}
