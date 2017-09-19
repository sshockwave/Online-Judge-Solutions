#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=100010;
struct Info{
	int _mx,mx,mx_,sum;//mx has meaning only if it's calculating a chain
	inline friend Info operator + (const Info &a,const Info &b){
		assert(a._mx>=0&&a.mx>=0&&a.mx_>=0);
		assert(b._mx>=0&&b.mx>=0&&b.mx_>=0);
		Info c;
		c._mx=max(a._mx,a.sum+b._mx);
		c.mx=max(a.mx_+b._mx,max(a.mx,b.mx));
		c.mx_=max(a.mx_+b.sum,b.mx_);
		c.sum=a.sum+b.sum;
		assert(c._mx>=0&&c.mx>=0&&c.mx_>=0);
		return c;
	}
};
namespace seg2{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,r,m;
		node lson,rson;
		int mx;
	};
	node rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->r=r,x->m=(l+r)>>1;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void set(node x,int p,int v){
		if(x->l==x->r){
			assert(x->l==p);
			x->mx=v;
		}else{
			set(p<=x->m?x->lson:x->rson,p,v);
			x->mx=max(x->lson->mx,x->rson->mx);
		}
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,r,m;
		node lson,rson;
		Info info;
	};
	node acc[N],rt;
	node build(int l,int r){
		static node n=(node)memset(new Node[N<<1],0,sizeof(Node)*(N<<1));
		node x=n++;
		x->l=l,x->r=r,x->m=(l+r)>>1;
		if(l==r){
			acc[l]=x;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	Info ask(node x,int l,int r){
		assert(x->l<=l&&r<=x->r);
		if(x->l==l&&x->r==r){
			return x->info;
		}
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
	void set(node x,int p,const Info &info){
		if(x->l==x->r){
			assert(x->l==p);
			x->info=info;
		}else{
			set(p<=x->m?x->lson:x->rson,p,info);
			x->info=x->lson->info+x->rson->info;
		}
	}
}
int pval[N];
namespace T{
	typedef int arr[N];
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	arr fa,son,sz,dfn,top,end,topdfn;
	inline void init(){
		memset(head,-1,sizeof(head));
		fa[1]=sz[0]=son[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		sz[x]=1,son[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				sz[x]+=sz[v];
				if(sz[v]>sz[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	int tim=0,tim2=0;
	inline Info ginfo(int x){
		assert(x==top[x]);
		return seg::ask(seg::rt,dfn[x],dfn[end[x]]);
	}
	void dfs2(int x){
		dfn[x]=++tim;
		if(son[fa[x]]==x){
			top[x]=top[fa[x]];
		}else{
			top[x]=x;
			topdfn[x]=++tim2;
		}
		end[top[x]]=x;
		int sum=0;
		if(son[x]){
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					dfs2(v);
					sum+=ginfo(v)._mx;
				}
			}
		}
		sum+=pval[x];
		int tx=max(sum,0);
		seg::set(seg::rt,dfn[x],(Info){tx,tx,tx,sum});
	}
	inline void alt(int x,int dv){
		int t=top[x];
		int prev=ginfo(t)._mx;
		int sum=seg::acc[dfn[x]]->info.sum+dv;
		int tx=max(sum,0);
		seg::set(seg::rt,dfn[x],(Info){tx,tx,tx,sum});
		Info cur=ginfo(t);
		seg2::set(seg2::rt,topdfn[t],cur.mx);
		if(fa[t]){
			alt(fa[t],cur._mx-prev);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	T::init(),seg::rt=seg::build(1,n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	seg2::rt=seg2::build(1,T::tim2);
	for(int i=1;i<=n;i++){
		if(T::top[i]==i){
			seg2::set(seg2::rt,T::topdfn[i],T::ginfo(i).mx);
		}
	}
	while(tot--){
		if(ni==1){
			int x=ni,v=ni;
			T::alt(x,v-pval[x]);
			pval[x]=v;
		}else{
			printf("%d\n",seg2::rt->mx);
		}
	}
	return 0;
}
