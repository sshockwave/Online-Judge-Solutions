#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <fstream>
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
const int N=100010,INF=0x7f7f7f7f;
namespace T{//Treap
	const int N=::N*20*6;//TODO::check size
	struct Node;
	typedef Node* node;
	node null;
	inline node nn(node);
	struct Node{
		//Treap
		int son[2];
		int size,pri,tag;
		//Info
		int val,dt;
		lint sum;
		inline void addval(int x){
			val+=x,dt+=x,sum+=(lint)x*size;
		}
		inline node lson();
		inline node rson();
		inline void up(){
			assert(dt==0);
			size=lson()->size+1+rson()->size;
			sum=lson()->sum+val+rson()->sum;
		}
		inline void down();
	}pool[N],Null;
	inline node Node::lson(){
		return son[0]!=-1?pool+son[0]:null;
	}
	inline node Node::rson(){
		return son[1]!=-1?pool+son[1]:null;
	}
	inline int toid(node x){
		return x==null?-1:x-pool;
	}
	inline void Node::down(){
		if(dt){
			if(lson()!=null){
				son[0]=toid(nn(lson())),lson()->addval(dt);
			}
			if(rson()!=null){
				son[1]=toid(nn(rson())),rson()->addval(dt);
			}
		}
		dt=0;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->son[0]=null->son[1]=-1;
	}
	int tim=0;
	inline node nn(node x=null){
		static node n=pool;
		assert(n<pool+N);
		return x->tag<tim?*n=*x,n->pri=rand(),n->tag=tim,n++:x;
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(u->pri>v->pri){
			u=nn(u);
			u->down();
			u->son[1]=toid(mg(u->rson(),v));
			u->up();
			return u;
		}else{
			v=nn(v);
			v->down();
			v->son[0]=toid(mg(u,v->lson()));
			v->up();
			return v;
		}
	}
	void sp(node x,int k,node &lhs,node &rhs){
		if(x==null)return lhs=rhs=null,void();
		if(k==0)return lhs=null,rhs=x,void();
		if(k==x->size)return lhs=x,rhs=null,void();
		x=nn(x),x->down();
		if(k<=x->lson()->size){
			node lson;
			rhs=x,sp(x->lson(),k,lhs,lson);
			x->son[0]=toid(lson);
		}else{
			node rson;
			lhs=x,sp(x->rson(),k-x->lson()->size-1,rson,rhs);
			x->son[1]=toid(rson);
		}
		x->up();
	}
	lint sum(node x,int k){
		if(x==null||k==0)return 0;
		if(k<=x->lson()->size)return sum(x->lson(),k)+(lint)x->dt*k;
		return x->lson()->sum+x->val+sum(x->rson(),k-x->lson()->size-1)+(lint)x->dt*(k-1);
	}
}
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("add.in","r",stdin);
	freopen("add.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	T::node rt=T::null;
	for(int i=1;i<=n;i++){
		using namespace T;
		tim++;
		node x=nn();
		x->val=ni;
		x->up();
		x->tag=--tim;
		rt=mg(rt,x);
	}
	while(tot--){
		int op=ni,l=ni,r=ni;
		using namespace T;
		if(op==1){
			node lhs,rhs;
			//tim++;
			sp(rt,l-1,lhs,rt);
			sp(rt,r-l+1,rt,rhs);
			rt=nn(rt),rt->addval(ni);
			rt=mg(mg(lhs,rt),rhs);
		}else if(op==2){
			node sect,lhs,rhs;
			int size=ni+1;
			tim++;
			sp(rt,l-1,lhs,sect);
			sp(sect,size,sect,rhs);
			sp(rt,r-1,lhs,rt);
			sp(rt,size,rt,rhs);
			//tim++;
			rt=mg(mg(lhs,sect),rhs);
		}else{
			printf("%lld\n",sum(rt,r)-sum(rt,l-1));
		}
	}
	return 0;
}
