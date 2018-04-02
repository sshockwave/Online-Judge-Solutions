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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=160000;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
struct Info{
	lint e,n,s;//all goes to right
	inline friend Info operator + (const Info &a,const Info &b){
		return (Info){a.e+b.e,a.n+b.n,(a.s+a.n*b.e)+b.s};
	}
};
namespace lct{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	node null;
	inline void draw(node);
	struct Node{
		union{
			node son[2];
			struct{node lson,rson;};
		};
		node fa;
		bool rev;
		bool isedge;
		Info sum[2],val;
		inline void putrev(){
			if(this==null)return;
			rev=!rev;
			swap(lson,rson);
			swap(sum[0],sum[1]);
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
		inline void up(){
			sum[0]=lson->sum[0]+val+rson->sum[0];
			sum[1]=rson->sum[1]+val+lson->sum[1];
		}
		inline void rot(){
			bool d=!sd();
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			int g=fa->sd();
			fa=fa->fa,son[d]->fa=this;
			if(~g){
				fa->son[g]=this;
			}
			son[d]->up(),up();
		}
		inline void spa(){
			draw(this);
			for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
		}
	}pool[N],Null;
	inline void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa);
		}
		x->dn();
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null->fa=null;
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			x->rson=s;
			x->up();
		}
	}
	inline void chr(node x){
		acc(x),x->spa(),x->putrev();
	}
	lint work(node x){
		Info lhs=(Info){0,0,0},rhs=(Info){0,0,0};
		lint ans=LINF;
		for(int d;;x=x->son[d]){
			x->dn();
			if(!x->isedge){
				apmin(ans,(lhs+x->lson->sum[0]).s+(rhs+x->rson->sum[1]).s);
			}
			lint val1=lhs.n+x->lson->sum[0].n;
			lint val2=rhs.n+x->rson->sum[1].n;
			if(val1==val2&&!x->isedge)break;
			if((d=val1<val2)){
				lhs=lhs+x->lson->sum[0]+x->val;
			}else{
				rhs=rhs+x->rson->sum[1]+x->val;
			}
			if(x->son[d]==null)break;
		}
		x->spa();
		return ans;
	}
}
lct::node nd[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("conference.in","r",stdin);
	freopen("conference.out","w",stdout);
#endif
	int n=ni;
	lct::init();
	for(int i=1;i<=n;i++){
		nd[i]=lct::nn();
		nd[i]->val.n=ni;
		nd[i]->up();
	}
	for(int i=1;i<n;i++){
		using namespace lct;
		node u=nd[ni],v=nd[ni],x=nn();
		x->val.e=ni;
		x->isedge=true;
		x->up();
		chr(u),chr(v);
		u->fa=v->fa=x;
	}
	for(int tot=ni;tot--;){
		using namespace lct;
		if(ni==1){
			node u=nd[ni],v=nd[ni];
			chr(u),acc(v),v->spa();
			printf("%lld\n",work(v));
		}else{
			node x=nd[ni];
			x->spa();
			x->val.n=ni;
			x->up();
		}
	}
	return 0;
}
