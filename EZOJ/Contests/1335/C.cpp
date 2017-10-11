#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <stack>
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
const int N=100010;
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
		int nxt,val;
		lint sum;
		inline int side(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void up(){
			sum=lson->sum+val+rson->sum;
		}
		inline void rot();
		inline void splay(){
			for(int d,fd;d=side(),~d;){
				fd=fa->side();
				if(fd==-1){
					rot();
					break;
				}else if(d==fd){
					fa->rot(),rot();
				}else{
					rot(),rot();
				}
			}
		}
	}null=(Node){&null,&null,&null,0,0,0};
	node bin[N*20],*bs=bin;
	inline void Node::rot(){
		bool d=!side();
		if(son[d]!=&null){
			son[d]->fa=fa;
		}
		fa->son[!d]=son[d],son[d]=fa;
		if(~fa->side()){
			fa->fa->son[fa->side()]=this;
		}
		fa=fa->fa,son[d]->fa=this;
		son[d]->up(),up();
	}
	inline node nn(node x=&null){
		static node n=new Node[N*20];
		return &(bs==bin?(*(n++)=*x):(**--bs=*x));
		return (*n=*x,n++);
	}
	node upbound(node x,int nxt){
		for(;x->nxt<=nxt&&x->rson!=&null;x=x->rson);
		if(x->lson==&null){
			return x;
		}
		node y=upbound(x->lson,nxt);
		return y->nxt>nxt?y:x;
	}
	void _ins(node x,node n){
		assert(x!=&null);
		assert(x->nxt!=n->nxt);
		bool d=n->nxt>x->nxt;
		if(x->son[d]==&null){
			x->son[d]=n;
			n->fa=x;
			n->lson=n->rson=&null;
			n->up();
		}else{
			_ins(x->son[d],n);
		}
		x->up();
	}
	inline node ins(node x,node n){
		if(x!=&null){
			x->splay();
			_ins(x,n);
			n->splay();
		}
		return n;
	}
	inline node get(node x,int nxt){//get node nxt
		for(;x!=&null&&x->nxt!=nxt;x=nxt<x->nxt?x->lson:x->rson);
		return x;
	}
	inline node del(node x,int nxt){
		node tmp=x;
		x->splay(),x=get(x,nxt);
		if(x==&null){
			return tmp;
		}
		x->splay();
		*(bs++)=x;
		if(x->rson==&null){
			x->lson->fa=&null;
			return x->lson;
		}
		node y=x->rson;
		for(;y->lson!=&null;y=y->lson);
		x->rson->fa=&null;
		y->splay();
		assert(y->lson==&null);
		y->lson=x->lson;
		if(x->lson!=&null){
			x->lson->fa=y;
		}
		y->up();
		return y;
	}
	node clone(node x){
		if(x==&null){
			return &null;
		}
		node y=nn(x);
		y->lson=clone(x->lson);
		y->rson=clone(x->rson);
		if(y->lson!=&null){
			y->lson->fa=y;
		}
		if(y->rson!=&null){
			y->rson->fa=y;
		}
		return y;
	}
	void putall(node x,node to,int nxt){//put all > nxt
		if(x==&null){
			return;
		}
		assert(x->nxt>nxt);
		to=ins(to,nn(x));
		if(x->lson->nxt>nxt){
			putall(x->lson,to,nxt);
		}
		putall(x->rson,to,nxt);
	}
}
int a[N],w[N];
int pre[N<<1],nxt[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		union{
			struct{
				node lson,rson;
			};
			node son[2];
		};
		T::node rt;
		inline void up(){
			lson->rt->splay();
			T::node tmp=T::upbound(lson->rt,r);
			tmp->splay();
			rson->rt->splay();
			rt=T::clone(rson->rt);
			if(tmp->nxt<=r){
				return;
			}
			putall(tmp,rt,r);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->rt=T::nn();
			x->rt->nxt=nxt[l];
			x->rt->sum=x->rt->val=w[a[l]];
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	inline void delnxt(int p){
		for(node x=rt;(nxt[p]>x->r?(x->rt=T::del(x->rt,nxt[p])):0),x->l!=x->r;x=x->son[p>x->m]);
	}
	inline void addnxt(int p){
		T::node n=T::nn();
		n->nxt=nxt[p];
		n->sum=n->val=w[a[p]];
		for(node x=rt;(nxt[p]>x->r?(x->rt=T::ins(x->rt,T::nn(n))):0),x->l!=x->r;x=x->son[p>x->m]);
		*(T::bs++)=n;
	}
	lint ask(node x,int l,int r){
		if(l<=x->l&&x->r<=r){
			x->rt->splay();
			T::node tmp=T::upbound(x->rt,r);
			tmp->splay();
			return tmp->nxt>r?tmp->rson->sum+tmp->val:0;
		}
		lint ans=0;
		if(l<=x->m){
			ans+=ask(x->lson,l,r);
		}
		if(r>x->m){
			ans+=ask(x->rson,l,r);
		}
		return ans;
	}
}
set<int>s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		s[a[i]].insert(i);
	}
	for(int i=1;i<=n;i++){
		w[i]=ni;
	}
	for(int c=1;c<=n;c++){
		s[c].insert(n+c);
		if(s[c].size()>1){
			int last=0;
			for(set<int>::iterator it=s[c].begin();it!=s[c].end();it++){
				int cur=*it;
				pre[cur]=last;
				nxt[last]=cur;
				last=cur;
			}
		}
	}
	seg::rt=seg::build(1,n);
	for(lint ans=0;tot--;){
		if(ni==1){
			lint p=nl^ans,c=nl^ans;
			if(a[p]==c){
				continue;
			}
			s[a[p]].erase(p);
			seg::delnxt(p);
			if(pre[p]){
				seg::delnxt(pre[p]);
				nxt[pre[p]]=nxt[p];
				seg::addnxt(pre[p]);
			}
			pre[nxt[p]]=pre[p];
			nxt[p]=*s[c].upper_bound(p);
			s[c].insert(p);
			pre[p]=pre[nxt[p]];
			pre[nxt[p]]=p;
			if(pre[p]){
				seg::delnxt(pre[p]);
				nxt[pre[p]]=p;
				seg::addnxt(pre[p]);
			}
			a[p]=c;
			seg::addnxt(p);
		}else{
			lint l=nl^ans,r=nl^ans;
			printf("%lld\n",ans=seg::ask(seg::rt,l,r));
		}
	}
	return 0;
}
