#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=100010,L=4;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int pval[N][L],len;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		lint dis[L][L];
		inline lint eval(){
			lint ans=-LINF;
			for(int i=0;i<len;i++){
				apmax(ans,dis[i][len-1]);
			}
			return ans;
		}
		inline void up(){
			for(int i=0;i<len;i++){
				for(int j=0;j<len;j++){
					lint &ans=dis[i][j]=-LINF;
					for(int k=0;k<len;k++){
						if(lson->dis[i][k]>-LINF&&rson->dis[k][j]>-LINF){
							apmax(ans,lson->dis[i][k]+rson->dis[k][j]);
						}
					}
				}
			}
		}
	}pool[N];
	node build(int l,int r);
}
namespace T{
	const int E=::N;
	int to[E],bro[E],head[N],e=0;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int fa[N],son[N],size[N],top[N];
	int dfn[N],idx[N];
	seg::node rt[N];
	struct state{
		int x,t;
		lint v;
		inline friend bool operator < (const state &a,const state &b){
			return a.v<b.v;
		}
	};
	priority_queue<state>q[N][L];
	int qtag[N];
	lint sumv[N];
	void calc(seg::node x,int p){
		if(x->l!=x->r)return calc(dfn[p]<=x->m?x->lson:x->rson,p),x->up();
		assert(x->l==dfn[p]);
		lint (*const f)[L]=x->dis;
		for(int i=0;i<len;i++){
			for(int j=0;j<len;j++){
				f[i][j]=-LINF;
			}
			priority_queue<state>&Q=q[p][i];
			for(;!Q.empty()&&Q.top().t<qtag[Q.top().x];Q.pop());
			if(!Q.empty()){
				lint t=Q.top().v;
				for(int j=0;j<len;j++){
					apmax(f[i][j],t+sumv[p]);
				}
			}
			if(i){
				apmax(f[i][i-1],sumv[p]);
			}else for(int j=0;j<len;j++){
				apmax(f[i][j],sumv[p]);
			}
			for(int j=0;j<len;j++){
				if(f[i][j]>-LINF){
					f[i][j]+=pval[p][i];
				}
			}
		}
	}
	lint prv[N];
	inline void putque(int x){
		assert(x!=1);
		++qtag[x];
		lint tmp=rt[x]->eval();
		sumv[fa[x]]+=tmp-prv[x];
		prv[x]=tmp;
		for(int i=0;i+1<len;i++){
			if(rt[x]->dis[i][len-1]>-LINF){
				q[fa[x]][i+1].push((state){x,qtag[x],rt[x]->dis[i][len-1]-tmp});
			}
		}
	}
	inline void init(int n){
		mset(head+1,-1,n);
		fa[1]=0;
		for(int i=2;i<=n;i++){
			ae(fa[i]=ni,i);
		}
	}
	inline void work(int n){
		mset(size+1,0,n);
		mset(son+1,0,n);
		for(int i=n;i>=2;i--){
			size[fa[i]]+=++size[i];
			if(size[i]>fa[i][son][size]){
				son[fa[i]]=i;
			}
		}
		++size[1];
		dfn[1]=1;
		for(int x=1;x<=n;x++){
			top[x]=x[fa][son]==x?x[fa][top]:x;
			idx[dfn[x]]=x;
			if(son[x]){
				dfn[son[x]]=dfn[x]+1;
				int tim=dfn[x]+size[son[x]];
				for(int i=head[x],v;~i;i=bro[i]){
					if((v=to[i])!=son[x]){
						dfn[v]=tim+1;
						tim+=size[v];
					}
				}
			}else{
				rt[top[x]]=seg::build(dfn[top[x]],dfn[x]);
			}
		}
		mset(sumv+1,0,n);
		mset(prv+1,0,n);
		for(int x=n;x>=1;x--){
			rt[x]=rt[top[x]];
			calc(rt[x],x);
			if(x==top[x]&&x!=1){
				putque(x);
			}
		}
	}
	void upd(int x){
		calc(rt[x],x);
		x=top[x];
		if(x!=1){
			putque(x),upd(fa[x]);
		}
	}
}
seg::node seg::build(int l,int r){
	static node n=pool;
	node x=n++;
	x->l=l,x->m=(l+r)>>1,x->r=r;
	if(l!=r){
		x->lson=build(l,x->m);
		x->rson=build(x->m+1,r);
	}
	return x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("decompose.in","r",stdin);
	freopen("decompose.out","w",stdout);
#endif
	int n=ni,q=ni;
	len=ni;
	T::init(n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<len;j++){
			pval[i][j]=ni;
		}
	}
	T::work(n);
	for(int i=1;i<=q;i++){
		int x=ni;
		for(int j=0;j<len;j++){
			pval[x][j]=ni;
		}
		T::upd(x);
		printf("%lld\n",T::rt[1]->eval());
	}
	return 0;
}
