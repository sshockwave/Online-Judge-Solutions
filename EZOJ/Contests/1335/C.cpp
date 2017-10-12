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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
const int N=100010,D=26;
int tim=0,totlen;
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		lint sum,delta;
		int tag;
		inline void up(){
			assert(delta==0);
			sum=lson->sum+rson->sum;
		}
	}null=(Node){&null,&null,0,0,-1};
	inline node renew(node x=&null){
		static node n=new Node[N*60];
		return x->tag==tim?x:(*n=*x,n->tag=tim,n++);
	}
	node add(node x,int v,int a,int b,int l=1,int r=totlen){
		if(a>b){
			return x;
		}
		x=renew(x);
		if(a==l&&b==r){
			x->sum+=v*(r-l+1);
			x->delta+=v;
			return x;
		}
		int m=(l+r)>>1;
		if(x->delta){
			x->lson=add(x->lson,x->delta,l,m,l,m);
			x->rson=add(x->rson,x->delta,m+1,r,m+1,r);
			x->delta=0;
		}
		if(b<=m){
			x->lson=add(x->lson,v,a,b,l,m);
		}else if(a>m){
			x->rson=add(x->rson,v,a,b,m+1,r);
		}else{
			x->lson=add(x->lson,v,a,m,l,m);
			x->rson=add(x->rson,v,m+1,b,m+1,r);
		}
		x->up();
		return x->sum?x:&null;
	}
	lint ask(node x,int a,int b,int l=1,int r=totlen){
		if(a>b||x==&null){
			return 0;
		}
		if(a==l&&b==r){
			return x->sum;
		}
		int m=(l+r)>>1;
		if(b<=m){
			return ask(x->lson,a,b,l,m)+(b-a+1)*x->delta;
		}
		if(a>m){
			return ask(x->rson,a,b,m+1,r)+(b-a+1)*x->delta;
		}
		return ask(x->lson,a,m,l,m)+ask(x->rson,m+1,b,m+1,r)+(b-a+1)*x->delta;
	}
}
seg::node rt[N];
namespace sam{
	struct Node;
	typedef Node* node;
	struct Node{
		node lnk,go[D];
		int len,pos;
	}pol[N*2],*pool=pol,*ini=pool++,*tail=ini;
	inline void init(){
		memset(pol,0,sizeof(pol));
	}
	inline void ext(int c){
		node p=tail;
		node np=tail=pool++;
		np->len=p->len+1;
		np->pos=++tim;
		rt[tim]=rt[tim-1];
		rt[tim]=seg::add(rt[tim],1,tim-np->len+1,tim);
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0){
			np->lnk=ini;
			return;
		}
		node q=p->go[c];
		if(q->len==p->len+1){
			np->lnk=q;
			for(;q!=ini;q=q->lnk){
				rt[tim]=seg::add(rt[tim],-1,q->pos-q->len+1,q->pos-q->lnk->len);
				q->pos=tim;
			}
			return;
			//todo::link cut tree
		}
		node nq=pool++;
		*nq=*q;
		nq->len=p->len+1;
		nq->pos=tim;
		q->lnk=np->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		rt[tim]=seg::add(rt[tim],-1,q->pos-nq->len+1,q->pos-nq->lnk->len);
		for(q=nq->lnk;q!=ini;q=q->lnk){
			rt[tim]=seg::add(rt[tim],-1,q->pos-q->len+1,q->pos-q->lnk->len);
			q->pos=tim;
		}
	}
}
struct Query{
	char c;
	int tp;
	lint l,r;
}q[N];
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("substring.in","r",stdin);
	freopen("substring.out","w",stdout);
#endif
	int d=ni;
	scanf("%s",s);
	totlen=strlen(s);
	int tot=ni;
	for(int i=1;i<=tot;i++){
		q[i].tp=ni;
		if(q[i].tp==1){
			totlen++;
			q[i].c=nc();
		}else{
			q[i].l=nl,q[i].r=nl;
		}
	}
	rt[0]=&seg::null;
	for(int i=0;s[i];i++){
		sam::ext(s[i]-'a');
	}
	lint ans=0;
	for(int i=1;i<=tot;i++){
		if(q[i].tp==1){
			sam::ext(d?(q[i].c-'a'+ans)%26:q[i].c-'a');
		}else{
			int l=d?(q[i].l-1+ans)%tim+1:q[i].l;
			int r=d?(q[i].r-1+ans)%tim+1:q[i].r;
			printf("%lld\n",ans=seg::ask(rt[r],l,r));
		}
	}
	return 0;
}
