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
const int N=100010;
namespace T{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int prior,size,val,mx;
		inline void up(){
			mx=max(max(lson->mx,rson->mx),val);
			size=lson->size+rson->size+1;
		}
	};
	node rt,null;
	inline void init(){
		rt=null=new Node;
		null->lson=null->rson=null;
		null->size=null->val=null->mx=0;
	}
	inline node nn(node x=null){
		static node n=new Node[N];
		return *n=*x,n->prior=rand(),n++;
	}
	void spsize(node x,int rnk,node &lt,node &rt){
		if(x==null)return lt=rt=x,void();
		if(rnk<=x->lson->size){
			rt=x,spsize(x->lson,rnk,lt,x->lson);
		}else{
			lt=x,spsize(x->rson,rnk-x->lson->size-1,x->rson,rt);
		}
		x->up();
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?(u->up(),u):(v->up(),v);
		if(u->prior>v->prior){
			return u->rson=mg(u->rson,v),u->up(),u;
		}else return v->lson=mg(u,v->lson),v->up(),v;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
#endif
	int n=ni;
	T::init();
	T::node l,r;
	int mx=0;
	for(int i=1;i<=n;i++){
		using namespace T;
		spsize(rt,ni,l,r);
		node p=nn();
		p->val=l->mx+1;
		apmax(mx,p->val);
		rt=mg(mg(l,p),r);
		printf("%d\n",mx);
	}
	return 0;
}
