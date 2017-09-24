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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7f;
namespace T{
	const int N=500010;
	struct Node;
	typedef Node* node;
	struct Node{
		node A,B;
		node lson,rson;
		lint mk;
		int size;
		inline friend bool operator < (const Node &a,const Node &b){
			return a.A->mk!=b.A->mk?a.A->mk<b.A->mk:a.B->mk<b.B->mk;
		}
		inline friend bool operator == (const Node &a,const Node &b){
			return a.A==b.A&&a.B==b.B;
		}
		inline void up(){
			size=lson->size+rson->size+1;
		}
		inline bool bal(){
			return lson->size*10<=size*7&&rson->size*10<=size*7;
		}
	}*rt,null={0,0,0,0,-1,0};
	inline node nn(node l,node r){
		static node n=new Node[N];
		n->A=l,n->B=r;
		n->lson=n->rson=&null;
		n->size=1;
		return n++;
	}
	inline void init(){
		rt=nn(&null,&null);
		rt->mk=0;
	}
	node seq[N];
	int ss;
	void dfs(node x){
		if(x==&null){
			return;
		}
		dfs(x->lson),seq[++ss]=x,dfs(x->rson);
	}
	node build(int l,int r,lint rebl,lint rebr){
		if(l>r){
			return &null;
		}
		int m=(l+r)>>1;
		node x=seq[m];
		x->mk=rebl+((rebr-rebl)>>1);
		x->lson=build(l,m-1,rebl,x->mk-1);
		x->rson=build(m+1,r,x->mk+1,rebr);
		x->up();
		return seq[m];
	}
	bool inbal;
	node *balrt;
	lint rebl,rebr;
	inline node __ins(node &x,node n,lint l,lint r){//behaves like map[];
		assert(l<r);
		if(x==&null){
			x=n;
			x->mk=l+((r-l)>>1);
			return n;
		}
		if((*x)==(*n)){
			return x;
		}
		node ret=(*n<*x)?__ins(x->lson,n,l,x->mk-1):__ins(x->rson,n,x->mk+1,r);
		x->up();
		if(!x->bal()){
			inbal=true;
			balrt=&x;
			rebl=l,rebr=r;
		}
		return ret;
	}
	inline node ins(node l,node r){//behaves like map[]
		inbal=false;
		node x=__ins(rt,nn(l,r),0,LINF);
		if(inbal){
			ss=0,dfs(*balrt);
			*balrt=build(1,ss,rebl,rebr);
		}
		return x;
	}
}
T::node val[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int p;
	}*rt;
	inline int join(int a,int b){
		return val[a]->mk>=val[b]->mk?a:b;
	}
	node build(int l,int r){
		static node n=new Node[N*2];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->p=l;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void set(node x,int p){
		if(x->l!=x->r){
			set(p<=x->m?x->lson:x->rson,p);
			x->p=join(x->lson->p,x->rson->p);
		}
	}
	inline int ask(node x,int l,int r){
		assert(x->l<=l&&r<=x->r);
		if(x->l==l&&x->r==r){
			return x->p;
		}
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return join(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
#endif
	int n=ni;
	T::init(),seg::rt=seg::build(1,n);
	for(int i=1;i<=n;i++){
		val[i]=T::rt;
	}
	for(int tot=ni;tot--;){
		if(nc()=='C'){
			int l=ni,r=ni,p=ni;
			val[p]=T::ins(val[l],val[r]);
			seg::set(seg::rt,p);
		}else{
			int l=ni,r=ni;
			printf("%d\n",seg::ask(seg::rt,l,r));
		}
	}
	return 0;
}
