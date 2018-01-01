#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <map>
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
const int N=100010,C=13;
const lint LINF=0x7f7f7f7f7f7f7f7f;
lint banval[C];
map<lint,int>ban;
namespace T{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		//treap
		node lson,rson;
		int prior;
		//interval
		int l,r;
		lint val;
		//subtree info
		int len;
		lint sum,mn,mx;
		//tag
		bool tag;
		lint dt;
		inline int index(){
			map<lint,int>::iterator it=ban.lower_bound(val);
			return it!=ban.end()?it->second:C;
		}
		inline void setval(lint v){
			if(this==null)return;
			val=v,sum=v*len,mn+=v,mx+=v;
			tag=true,dt=v;
		}
		inline void addval(lint v){
			if(this==null)return;
			val+=v,sum+=v*len,mn+=v,mx+=v;
			dt+=v;
		}
		inline void up(){
			assert(!tag&&dt==0);
			len=lson->len+(r-l+1)+rson->len;
			sum=lson->sum+val*(r-l+1)+rson->sum;
			mn=min(val,min(lson->mn,rson->mn));
			mx=max(val,max(lson->mx,rson->mx));
		}
		inline void down(){
			if(tag){
				lson->setval(dt);
				rson->setval(dt);
				tag=false,dt=0;
			}else if(dt){
				lson->addval(dt);
				rson->addval(dt);
				dt=0;
			}
		}
	}Null,pool[N];
	node pt[N],*n=pt;
	node rt[C+1],nrt[C+1];
	inline node nn(node x=null){
		return **n=*x,(*n)->prior=rand(),*n++;
	}
	void del(node x){
		if(x==null)return;
		del(x->lson),*--n=x,del(x->rson);
	}
	inline void init(){
		for(int i=0;i<N;i++){
			pt[i]=pool+i;
		}
		null=&Null;
		memset(null,0,sizeof(Null));
		null->lson=null->rson=null;
		null->mn=LINF;
		for(int i=0;i<=C;i++){
			rt[i]=null;
		}
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(u->prior>v->prior){
			return u->down(),u->rson=mg(u->rson,v),u->up(),u;
		}else{
			return v->down(),v->lson=mg(u,v->lson),v->up(),v;
		}
	}
	node rtl,rtr,y;
	void _sp(node x,int m,node &lt,node &rt){
		if(x==null)return lt=rt=null,void();
		x->down();
		if(m<x->l){
			rt=x,_sp(x->lson,m,lt,x->lson),x->up();
		}else if(m>=x->r){
			lt=x,_sp(x->rson,m,x->rson,rt),x->up();
		}else{
			y=nn(x);
			x->r=m,y->l=m+1;
			x->rson=y->lson=null;
			x->up(),y->up();
			lt=x,rt=null;
		}
	}
	void sp(node x,int m,node &lt,node &rt){
		lt=rt=null;
		rtl=rtr=y=null;
		_sp(x,m,rtl,rtr);
		if(y!=null){
			rtr=mg(y,rtr);
		}
		lt=rtl,rt=rtr;
	}
	void ins(node &x,node y){
		if(x==null)return x=y,void();
		if(y->prior>x->prior){
			sp(x,y->l,y->lson,y->rson);
			(x=y)->up();
			return;
		}
		x->down();
		if(y->l<x->l){
			ins(x->lson,y);
		}else{
			ins(x->rson,y);
		}
		x->up();
	}
	void fixup(node &x,lint v){
		while(x->mx>v){
			assert(x!=null);
			x->down();
			if(x->val>v){
				node y=x;
				x=mg(x->lson,x->rson);
				y->lson=y->rson=null,y->up();
				ins(T::rt[y->index()],y);
			}else if(x->lson->mx>v){
				fixup(x->lson,v),x->up();
			}else if(x->rson->mx>v){
				fixup(x->rson,v),x->up();
			}else assert(false);
		}
	}
	lint gval(node x,int p){
		if(x==null)return -1;
		if(x->l<=p&&p<=x->r)return x->val;
		x->down();
		return gval(p<x->l?x->lson:x->rson,p);
	}
}
T::node lhs[C+1],rhs[C+1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("operation.in","r",stdin);
	freopen("operation.out","w",stdout);
#endif
	ban[banval[0]=233]=0;
	for(int i=1;i<C;i++){
		ban[banval[i]=banval[i-1]*10+3]=i;
	}
	int n=ni;
	ni;
	T::init();
	for(int i=1,j;i<=n;i++){
		T::node x=T::nn();
		x->l=x->r=i;
		x->val=ni;
		x->up();
		j=x->index();
		T::rt[j]=T::mg(T::rt[j],x);
	}
	for(int op;scanf("%d",&op)!=EOF;){
		if(op==1){
			int x=ni;
			lint val;
			for(int i=0;i<=C;i++){
				val=T::gval(T::rt[i],x);
				if(val!=-1)break;
			}
			printf("%lld\n",val);
		}else{
			int l=ni,r=ni;
			for(int i=0;i<=C;i++){
				T::sp(T::rt[i],l-1,lhs[i],T::rt[i]);
				T::sp(T::rt[i],r,T::rt[i],rhs[i]);
			}
			if(op==3){//addval
				for(int dt=ni;dt;){
					for(int i=C;i>=0;i--){
						T::rt[i]->addval(dt);
						if(i==C)continue;
						T::fixup(T::rt[i],banval[i]);
					}
					dt=0;
					for(int i=0;i<C;i++){
						if(T::rt[i]->mx==banval[i]){
							dt=1;
							break;
						}
					}
				}
				for(int i=0;i<=C;i++){
					T::rt[i]=T::mg(T::mg(lhs[i],T::rt[i]),rhs[i]);
				}
			}else{//setval
				T::node x=T::nn();
				x->l=l,x->r=r;
				if(op==2){
					x->val=ni;
				}else if(op==4){
					x->val=0;
					for(int i=0;i<=C;i++){
						apmax(x->val,T::rt[i]->mx);
					}
				}else if(op==5){
					x->val=LINF;
					for(int i=0;i<=C;i++){
						apmin(x->val,T::rt[i]->mn);
					}
				}else if(op==6){
					x->val=0;
					for(int i=0;i<=C;i++){
						x->val+=T::rt[i]->sum;
					}
					x->val=(long double)x->val/(r-l+1)+1e-9;
				}
				for(;ban.find(x->val)!=ban.end();x->val++);
				x->up();
				for(int i=0,j=x->index();i<=C;i++){
					T::del(T::rt[i]);
					if(i==j){
						T::rt[i]=T::mg(T::mg(lhs[i],x),rhs[i]);
					}else{
						T::rt[i]=T::mg(lhs[i],rhs[i]);
					}
				}
			}
		}
	}
	return 0;
}
