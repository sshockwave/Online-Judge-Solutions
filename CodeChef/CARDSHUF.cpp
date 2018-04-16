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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
namespace treap{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		int id;
		int size;
		int pri;
		bool rev;
		inline void putrev(){
			if(this==null)return;
			rev^=1;
			swap(lson,rson);
		}
		inline void up(){
			size=lson->size+1+rson->size;
		}
		inline void dn(){
			if(rev){
				lson->putrev();
				rson->putrev();
				rev=false;
			}
		}
	}pool[N],Null;
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n->pri=rand(),n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		u->dn(),v->dn();
		if(u->pri>v->pri){
			u->rson=mg(u->rson,v);
			u->up();
			return u;
		}else{
			v->lson=mg(u,v->lson);
			v->up();
			return v;
		}
	}
	void sp(node x,int k,node &lhs,node &rhs){
		if(x==null)return lhs=rhs=null,void();
		if(k==0)return lhs=null,rhs=x,void();
		if(k==x->size)return lhs=x,rhs=null,void();
		x->dn();
		if(k<=x->lson->size){
			rhs=x;
			sp(x->lson,k,lhs,x->lson);
		}else{
			lhs=x;
			sp(x->rson,k-x->lson->size-1,x->rson,rhs);
		}
		x->up();
	}
	void dfs(node x){
		if(x==null)return;
		dfs(x->lson),dfs(x->rson),x->up();
	}
	void dfs2(node x){
		if(x==null)return;
		x->dn();
		dfs2(x->lson);
		printf("%d ",x->id);
		dfs2(x->rson);
	}
}
treap::node stk[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cardshuf.in","r",stdin);
	freopen("cardshuf.out","w",stdout);
#endif
	int n=ni,m=ni,ss=0;
	treap::init();
	for(int i=n;i>=1;i--){
		treap::node x=treap::nn();
		x->id=i;
		stk[ss+1]=treap::null;
		for(;ss&&stk[ss]->pri<x->pri;ss--);
		if(ss){
			stk[ss]->lson=x;
		}
		x->rson=stk[ss+1];
		stk[++ss]=x;
	}
	treap::node rt=stk[1];
	treap::dfs(rt);
	for(int i=1;i<=m;i++){
		treap::node a,b,c;
		using treap::sp;
		using treap::mg;
		sp(rt,ni,a,rt);
		sp(rt,ni,b,rt);
		rt=mg(a,rt);
		sp(rt,ni,c,rt);
		b->putrev();
		rt=mg(c,mg(b,rt));
	}
	treap::dfs2(rt);
	putchar('\n');
	return 0;
}
