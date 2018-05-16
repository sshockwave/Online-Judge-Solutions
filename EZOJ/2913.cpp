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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,D=3;
namespace T{
	const int E=::N;
	int to[E],bro[E],head[N],e=0;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int fa[N],son[N],size[N],dep[N],top[N];
	inline void build(int n){
		mset(head+1,-1,n);
		fa[1]=0;
		for(int i=2;i<=n;i++){
			ae(fa[i]=ni,i);
		}
		mset(size,0,n+1);
		mset(son+1,0,n);
		for(int i=n;i>=2;i--){
			size[fa[i]]+=++size[i];
			if(size[i]>fa[i][son][size]){
				fa[i][son]=i;
			}
		}
		++size[1];
		assert(size[1]==n);
		dep[0]=-1;
		for(int x=1;x<=n;x++){
			dep[x]=dep[fa[x]]+1;
			top[x]=son[fa[x]]==x?top[fa[x]]:x;
		}
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
}
namespace lct{
	struct Node;
	typedef Node* node;
	node null;
	void draw(node);
	struct Node{
		union{
			struct{node lson,rson;};
			node son[2];
		};
		node fa;
		int size;
		int col,val;
		bool coltag;
		int cnt[D],sum[D];
		node lend,rend;
		inline void putcol(int c){
			if(this==null)return;
			coltag=true,val=sum[col=c]+size;
		}
		inline int sd(){return fa->lson==this?0:fa->rson==this?1:-1;}
		inline void up(){
			size=lson->size+1+rson->size;
			for(int i=0;i<D;i++){
				sum[i]=lson->sum[i]+cnt[i]+rson->sum[i];
			}
			val=sum[col]+size;
			assert(!coltag);
			lend=lson!=null?lson->lend:this;
			rend=rson!=null?rson->rend:this;
		}
		inline void dn(){
			if(coltag){
				lson->putcol(col);
				rson->putcol(col);
				coltag=false;
			}
		}
		inline void rot(){
			assert(sd()!=-1);
			bool d=!sd();
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			int g=fa->sd();
			fa=fa->fa,son[d]->fa=this;
			if(g!=-1){
				fa->son[g]=this;
			}
			son[d]->up(),up();
		}
		inline void spa(){
			assert(this!=null);
			draw(this);
			for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
		}
	}pool[N],Null;
	void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa);
		}
		x->dn();
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
		null->lend=null->rend=null;
	}
	inline void acc_col(node x){
		int pval=0;
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			if(s!=null&&x->col!=s->col)break;
			if(x->rson!=null){
				x->cnt[x->rson->col]+=x->rson->val;
			}
			x->rson=s;
			x->cnt[s->col]-=pval;
			pval=x->val;
			x->up();
		}
	}
	inline void set_col(node x,const node w,const int c){
		node s=null;
		int pval=0;
		for(;x!=w;s=x,x=x->fa){
			x->spa();
			if(x->rson!=null){
				x->cnt[x->rson->col]+=x->rson->val;
			}
			x->rson=s;
			x->cnt[s->col]-=pval;
			pval=x->val;
			x->up();
		}
		x->spa();
		assert(x->col==c);
		const node t=x->fa;
		if(t!=null){
			t->spa();
			assert(t->col!=c);
			t->cnt[c]-=x->val;
		}
		x->cnt[s->col]-=pval;
		s->putcol(c);
		x->cnt[c]+=s->val;
		x->up();
		if(t!=null){
			assert(t->sd()==-1);
			t->cnt[c]+=x->val;
			t->up();
		}
	}
}
lct::node nd[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("enos.in","r",stdin);
	freopen("enos.out","w",stdout);
#endif
	int n=ni,q=ni;
	T::build(n);
	lct::init();
	for(int i=1;i<=n;i++){
		using namespace lct;
		nd[i]=nn();
		nd[i]->col=0;
		nd[i]->cnt[0]=T::size[i]-1;
		nd[i]->up();
		if(i>1){
			nd[i]->fa=nd[T::fa[i]];
		}
	}
	while(q--){
		if(ni==1){//alt
			lct::node u,v,w;
			{
				int x=ni,y=ni;
				u=nd[x],v=nd[y],w=nd[T::lca(x,y)];
			}
			const int c=ni;
			lct::acc_col(w);
			w->spa();
			if(w->col!=c){//change w's color
				using namespace lct;
				if(w->lson!=null){
					int pval=w->val;
					node t=w->lson->rend;
					t->spa();
					assert(t->rson==w);
					t->rson=null;
					w->putcol(c);
					t->cnt[c]+=w->val;
					assert(t->val==pval);
					t->up();
					if(t->fa!=null){
						t->fa->spa();
						assert(t->fa->col!=t->col);
						t->fa->cnt[t->col]+=t->val-pval;
						t->fa->up();
					}
				}else if(w->fa!=null){
					node t=w->fa;
					acc_col(t);
					t->spa();
					t->cnt[w->col]-=w->val;
					w->putcol(c);
					t->cnt[c]+=w->val;
					int pval=t->val;
					t->up();
					if(pval!=t->val){
						if(t->fa!=null){
							assert(t->col==c);
							t->fa->spa();
							t->fa->cnt[c]+=t->val-pval;
							t->fa->up();
						}
						acc_col(w);
					}
				}else{
					w->putcol(c);
				}
			}
			lct::set_col(u,w,c);
			lct::set_col(v,w,c);
		}else{//ask
			const lct::node x=nd[ni];
			lct::acc_col(x);
			x->spa();
			printf("%d\n",x->val);
		}
	}
	return 0;
}
