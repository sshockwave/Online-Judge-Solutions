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
			x->lson=renew(x->lson),x->lson->sum+=x->delta*(m-l+1),x->lson->delta+=x->delta;
			x->rson=renew(x->rson),x->rson->sum+=x->delta*(r-m),x->rson->delta+=x->delta;
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
		node lnk,fa,go[D];
		static node null;
		union{
			struct{
				node lson,rson;
			};
			node son[2];
		};
		int len,pos;
		bool tag;
		inline int side(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void down(){
			if(tag){
				if(lson!=null){
					lson->pos=pos;
					lson->tag=true;
				}
				if(rson!=null){
					rson->pos=pos;
					rson->tag=true;
				}
				tag=false;
			}
		}
		inline void rot(){
			bool d=!side();
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			if(~fa->side()){
				fa->fa->son[fa->side()]=this;
			}
			fa=fa->fa,son[d]->fa=this;
		}
		inline void splay();
	}pool[N*2];
	node Node::null;
	node ini,tail;
	inline node nn(node x=Node::null){
		static node n=pool;
		return (*n=*x,n++);
	}
	inline void init(){
		Node::null=pool;
		memset(Node::null,0,sizeof(Node));
		Node::null=nn();
		Node::null->fa=Node::null->lson=Node::null->rson=Node::null;
		ini=tail=nn();
	}
	void draw(node x){
		if(x!=Node::null){
			draw(x->fa),x->down();
		}
	}
	inline void Node::splay(){
		draw(this);
		for(int d,fd;d=side(),~d;){
			fd=fa->side();
			if(fd==-1){
				rot();
				break;
			}else if(fd==d){
				fa->rot(),rot();
			}else{
				rot(),rot();
			}
		}
	}
	inline void acc(node x){
		for(node s=x;x=x->fa,x!=Node::null;s=x){
			x->splay();
			x->rson=s;
			if(x->pos!=tim){
				rt[tim]=seg::add(rt[tim],-1,x->pos-x->len+1,x->pos-x->fa->len);
				x->pos=tim,x->tag=true;
			}
		}
	}
	inline void ext(int c){
		node p=tail;
		node np=tail=nn();
		np->len=p->len+1;
		np->pos=++tim;
		rt[tim]=seg::add(rt[tim-1],1,1,tim);
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0){
			np->fa=np->lnk=ini;
			return;
		}
		node q=p->go[c];
		if(q->len==p->len+1){
			np->fa=np->lnk=q;
			acc(np);
			return;
		}
		q->splay();
		node nq=nn(q);
		if(q->lson!=Node::null){
			q->lson->fa=nq;
			q->lson=Node::null;
		}
		nq->len=p->len+1;
		nq->rson=Node::null;
		q->fa=q->lnk=np->fa=np->lnk=nq;
		acc(np);
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
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
	sam::init();
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
