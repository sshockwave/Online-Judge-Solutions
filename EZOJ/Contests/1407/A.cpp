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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=1000010,O=998244353;
namespace lct{
	struct Node;
	typedef Node* node;
	node grot(node);
	void draw(node);
	node null;
	struct Node{
		node fa;
		union{
			struct{node lson,rson;};
			node son[2];
		};
		bool rev;
		node unifa;
		int unisize;
		inline void putrev(){
			if(this==null)return;
			rev^=1,swap(lson,rson);
		}
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void dn(){
			if(rev){
				lson->putrev();
				rson->putrev();
				rev=false;
			}
		}
		inline void rot(){
			assert(sd()!=-1);
			bool d=!sd();
			assert(unifa==this);
			assert(fa->unifa==fa);
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			int g=fa->sd();
			fa=fa->fa,son[d]->fa=this;
			if(g!=-1){
				fa->son[g]=this;
			}
		}
		inline void spa(){
			draw(this);
			for(int d,fd;d=sd(),~d;fa=grot(fa),fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
		}
	}pool[N],Null;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
		null->unifa=null,null->unisize=0;
		null->rev=false;
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n->unifa=n,n->unisize=1,n++;
	}
	node grot(node x){
		if(x==null)return assert(x->unifa==null),x;
		return x->unifa!=x?x->unifa=grot(x->unifa):x;
	}
	void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa=grot(x->fa));
		}
		x->dn();
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x->fa=grot(x->fa),x=x->fa){
			x->spa();
			x->rson=s;
		}
	}
	inline void chr(node x){
		acc(x),x->spa(),x->putrev();
	}
	void setall(node x,node rt){
		if(x==null)return;
		assert(x->unifa==x);
		x->unifa=rt,rt->unisize+=x->unisize;
		setall(x->lson,rt);
		setall(x->rson,rt);
	}
}
lct::node nd[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
#endif
	int n=ni;
	lct::init();
	for(int i=1;i<=n;i++){
		nd[i]=lct::nn();
	}
	int ans=0;
	for(int tt=1,tot=ni;tt<=tot;tt++){
		int cur;
		using namespace lct;
		node u=grot(nd[ni]),v=grot(nd[ni]);
		if(u==v){//bi-connected
			cur=u->unisize;
		}else{
			chr(u),acc(v),v->spa();
			assert(v->fa==null);
			if(u->sd()!=-1){//sing-connected->bi-connected
				setall(v->lson,v);
				setall(v->rson,v);
				cur=v->unisize;
			}else{//unconnected->sing connected
				assert(u->fa==null);
				u->fa=v;
				cur=0;
			}
		}
		ans=(ans+(lint)cur*tt%O*tt)%O;
	}
	printf("%d\n",ans);
	return 0;
}
