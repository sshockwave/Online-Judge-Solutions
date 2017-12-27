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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=400010;
struct Val{
	int val,cnt;
	inline Val operator + (int x){
		return (Val){val+x,cnt};
	}
	inline Val operator - (int x){
		return (Val){val-x,cnt};
	}
	inline friend bool operator < (const Val &a,const Val &b){
		return a.val<b.val;
	}
	inline friend bool operator > (const Val &a,const Val &b){
		return a.val>b.val;
	}
	inline friend Val min(const Val &a,const Val &b){
		return a<b?a:b<a?b:(Val){a.val,a.cnt+b.cnt};
	}
	inline friend Val max(const Val &a,const Val &b){
		return a>b?a:b>a?b:(Val){a.val,a.cnt+b.cnt};
	}
};
struct info{
	int len,top,sect;
	Val l,r,cur;
	inline Val eval(int x){
		return max(l-x,r+x);
	}
	inline void chroot(int pos){
		top=pos;
		cur=eval(pos);
	}
	inline pair<int,int>groot(int lenl,int lenr){
		assert(len==lenl+lenr-(sect<<1));
		int fir=lenl-sect;
		return make_pair(min(top,fir),sect+max(top-fir,0));
	}
	inline void gcomb(info &a,info &b){
		sect=min(a.len-a.top,b.top);
		len=a.len+b.len-(sect<<1);
		int fir=a.len-sect;
		l=max(a.l,b.eval(sect)+fir);
		r=max(a.eval(fir)-fir,b.r+sect-fir);
		assert(a.top<=fir);
		assert(b.top>=sect);
		if(a.top<fir){
			assert(b.top==sect);
			chroot(a.top);
		}else if(b.top>sect){
			assert(a.top==sect);
			chroot(b.top);
		}else{
			chroot(a.top);
		}
	}
};
namespace T{
	const int N=400010<<1;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		//treap info
		node fa,lson,rson;
		int size,prior;
		//chain info
		node pre,nxt;
		//edge info
		int fr,to;
		//route info
		info i,lm,all;
		bool tag;
		inline void putroot(int x){
			all.chroot(x);
			tag=true;
		}
		inline void down(){
			if(!tag)return;
			tag=false;
			if(rson==null){
				lm=all;
			}else{
				pair<int,int>rt=all.groot(lm.len,rson->all.len);
				lm.chroot(rt.first);
				rson->putroot(rt.second);
			}
			if(lson==null){
				i=lm;
			}else{
				pair<int,int>rt=all.groot(lson->all.len,i.len);
				lson->putroot(rt.first);
				i.chroot(rt.second);
			}
			assert(i.len==1);
		}
		inline void up(){
			assert(!tag);
			size=lson->size+1+rson->size;
			if(lson==null){
				lm=i;
			}else{
				lm.gcomb(lson->all,i);
				lson->fa=this;
			}
			if(lson==null){
				all=lm;
			}else{
				all.gcomb(lm,rson->all);
				rson->fa=this;
			}
		}
	}Null,pool[N];
	node pt[N],*n=pt;
	inline node coup(const node &x){
		return pool+((x-pool)^1);
	}
	inline node nn(node x=null){
		return **n=*x,(*n)->prior=rand(),*n++;
	}
	inline void del(node x){
		*--n=x;
	}
	inline node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(u->prior>v->prior){
			u->down();
			u->rson=mg(u->rson,v);
			u->up();
			return u;
		}else{
			v->down();
			v->lson=mg(u,v->lson);
			v->up();
			return v;
		}
	}
	inline void sp(node x,int rnk,node &l,node &r){
		if(x==null)return l=null,r=null,void();
		x->down();
		if(rnk<=x->lson->size){
			r=x;
			sp(x->lson,rnk,l,x->lson);
			x->up();
		}else{
			l=x;
			sp(x->rson,rnk-x->lson->size-1,x->rson,r);
			x->up();
		}
	}
	inline node gnode(node x,int rnk){
		x->down();
		if(rnk<=x->lson->size)return gnode(x->lson,rnk);
		if(rnk==x->lson->size+1)return x;
		return gnode(x->rson,rnk-x->lson->size-1);
	}
	node currt;
	int grank(node x,bool flag=true){
		int rank=0;
		if(x->fa==null){
			currt=x;
		}else{
			rank=grank(x->fa,x->fa->rson==x);
		}
		return rank+(flag?x->lson->size+1:0);
	}
	inline void init(){
		null=&Null;
		memset(null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
		null->pre=null->nxt=null;
		for(int i=0;i<N;i++){
			pt[i]=pool+i;
		}
	}
}
T::node chain[N];//out edge
inline int gedge(int x){//end edge rank
	using namespace T;
	node rtl,rtr;
	int rnk=grank(chain[x]);
	sp(currt,rnk-1,rtl,rtr);
	int len=rnk=0;
	for(node p=rtr;p!=null;p=p->rson){
		p->down();
		if(p->lson!=null){
			if(p->lson->all.top>len){
				p=p->lson;
				continue;
			}
			rnk+=p->lson->size;
			len-=p->lson->all.top;
			len+=p->lson->all.len-p->lson->all.top;
		}
		if(p->i.top>len)break;
		rnk++;
		len+=p->i.top?-1:1;
		assert(len>=0);
	}
	assert(len==0);
	rnk+=rtl->size;
	mg(rtl,rtr)->fa=null;
	return rnk;
}//currt ready
inline void chroot(int x){
	using namespace T;
	if(chain[x]==null)return;//no son no fa
	int rnk=gedge(x);
	node p=gnode(currt,rnk);
	if(p->i.top){//has son
		p=pool[(p-pool)^1].nxt;
		if(p->i.top){//has fa
			rnk=grank(coup(p));
		}else return;//no fa
	}
	node rtl,rtr;
	sp(currt,rnk,rtl,rtr);
	mg(rtr,rtl)->fa=null;
}//currt ready
inline void insafter(T::node x,T::node n){
	n->pre=x,n->nxt=x->nxt;
	n->pre->nxt=n->nxt->pre=n;
}
inline void lnk(int fa,int x){
	using namespace T;
	node fx=nn(),xf=nn(),p;
	fx->fr=fa,fx->to=x;
	xf->fr=x,xf->to=fa;
	if(chain[x]==T::null){
		chain[x]=xf;
		xf->pre=xf->nxt=xf;
		p=mg(fx,xf);
	}else{
		grank(chain[x]);
		insafter(coup(gnode(currt,currt->size)),xf);
		p=mg(mg(fx,currt),xf);
	}
	if(chain[fa]==T::null){
		chain[fa]=fx;
		fx->pre=fx->nxt=fx;
	}else{
		node rtl,rtr;
		int rnk=gedge(fa);
		sp(currt,rnk,rtl,rtr);
		insafter(coup(gnode(rtl,rtl->size)),fx);
		p=mg(mg(rtl,p),rtr);
	}
	p->fa=null;
}
inline void delnode(T::node x){
	if(x->nxt==x){
		chain[x->fr]=T::null;
	}else{
		x->pre->nxt=x->nxt;
		x->nxt->pre=x->pre;
		if(chain[x->fr]==x){
			chain[x->fr]=x->nxt;
		}
	}
	T::del(x);
}
inline void cut(int x){
	using namespace T;
	int rnk=gedge(x);
	node rtl,rtm,rtr;
	sp(currt,rnk,rtl,rtr);
	node p;
	sp(rtr,1,p,rtr);
	rtl->fa=null;
	rnk=grank(coup(p));
	delnode(p);
	delnode(coup(p));
	sp(rtl,rnk,rtl,rtm);
	sp(rtl,rtl->size-1,rtl,p);
	mg(mg(rtl,rtm),rtr)->fa=null;
}
int fa[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("darkforest.in","r",stdin);
	freopen("darkforest.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	for(int i=1;i<=n;i++){
		chain[i]=T::null;
	}
	for(int i=1;i<=n;i++){
		fa[i]=ni;
		if(fa[i]){
			lnk(fa[i],i);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(fa[i]==0){
			if(chain[i]==T::null){
				ans++;
			}else{
				T::grank(chain[i]);
				assert(T::currt->all.len==0&&T::currt->all.top==0);
				ans+=T::currt->all.eval(0).cnt;
			}
		}
	}
	while(printf("%d\n",ans),tot--){
		if(ni==1){
			int x=ni,y=ni;
			chroot(x);
			lnk(y,x);
		}else{
			cut(ni);
		}
	}
	return 0;
}
