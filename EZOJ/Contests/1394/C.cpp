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
		if(x!=null){
			draw(x->fa),x->dn();
		}
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
	inline node fir_nod(node x){
		if(x==null)return null;
		node a=fir_nod(x->lson);
		if(a!=null)return a;
		if(!x->isedge)return x;
		return fir_nod(x->rson);
	}
	inline node las_nod(node x){
		if(x==null)return null;
		node a=las_nod(x->rson);
		if(a!=null)return a;
		if(!x->isedge)return x;
		return las_nod(x->lson);
	}
	lint work(node x){
		Info lhs=(Info){0,0,0},rhs=(Info){0,0,0};
		lint ans=LINF;
		for(int d;;x=x->son[d]){
			x->dn();
			if(x->isedge){
				lint val1=(lhs+x->lson->sum[0]).s+(rhs+x->rson->sum[1]+x->val).s;
				lint val2=(lhs+x->lson->sum[0]+x->val).s+(rhs+x->rson->sum[1]).s;
				d=val1!=val2?val1>val2:-1;
			}else{
				apmin(ans,(lhs+x->lson->sum[0]).s+(rhs+x->rson->sum[1]).s);
				lint val1=x->lson->sum[0].n;
				lint val2=x->rson->sum[1].n;
				d=val1!=val2?val1<val2:-1;
			}
			if(d==1){
				lhs=lhs+x->lson->sum[0]+x->val;
			}else if(d==0){
				rhs=rhs+x->rson->sum[1]+x->val;
			}else{
				node u=las_nod(x->lson),v=fir_nod(x->rson);
				if(u!=null){
					u->spa(),apmin(ans,u->lson->sum[0].s+u->rson->sum[1].s);
				}
				if(v!=null){
					v->spa(),apmin(ans,v->lson->sum[0].s+v->rson->sum[1].s);
				}
				return ans;
			}
			if(x->son[d]==null)break;
		}
		x->spa();
		return ans;
	}
}
lct::node nd[N],nde[N];
namespace brute{
	const int N=160000;
	const lint LINF=0x7f7f7f7f7f7f7f7fll;
	namespace T{
		const int E=N<<1;
		int to[E],bro[E],val[E],head[N],e=0;
		inline void init(){
			memset(head,-1,sizeof(head));
		}
		inline void ae(int u,int v,int w){
			to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
		}
		inline void add(int u,int v,int w){
			ae(u,v,w),ae(v,u,w);
		}
		int stk[N],ss;
		bool dfs(int x,int y,int f){
			if(x==y)return true;
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=f){
					stk[++ss]=i;
					if(dfs(v,y,x))return true;
					ss--;
				}
			}
			return false;
		}
	}
	int a[N],pt[N];
	Info lhs[N],rhs[N];
	int main(int n){
		for(int i=1;i<=n;i++){
			a[i]=ni;
		}
		T::init();
		for(int i=1;i<n;i++){
			int u=ni,v=ni;
			T::add(u,v,ni);
		}
		for(int tot=ni;tot--;){
			int tp=ni,u=ni,v=ni;
			if(tp==1){
				if(u==v){
					puts("0");
					continue;
				}
				using T::stk;
				using T::ss;
				T::ss=0;
				T::dfs(u,v,0);
				pt[0]=u;
				for(int i=1;i<=ss;i++){
					pt[i]=T::to[stk[i]];
				}
				assert(pt[ss]==v);
				lint ans=LINF;
				lhs[0]=(Info){0,a[pt[0]],0};
				for(int i=1;i<=ss;i++){
					lhs[i]=lhs[i-1]+(Info){T::val[stk[i]],0,0}+(Info){0,a[pt[i]],0};
				}
				rhs[ss+1]=(Info){0,0,0};
				for(int i=ss;i>=0;i--){
					rhs[i]=rhs[i+1]+(Info){i==ss?0:T::val[stk[i+1]],0,0}+(Info){0,a[pt[i]],0};
				}
				for(int i=0;i<=ss;i++){//all go to pt[i]
					apmin(ans,lhs[i].s+rhs[i].s);
				}
				printf("%lld\n",ans);
			}else{
				a[u]=v;
			}
		}
		return 0;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("conference.in","r",stdin);
	freopen("conference.out","w",stdout);
#endif
	int n=ni;
	if(n<=3000)return brute::main(n);
	lct::init();
	for(int i=1;i<=n;i++){
		nd[i]=lct::nn();
		nd[i]->val.n=ni;
		nd[i]->up();
	}
	for(int i=1;i<n;i++){
		using namespace lct;
		node u=nd[ni],v=nd[ni];
		nde[i]=nn();
		nde[i]->val.e=ni;
		nde[i]->isedge=true;
		nde[i]->up();
		chr(u),chr(v);
		u->fa=v->fa=nde[i];
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
