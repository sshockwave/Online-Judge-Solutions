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
		int prior,len,size;
		lint a,d;
		inline void up(){
			size=len;
			if(lson){
				size+=lson->size;
			}
			if(rson){
				size+=rson->size;
			}
		}
	}*rt,pool[N<<1];
	inline void init(){
		memset(pool,0,sizeof(pool));
	}
	inline node nn(){
		static node n=pool-1;
		return n++,n->prior=rand(),n;
	}
	node merge(node u,node v){//u on left, v on right
		if(u==0||v==0){
			return u?u:v;
		}
		if(u->prior>v->prior){
			return u->rson=merge(u->rson,v),u->up(),u;
		}else{
			return v->lson=merge(u,v->lson),v->up(),v;
		}
	}
	inline ostream & operator << (ostream & out,node x){
		if(x==0)return out;
		out<<x->lson;
		if(x->d==-1){
			out<<"["<<x->a<<","<<x->a+x->d*(x->len-1)<<"]";
		}else{
			out<<"["<<x->a<<"](len="<<x->len<<")";
		}
		out<<"(size="<<x->size<<") ";
		out<<x->rson;
		return out;
	}
	node rootl,rootr;
	void split(node x,int size,node &l=rootl,node &r=rootr){
		if(x==0)return;
		int lsize=x->lson?x->lson->size:0;
		if(size<=lsize){
			node tmp=x->lson;
			r=x,x->size-=size;
			split(tmp,size,l,x->lson=0);
		}else if(size>=lsize+x->len){
			node tmp=x->rson;
			l=x,x->size=size;
			split(tmp,size-lsize-x->len,x->rson=0,r);
		}else{
			size-=lsize;
			node n=nn();
			n->rson=x->rson,x->rson=0;
			n->len=x->len-size,x->len=size;
			n->a=x->a+size*x->d,n->d=x->d;
			x->up(),n->up();
			l=x,r=n;
		}
	}
	lint getans(node x){
		lint ans=x->a+x->d*(x->len-1);
		if(x->lson){
			apmin(ans,getans(x->lson));
		}
		if(x->rson){
			apmin(ans,getans(x->rson));
		}
		return ans;
	}
}
int k;
inline lint Main(){
	int n=ni;
	k=ni;
	T::init();
	T::rt=T::nn();
	T::rt->len=T::rt->size=k;
	lint sum=0;
	for(int i=1;i<=n;i++){
		int a=ni,b=ni;
		sum+=a;
		using namespace T;
		rootl=rootr=0;
		if(b==1){//single way track
			if((a<<1)>k)return -1;
			split(rt,a<<1);
			node ch=rootl;
			for(;ch->rson;ch=ch->rson);
			lint val=ch->a+ch->d*(ch->len-1);
			node nd=nn();
			nd->len=rootl->size;
			nd->a=val+nd->len-1,nd->d=-1;
			nd->up();
			rt=merge(rootr,nd);
		}else{//two way track
			split(rt,(a<<1)%k);
			rt=merge(rootr,rootl);
		}
		assert(rt->size==k);
	}
	return (sum<<1)+T::getans(T::rt);
}
int main(){
	printf("%lld\n",Main());
	return 0;
}
