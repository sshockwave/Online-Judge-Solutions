#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
const int N=80010,D=4,INF=0x7f7f7f7f;
namespace valtreap{
	const int N=::N*30;
	struct Node;
	typedef Node* node;
	node pt[N],*n=pt,null;
	struct Node{
		node lson,rson;
		int pri;
		int val,size;
		inline void up(){
			size=lson->size+1+rson->size;
		}
	}pool[N],Null;
	inline node nn(node x=null){
		assert(n<pt+N);
		return **n=*x,n[0]->pri=rand(),n++[0];
	}
	inline node nn(int v){
		node x=nn();
		x->val=v;
		return x;
	}
	inline void del(node x){
		*(--n)=x;
	}
	void del_all(node x){
		if(x==null)return;
		del(x);
		del_all(x->lson);
		del_all(x->rson);
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		for(int i=0;i<N;i++){
			pt[i]=pool+i;
		}
	}
	void sp(node x,int val,node &lhs,node &rhs){
		if(x==null)return lhs=rhs=null,void();
		if(x->val<val){
			lhs=x;
			sp(x->rson,val,x->rson,rhs);
		}else{
			rhs=x;
			sp(x->lson,val,lhs,x->lson);
		}
		x->up();
	}
	void ins(node &x,node n){
		if(x==null){
			x=n;
			x->lson=x->rson=null;
		}else if(x->pri<n->pri){
			sp(x,n->val,n->lson,n->rson);
			x=n;
		}else{
			ins(n->val<x->val?x->lson:x->rson,n);
		}
		x->up();
	}
	int ask(node x,int val){//<=val
		int ans=0;
		while(x!=null){
			if(val<x->val){
				x=x->lson;
			}else if(val>x->val){
				ans+=x->lson->size+1;
				x=x->rson;
			}else{
				ans+=x->lson->size+1;
				break;
			}
		}
		return ans;
	}
}
namespace strtreap{
	struct Node;
	typedef Node* node;
	node null,rt;
	struct Node{
		/* SGT */
		node lson,rson;
		node lend,rend;
		/* Chain */
		node pre,nxt;
		/* String */
		int c;
		node str;
		int len;
		ull lval,mark,rval;
		/* Info */
		int v,lcp;
		int size,mn;
		valtreap::node val;
		inline void up(){
			lend=lson!=null?lson->lend:this;
			rend=rson!=null?rson->rend:this;
			size=lson->size+1+rson->size;
			assert(rval-lval>=10);
			mn=min(lcp,min(lson->mn,rson->mn));
		}
	}pool[N],Null;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		null->lend=null->rend=null;
		null->pre=null,null->nxt=pool;
		null->lval=0,null->rval=-1;
		null->str=null;
		null->lcp=null->mn=INF;
		null->val=valtreap::null;
	}
	inline node nn(node x=null){
		static node n=pool+1;
		return *n=*x,n++;
	}
	int ask_lcp(node x,node a,node b){
		if(x==null)return INF;
		if(a->mark>b->mark){
			swap(a,b);
		}
		if(a->mark<=x->lend->mark&&x->rend->mark<=b->mark)return x->mn;
		if(x->mark>b->mark)return ask_lcp(x->lson,a,b);
		if(x->mark<a->mark)return ask_lcp(x->rson,a,b);
		int ans=x->lcp;
		if(a->mark<x->mark){
			apmin(ans,ask_lcp(x->lson,a,b));
		}
		if(b->mark>x->mark){
			apmin(ans,ask_lcp(x->rson,a,b));
		}
		return ans;
	}
	inline bool operator < (const Node &a,const Node &b){
		return a.c!=b.c?a.c<b.c:a.str->mark<b.str->mark;
	}
	//[null,pool]
	node *reb;
	void ins(node &x,node n){//put pre & nxt in n
		if(x!=null){
			valtreap::ins(x->val,valtreap::nn(n->v));
			if(*n<*x){
				n->nxt=x;
				n->rval=x->mark-1;
				ins(x->lson,n);
			}else{
				n->pre=x;
				n->lval=x->mark+1;
				ins(x->rson,n);
			}
			x->up();
			if(x->lson->size*3>x->size*2||x->rson->size*3>x->size*2){
				reb=&x;
			}
			return;
		}
		x=n;
		x->mark=x->lval+((x->rval-x->lval)>>1);
		assert(x->lcp==INF);
		x->up();
		assert(x->val==valtreap::null);
		valtreap::ins(x->val,valtreap::nn(n->v));
		if(x->pre!=null){
			x->pre->nxt=x;
			x->pre->lcp=x->pre->c==x->c?ask_lcp(rt,x->pre->str,x->str->pre)+1:0;
		}
		if(x->nxt!=pool){
			x->nxt->pre=x;
			x->lcp=x->nxt->c==x->c?ask_lcp(rt,x->str,x->nxt->str->pre)+1:0;
		}
		x->up();
	}
	node lst[N];
	int numa[N],numb[N];
	inline void dfs(valtreap::node x,int num[],int &n){
		if(x==valtreap::null)return;
		dfs(x->lson,num,n);
		num[++n]=x->val;
		dfs(x->rson,num,n);
		x->up();
	}
	valtreap::node stk[N];
	int ss;
	inline void psh(valtreap::node x){
		stk[ss+1]=valtreap::null;
		for(;ss>=1&&stk[ss]->pri<x->pri;ss--);
		if(ss){
			stk[ss]->rson=x;
		}
		x->lson=stk[ss+1],x->rson=valtreap::null;
		stk[++ss]=x;
	}
	node build(int l,int r,ull lval,ull rval){
		if(l>r)return null;
		int m=(l+r)>>1;
		node x=lst[m];
		x->lval=lval,x->mark=lval+((rval-lval)>>1),x->rval=rval;
		x->lson=build(l,m-1,lval,x->mark-1);
		x->rson=build(m+1,r,x->mark+1,rval);
		int na=0,nb=0;
		dfs(x->lson->val,numa,na);
		dfs(x->rson->val,numb,nb);
		numa[na+1]=numb[nb+1]=INF;
		ss=0,stk[1]=valtreap::null;
		for(int i=1,j1=1,j2=1;i<=na+nb;i++){
			psh(valtreap::nn(numa[j1]<numb[j2]?numa[j1++]:numb[j2++]));
		}
		valtreap::ins(x->val=stk[1],valtreap::nn(x->v));
		dfs(x->val,numa,na=0);
		x->up();
		return x;
	}
	void ins(node n){
		reb=0;
		ins(rt,n);
		if(reb==0)return;
		int ls=0;
		for(node x=(*reb)->lend;;x=x->nxt){
			valtreap::del_all(x->val);
			lst[++ls]=x;
			if(x==(*reb)->rend)break;
		}
		*reb=build(1,ls,(*reb)->lval,(*reb)->rval);
	}
	int ans;
	bool ask_lef(node x,node y,int l,int r){//does not include y
		if(x==null)return true;
		if(y->mark<=x->lend->mark)return true;
		if(y->mark<=x->mark)return ask_lef(x->lson,y,l,r);
		if(y->mark>x->rend->mark&&x->mn>=l)return ans+=valtreap::ask(x->val,r),true;
		if(!ask_lef(x->rson,y,l,r))return false;
		if(x->lcp<l)return false;
		ans+=x->v<=r;
		return ask_lef(x->lson,y,l,r);
	}
	bool ask_rig(node x,node y,int l,int r){//does not include y too
		if(x==null)return true;
		if(y->mark>x->mark)return ask_rig(x->rson,y,l,r);
		if(y->mark==x->mark)return x->lcp>=l&&ask_rig(x->rson,y,l,r);
		if(y->mark<x->lend->mark&&x->mn>=l)return ans+=valtreap::ask(x->val,r),true;
		if(!ask_rig(x->lson,y,l,r))return false;
		ans+=x->v<=r;
		if(x->lcp<l)return false;
		return ask_rig(x->rson,y,l,r);
	}
}
inline int gchar(){
	char c;
	while(!isalpha(c=getchar()));
	return c=='A'?0:c=='T'?1:c=='C'?2:3;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
#endif
	int n=ni,tot=ni;
	valtreap::init();
	strtreap::init();
	for(int i=1;i<=n;i++){
		using namespace strtreap;
		node x=nn();
		x->v=ni;
	}
	for(int i=1;i<n;i++){
		int u=ni;
		using namespace strtreap;
		node x=pool+ni;
		x->str=pool+u;
		x->c=gchar();
	}
	{
		using namespace strtreap;
		pool->mark=-1;
		rt=pool+1;
		rt->str=rt;
		rt->c=-1;
		rt->up();
		valtreap::ins(rt->val,valtreap::nn(rt->v));
		for(int i=2;i<=n;i++){
			ins(pool+i);
			pool[i].len=pool[i].str->len+1;
		}
	}
	for(int last=1;tot--;){
		using namespace strtreap;
		if(ni==0){//ask
			node x=pool+(ni^last);
			int l=ni,r=ni;
			ans=0;
			ask_lef(rt,x,l,r);
			ask_rig(rt,x,l,r);
			ans+=x->v<=r&&x->len>=l;
			if(ans){
				last=ans;
			}
			printf("%d\n",ans);
		}else{//grow
			node x=nn();
			x->str=pool+(ni^last);
			x->len=x->str->len+1;
			x->v=ni;
			x->c=gchar();
			ins(x);
		}
	}
	return 0;
}
