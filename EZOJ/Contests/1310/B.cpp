#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int n=ni,N=100010,TN=N*40;
int tim=0;
#define getter(fn)\
inline int fn(int x,int p){\
	q=p;\
	return fn(x,1,n);\
}
#define setter(fn,set)\
inline int fn(int x,int p,int v){\
	q=p,qv=v;\
	return set(x,1,n);\
}
namespace W{
	struct node{
		int lson,rson,tag,cnt;
	}pt[TN];
	int nn=1;
	inline void init(){
		pt[0]=(node){0,0,-1,0};
	}
	inline node* renew(int x){
		return pt+(pt[x].tag<tim?(pt[nn]=pt[x],pt[nn].tag=tim,nn++):x);
	}
	int q;
	int set(int xx,int l,int r){
		node* x=renew(xx);
		if(l==r){
			x->cnt=1;
		}else{
			int mid=(l+r)>>1;
			if(q<=mid){
				x->lson=set(x->lson,l,mid);
			}else{
				x->rson=set(x->rson,mid+1,r);
			}
			x->cnt++;
		}
		return x-pt;
	}
	int del(int xx,int l,int r){
		assert(pt[xx].cnt);
		if(pt[xx].cnt==1){
			return 0;
		}
		node* x=renew(xx);
		int mid=(l+r)>>1;
		if(q<=mid){
			x->lson=del(x->lson,l,mid);
		}else{
			x->rson=del(x->rson,mid+1,r);
		}
		x->cnt--;
		return x-pt;
	}
	int pre(int xx,int l,int r){
		node* x=pt+xx;
		if(x->cnt==0){
			return 0;
		}
		if(l==r){
			return l<q?l:0;
		}
		int mid=(l+r)>>1;
		if(q<=mid){
			return pre(x->lson,l,mid);
		}
		int res=pre(x->rson,mid+1,r);
		return res?res:pre(x->lson,l,mid);
	}
	int nxt(int xx,int l,int r){
		node* x=pt+xx;
		if(x->cnt==0){
			return n+1;
		}
		if(l==r){
			return l>q?l:n+1;
		}
		int mid=(l+r)>>1;
		if(q>mid){
			return nxt(x->rson,mid+1,r);
		}
		int res=nxt(x->lson,l,mid);
		return res<=n?res:nxt(x->rson,mid+1,r);
	}
	getter(set);getter(del);getter(pre);getter(nxt);
}
namespace R{
	struct node{
		int lson,rson,tag,val;
	}pt[TN];
	int root[N],nn=1;
	inline void init(){
		pt[0]=(node){0,0,-1,0};
		memset(root,0,sizeof(root));
	}
	inline node* renew(int x){
		return pt+(pt[x].tag<tim?(pt[nn]=pt[x],pt[nn].tag=tim,nn++):x);
	}
	int q,qv;
	int _set(int xx,int l,int r){
		node* x=renew(xx);
		if(l==r){
			x->val=qv;
			return x-pt;
		}
		int mid=(l+r)>>1;
		if(q<=mid){
			x->lson=_set(x->lson,l,mid);
		}else{
			x->rson=_set(x->rson,mid+1,r);
		}
		return x-pt;
	}
	int ask(int x,int l,int r){
		if(x==0){
			return 0;
		}
		if(l==r){
			return pt[x].val;
		}
		int mid=(l+r)>>1;
		if(q<=mid){
			return ask(pt[x].lson,l,mid);
		}else{
			return ask(pt[x].rson,mid+1,r);
		}
	}
	setter(set,_set);getter(ask);
}
namespace T{
	struct node{
		int lson,rson,tag,nxt,color;
		lint sum,diff;
		inline void up(int,int);
	}pt[TN];
	int root[N],nn=1;
	inline void init(){
		pt[0]=(node){0,0,-1,0,0,0ll,0ll};
		memset(root,0,sizeof(root));
	}
	inline node* renew(int x){
		return pt+(pt[x].tag<tim?(pt[nn]=pt[x],pt[nn].tag=tim,nn++):x);
	}
	int q,qv,ql,qr;
	inline lint all(int l,int r){
		return ((((lint)qv<<1)-l-r)*(r-l+1))>>1;
	}
	lint lim(int xx,int l,int r){
		assert(xx);
		node* x=pt+xx;
		if(x->nxt>=qv){
			return all(l,r);
		}
		if(l==r){
			return x->nxt-l;
		}
		int mid=(l+r)>>1;
		if(pt[x->rson].nxt<=qv){
			return lim(x->rson,mid+1,r)+pt[x->lson].sum+x->diff;
		}else{
			return lim(x->lson,l,mid)+all(mid+1,r);
		}
	}
	lint ask(int xx,int l,int r){
		node *x=pt+xx;
		if(ql<=l&&r<=qr){
			lint ans=lim(xx,l,r);
			apmin(qv,x->nxt);
			return ans;
		}
		int mid=(l+r)>>1;
		lint ans=0;
		if(qr>mid){
			ans+=ask(x->rson,mid+1,r);
		}
		if(ql<=mid){
			ans+=ask(x->lson,l,mid);
		}
		return ans;
	}
	inline lint ask(int x,int l,int r,int lim){
		qv=lim,ql=l,qr=r;
		return ask(x,1,n);
	}
	inline void node::up(int l,int r){
		assert(tag==tim);
		assert(lson&&rson);
		int mid=(l+r)>>1;
		if(pt[lson].nxt>=pt[rson].nxt){
			nxt=pt[rson].nxt;
			qv=pt[rson].nxt;
			sum=all(l,mid);
		}else{
			nxt=pt[lson].nxt;
			qv=pt[rson].nxt;
			sum=lim(lson,l,mid);
		}
		diff=sum-pt[lson].sum;
		sum+=pt[rson].sum;
	}
	int _setc(int xx,int l,int r){
		node* x=renew(xx);
		if(l==r){
			assert(q==l);
			x->color=qv;
		}else{
			int mid=(l+r)>>1;
			if(q<=mid){
				x->lson=_setc(x->lson,l,mid);
			}else{
				x->rson=_setc(x->rson,mid+1,r);
			}
		}
		return x-pt;
	}
	int askc(int x,int l,int r){
		assert(x);
		if(l==r){
			assert(q==l);
			return pt[x].color;
		}
		int mid=(l+r)>>1;
		if(q<=mid){
			return askc(pt[x].lson,l,mid);
		}else{
			return askc(pt[x].rson,mid+1,r);
		}
	}
	int _setn(int xx,int l,int r){
		node* x=renew(xx);
		if(l==r){
			assert(q==l);
			x->nxt=qv,x->sum=x->nxt-l;
			assert(x->diff==0);
		}else{
			int mid=(l+r)>>1;
			if(q<=mid){
				x->lson=_setn(x->lson,l,mid);
			}else{
				x->rson=_setn(x->rson,mid+1,r);
			}
			x->up(l,r);
		}
		return x-pt;
	}
	int *nxt,*color;
	int build(int l,int r){
		node* x=renew(0);
		if(l==r){
			x->color=color[l];
			x->nxt=nxt[l],x->sum=x->nxt-l;
			assert(x->diff==0);
		}else{
			int mid=(l+r)>>1;
			x->lson=build(l,mid);
			x->rson=build(mid+1,r);
			x->up(l,r);
		}
		return x-pt;
	}
	setter(setc,_setc);setter(setn,_setn);getter(askc);
}
lint ans=0;
inline int nd(){
	return (ans+ni)%n+1;
}
int main(){
	W::init(),R::init(),T::init();
	{
		int color[N],nxt[N],root[N];
		memset(root,0,sizeof(root));
		for(int i=1;i<=n;i++){
			color[i]=ni;
			root[color[i]]=W::set(root[color[i]],i);
		}
		R::root[0]=0;
		for(int i=1;i<=n;i++){
			if(root[i]){
				R::root[0]=R::set(R::root[0],i,root[i]);
			}
			root[i]=n+1;
		}
		for(int i=n;i>=1;i--){
			nxt[i]=root[color[i]];
			root[color[i]]=i;
		}
		T::color=color,T::nxt=nxt;
		T::root[0]=T::build(1,n);
	}
	for(int tot=ni;tot--;){
		int id=ni,t=ni;
		if(id==1){//alt
			tim++;
			int x=nd(),newc=nd(),oldc=T::askc(T::root[t],x);
			if(newc==oldc){
				T::root[tim]=T::root[t];
				R::root[tim]=R::root[t];
				continue;
			}
			int oldr=W::del(R::ask(R::root[t],oldc),x),newr=W::set(R::ask(R::root[t],newc),x);
			R::root[tim]=R::set(R::set(R::root[t],oldc,oldr),newc,newr);
			T::root[tim]=T::setn(T::setc(T::root[t],x,newc),x,W::nxt(newr,x));
			int pre=W::pre(oldr,x);
			if(pre){
				T::root[tim]=T::setn(T::root[tim],pre,W::nxt(oldr,pre));
			}
			pre=W::pre(newr,x);
			if(pre){
				T::root[tim]=T::setn(T::root[tim],pre,x);
			}
		}else{//ask
			int l=nd(),r=nd();
			printf("%lld\n",ans=T::ask(T::root[t],l,r,r+1));
		}
	}
}
