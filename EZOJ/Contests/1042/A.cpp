#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=100010,E=200010;
const lint LINF=0x7f7f7f7f7f7f7f7f;
bool good[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,r,m;
		node lson,rson;
		int mx;
		inline void up(){
			mx=max(lson->mx,rson->mx);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N*2];
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
			x->up();
		}
	}
	int ask(node x,int l,int r){
		assert(x->l<=l&&r<=x->r);
		if(x->l==l&&x->r==r){
			return x->mx;
		}
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return max(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r));
	}
}
namespace T{
	const int E=N*2;
	int to[E],bro[E],val[E],head[N],e=0;
	typedef int arr[N];
	arr fa,son,size,dep,top,dfn;
	inline void init(){
		memset(head,-1,sizeof(head));
		fa[1]=dep[1]=son[0]=size[0]=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs1(int x){
		size[x]=1,son[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	int tim=0;
	void dfs2(int x){
		dfn[x]=++tim;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]){
			dfs2(son[x]);
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x]){
				seg::set(seg::rt,dfn[x],val[i]);
			}else if(v!=son[x]){
				dfs2(v);
			}
		}
	}
	inline int ask(int u,int v){
		int ans=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
			apmax(ans,seg::ask(seg::rt,dfn[top[u]],dfn[u]));
			u=fa[top[u]];
		}
		if(u==v){
			return ans;
		}
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		return max(ans,seg::ask(seg::rt,dfn[v]+1,dfn[u]));
	}
}
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}e[E];
namespace uni{
	int fa[N];
	inline void init(){
		memset(fa,0,sizeof(fa));
	}
	int root(int x){
		if(fa[x]==0){
			return x;
		}
		return fa[x]=root(fa[x]);
	}
}
inline void Main456(int n,int tot){
	T::init();
	for(int i=0;i<tot;i++){
		e[i]=(Edge){ni,ni,ni};
	}
	sort(e,e+tot);
	uni::init();
	for(int i=0;i<tot;i++){
		int u=uni::root(e[i].u),v=uni::root(e[i].v);
		if(u!=v){
			T::add(e[i].u,e[i].v,e[i].w);
			uni::fa[u]=v;
		}
	}
	seg::rt=seg::build(1,n),T::dfs1(1),T::dfs2(1);
	for(tot=ni;tot--;){
		printf("%d\n",T::ask(ni,ni));
	}
}
namespace G{
	const int E=200010*2;
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
	lint dis[N];
	int que[N];
	bool inque[N];
	inline void spfa(int s,lint mx){
		memset(dis,127,sizeof(dis));
		memset(inque,0,sizeof(inque));
		int qh=0,qt=0;
		que[qt++]=s,inque[s]=true,dis[s]=0;
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			inque[x]=false;
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>dis[x]+val[i]&&dis[x]+val[i]<=mx){
					dis[v]=good[v]?0:dis[x]+val[i];
					if(!inque[v]){
						que[qt++]=v,inque[v]=true;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
			assert(!inque[x]);
		}
	}
}
lint mx=0;
inline lint work(int s,int t){
	lint l=0,r=mx;
	while(l<r){
		lint m=(l+r)>>1;
		G::spfa(s,m);
		if(G::dis[t]<LINF){
			r=m;
		}else{
			l=m+1;
		}
	}
	return l;
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
#endif
	G::init();
	int n=ni,tot=ni;
	scanf("%s",s+1);
	bool flag=true;
	for(int i=1;i<=n;i++){
		good[i]=s[i]=='1';
		if(!good[i]){
			flag=false;
		}
	}
	if(flag){
		Main456(n,tot);
		return 0;
	}
	while(tot--){
		int u=ni,v=ni,w=ni;
		mx+=w;
		G::add(u,v,w);
	}
	for(tot=ni;tot--;){
		int x=ni,y=ni;
		printf("%lld\n",work(x,y));
	}
	return 0;
}
