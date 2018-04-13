#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
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
const int N=100010,Q=300010,D=10;
inline lint C2(lint n){
	if(n<2)return 0;
	return (n*(n-1))>>1;
}
namespace seg{
	const int N=::N*20;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int lpos,rpos;
		lint sum;
		bool isnull;
		inline void up(){
			assert(!isnull);
			lpos=(lson->lpos<=m?lson:rson)->lpos;
			rpos=(rson->rpos>m?rson:lson)->rpos;
			sum=lson->sum;
			sum+=(lint)(lson->rpos-l+1)*(r-m);
			sum+=(lint)(m-lson->rpos)*(r-rson->lpos+1);
			sum+=rson->sum;
		}
	}pool[N];
	node rt;
	inline node nn(node x=pool){
		static node n=pool+1;
		return x->isnull?*n=*x,n->isnull=false,n++:x;
	}
	node build(int l,int r){
		node x=nn();
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->lpos=r+1,x->rpos=l-1;
		x->sum=0;
		x->isnull=true;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	node ins(node x,int p){
		x=nn(x);
		if(x->l==x->r){
			x->lpos=x->rpos=p;
			x->sum=1;
		}else{
			node &s=p<=x->m?x->lson:x->rson;
			s=ins(s,p);
			x->up();
		}
		return x;
	}
	node mg(node u,node v){
		if(u->isnull||v->isnull)return !u->isnull?u:v;
		u->lson=mg(u->lson,v->lson);
		u->rson=mg(u->rson,v->rson);
		u->up();
		return u;
	}
	struct Info{
		int lpos,rpos;
		lint sum;
	};
	Info ask(node x,int l){//from l to rend
		if(l==x->l)return (Info){x->lpos,x->rpos,x->sum};
		if(l>x->m)return ask(x->rson,l);
		Info tmp=ask(x->lson,l);
		tmp.sum+=(lint)(tmp.rpos-l+1)*(x->r-x->m);
		tmp.sum+=(lint)(x->m-tmp.rpos)*(x->r-x->rson->lpos+1);
		tmp.sum+=x->rson->sum;
		if(tmp.lpos==x->m+1){
			tmp.lpos=x->rson->lpos;
		}
		if(x->rson->rpos>x->m){
			tmp.rpos=x->rson->rpos;
		}
		return tmp;
	}
	inline int ask_pre(node x,int p){
		if(p==x->r)return x->rpos;
		if(x->lpos>p)return x->l-1;
		if(p<=x->m)return ask_pre(x->lson,p);
		int ans=ask_pre(x->rson,p);
		return ans>x->m?ans:ask_pre(x->lson,x->m);
	}
	inline int ask_nxt(node x,int p){
		if(p==x->l)return x->lpos;
		if(x->rpos<p)return x->r+1;
		if(p>x->m)return ask_nxt(x->rson,p);
		int ans=ask_nxt(x->lson,p);
		return ans<=x->m?ans:ask_nxt(x->rson,x->m+1);
	}
	lint ask2(node x,int l){
		if(l>x->rpos)return 0;
		return ask(x,l).sum-(x->rpos-l+1);
	}
	lint ask(node x,int l,int r){
		lint ans=ask2(x,l);
		if(r<x->r){
			ans-=ask2(x,r+1);
		}
		return ans;
	}
}
struct Query{
	int l,r;
	lint ans;
}qry[Q];
typedef vector<Query*>vq;
typedef vq::iterator iter;
namespace sam{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lnk,go[D];
		int len;
		seg::node rt;
		vq vec,qry;
		node head,bro;
		inline node ext(int);
	}pool[N];
	node pol=pool,ini;
	inline node nn(){
		return pol->rt=seg::rt,pol++;
	}
	inline void init(){
		ini=nn();
	}
	inline node Node::ext(int c){
		node p=this,np=nn();
		np->len=p->len+1;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0)return np->lnk=ini,np;
		node q=p->go[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		node nq=nn();
		nq->lnk=q->lnk;
		memcpy(nq->go,q->go,sizeof(nq->go));
		nq->len=p->len+1;
		q->lnk=np->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
	inline void ae(node u,node v){
		v->bro=u->head,u->head=v;
	}
	node stk[N];
	int ss=0;
	int n;
	void dfs(node x){
		stk[++ss]=x;
		for(iter it=x->vec.begin();it!=x->vec.end();++it){
			int l=1,r=ss;
			int len=(*it)->r-(*it)->l+1;
			while(l<r){
				int m=(l+r)>>1;
				if(stk[m]->len<len){
					l=m+1;
				}else{
					r=m;
				}
			}
			stk[l]->qry.push_back(*it);
		}
		for(node i=x->head;i;i=i->bro){
			dfs(i),x->rt=seg::mg(x->rt,i->rt);
		}
		for(iter it=x->qry.begin();it!=x->qry.end();++it){
			lint &ans=(*it)->ans=0;
			if(x->rt->lpos>x->rt->r)continue;
			int len=(*it)->r-(*it)->l+1;
			int a=x->rt->lpos,b=x->rt->rpos-len;
			assert(b<n);
			ans=C2(n-a)+C2(b)-C2(b-a+1);
			int pos=seg::ask_pre(x->rt,b);
			if(min(pos-len,a-1)>0){
				ans+=(lint)min(pos-len,a-1)*(n-b-1);
			}
			if(max(pos-len,0)<min(a-1,b-len)){
				assert(b<n);
				ans+=(lint)(min(a-1,b-len)-max(pos-len,0))*(n-seg::ask_nxt(x->rt,b+1));
			}
			if(max(len+1,b+1)<=min(n,a+len-1)){
				ans+=seg::ask(x->rt,max(len+1,b+1),min(n,a+len-1));
			}
		}
		ss--;
	}
	inline void main(){
		for(node i=ini+1;i<pol;i++){
			ae(i->lnk,i);
		}
		dfs(ini);
	}
}
inline bool lcmp(int a,int b){
	return qry[a].r<qry[b].r;
}
int lst[Q];
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cutting.in","r",stdin);
	freopen("cutting.out","w",stdout);
#endif
	int n=ni,q=ni;
	scanf("%s",s+1);
	for(int i=1;i<=q;i++){
		qry[i]=(Query){ni,ni};
		lst[i]=i;
	}
	sort(lst+1,lst+q+1,lcmp);
	seg::rt=seg::build(1,n),sam::init();
	sam::node p=sam::ini;
	for(int i=1,j=1;i<=n;i++){
		p=p->ext(s[i]-'0');
		p->rt=seg::ins(p->rt,i);
		for(;j<=q&&qry[lst[j]].r==i;j++){
			p->vec.push_back(qry+lst[j]);
		}
	}
	sam::n=n,sam::main();
	for(int i=1;i<=q;i++){
		printf("%lld\n",qry[i].ans);
	}
	return 0;
}
