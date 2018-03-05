#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <cstdlib>
#ifndef NDEBUG
#include <fstream>
#endif
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
namespace T{
	const int N=::N*20*5;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		//Treap
		node lson,rson;
		int size,tag;
		//Info
		int val,dt;
		lint sum;
		inline void addval(int x){
			if(this==null)return;
			dt+=x,sum+=(lint)size*x;
		}
		inline void up(){
			size=lson->size+1+rson->size;
			sum=lson->sum+val+rson->sum+(lint)size*dt;
		}
	}pool[N],Null;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
	}
	int tim=0;
	inline node nn(node x=null){
		static node n=pool;
		assert(n<pool+N);
		return x->tag<tim?*n=*x,n->tag=tim,n++:x;
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(rand()%(u->size+v->size)<u->size){
			u=nn(u);
			if(u->dt){
				v=nn(v),v->addval(-u->dt);
			}
			u->rson=mg(u->rson,v);
			u->up();
			return u;
		}else{
			v=nn(v);
			if(v->dt){
				u=nn(u),u->addval(-v->dt);
			}
			v->lson=mg(u,v->lson);
			v->up();
			return v;
		}
	}
	void sp(node x,int k,node &lhs,node &rhs){
		if(x==null)return lhs=rhs=null,void();
		if(k==0)return lhs=null,rhs=x,void();
		if(k==x->size)return lhs=x,rhs=null,void();
		x=nn(x);
		if(k<=x->lson->size){
			rhs=x;
			x->lson=nn(x->lson),x->lson->addval(x->dt);
			sp(x->lson,k,lhs,x->lson);
			x->lson->addval(-x->dt);
		}else{
			lhs=x;
			x->rson=nn(x->rson),x->rson->addval(x->dt);
			sp(x->rson,k-x->lson->size-1,x->rson,rhs);
			x->rson->addval(-x->dt);
		}
		x->up();
	}
	lint sum(node x,lint k){
		if(x==null||k==0)return 0;
		if(k==x->size)return x->sum;
		lint ans;
		if(k<=x->lson->size){
			ans=sum(x->lson,k);
		}else{
			ans=x->lson->sum+x->val+sum(x->rson,k-x->lson->size-1);
		}
		return ans+k*x->dt;
	}
}
T::node build(int l,int r){
	using namespace T;
	if(l>r)return null;
	node x=nn();
	int m=(l+r)>>1;
	x->lson=build(l,m-1);
	x->val=ni;
	x->rson=build(m+1,r);
	x->up();
	return x;
}
#ifndef NDEBUG
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
#endif
int main(){
#ifndef ONLINE_JUDGE
	freopen("add.in","r",stdin);
	freopen("add.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	T::tim++;
	T::node rt=build(1,n);
	while(tot--){
		const int op=ni,l=ni,r=ni;
		using namespace T;
		if(op==1){
			node lhs,rhs;
			tim++;
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
			rt=mg(mg(lhs,sect),rhs);
		}else{
			printf("%lld\n",sum(rt,r)-sum(rt,l-1));
		}
	}
	return 0;
}
