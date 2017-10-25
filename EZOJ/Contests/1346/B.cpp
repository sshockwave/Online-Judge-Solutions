#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
int que[N],qh=0,qt=0;
bool inque[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		set<int>e;
		bool zero,one;
		inline void up(){
			if(l==r){
				zero=true,one=false;
			}else{
				zero=lson->zero||rson->zero;
				one=lson->one||rson->one;
			}
			if(e.size()==1){
			one=zero,zero=false;
			}else if(e.size()>1){
				one=zero=false;
			}
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->zero=true,x->one=false;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void psh(node x){
		assert(x->e.size()==1);
		int e=*(x->e.begin());
		if(!inque[e]){
			inque[e]=true,que[qt++]=e;
		}
	}
	void addque(node x,int upsum=0){
		if(upsum||!x->one){
			return;
		}
		if(!x->e.empty()){
			psh(x);
		}else{
			addque(x->lson),addque(x->rson);
		}
	}
	void add(node x,int l,int r,int e,int upsum=0){
		if(x->l==l&&x->r==r){
			if(e>0){
				x->e.insert(e);
				x->up();
			}else{
				x->e.erase(-e);
				x->up();
				addque(x,upsum);
			}
			return;
		}
		upsum+=x->e.size();
		if(r<=x->m){
			add(x->lson,l,r,e,upsum);
		}else if(l>x->m){
			add(x->rson,l,r,e,upsum);
		}else{
			add(x->lson,l,x->m,e,upsum);
			add(x->rson,x->m+1,r,e,upsum);
		}
		x->up();
		if(e<0&&x->one&&x->e.size()==1&&upsum-x->e.size()==0){
			psh(x);
		}
	}
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],idx[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		fa[1]=size[0]=dep[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		dep[x]=dep[fa[x]]+1;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	void dfs2(int x){
		idx[dfn[x]=++tim]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]){
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					dfs2(v);
				}
			}
		}
	}
	inline void alt(int u,int v,int w){
		for(;top[u]!=top[v];u=fa[top[u]]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
			seg::add(seg::rt,dfn[top[u]],dfn[u],w);
		}
		if(u!=v){
			if(dep[u]<dep[v]){
				swap(u,v);
			}
			seg::add(seg::rt,dfn[v]+1,dfn[u],w);
		}
	}
}
int u[N],v[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("redblue.in","r",stdin);
	freopen("redblue.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	seg::rt=seg::build(1,n),T::dfs1(1),T::dfs2(1);
	for(int i=1;i<n;T::alt(u[i]=ni,v[i]=ni,i),i++);
	memset(inque,0,sizeof(inque));
	seg::addque(seg::rt);
	for(int i;i=que[qh],qh<qt;qh++){
		T::alt(u[i],v[i],-i);
	}
	for(int i=1;i<n;i++){
		if(!inque[i]){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
