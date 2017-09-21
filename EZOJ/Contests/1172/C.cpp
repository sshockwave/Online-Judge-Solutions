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
const int N=110000,rtN=40;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	typedef int arr[N];
	arr fa,son,size,dep,top,dfn,id;
	inline void init(){
		memset(head,-1,sizeof(head));
		fa[1]=son[0]=size[0]=0,dep[1]=1;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		son[x]=0,size[x]=1;
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
		id[dfn[x]=tim++]=x;
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
	inline int go(int x,int n){
		while(n&&x){
			int d=min(n,dfn[x]-dfn[top[x]]);
			x=id[dfn[x]-d];
			n-=d;
			if(n){
				n--;
				x=fa[x];
			}
		}
		return x;
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline int ask1(int,int,int);
	inline int ask2(int,int,int);
}
int pval[N],R,C,n;
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int mx;
	}pol[N*2],*n;
	node build(int l,int r){
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			int r=l%R,c=l/R;
			x->mx=pval[T::id[r*C+c]];
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->mx=max(x->lson->mx,x->rson->mx);
		}
		return x;
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
seg::node rt;
inline int T::ask1(int u,int v,int k){
	int w=lca(u,v),ou=k-1,ov=(1+dep[u]-dep[w]+dep[v]-dep[w])%k;
	int R=(n-1)/k+1,ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]){
			swap(u,v),swap(ou,ov);
		}
		if(dfn[top[u]]<=dfn[u]-ou){
			int r=dfn[u]-ou,l=dfn[top[u]]+(r-dfn[top[u]])%k;
			assert(l<=r),assert(l%k==r%k);
			apmax(ans,seg::ask(rt,l%k*R+l/k,r%k*R+r/k));
		}
		ou=(ou-(dep[u]-dep[fa[top[u]]]))%k;
		if(ou<0){
			ou+=k;
		}
		u=fa[top[u]];
	}
	if(dep[u]<dep[v]){
		swap(u,v),swap(ou,ov);
	}
	assert(((dfn[u]-ou)%k+k)%k==((dfn[v]+ov)%k+k)%k);
	int l=dfn[v]+ov,r=dfn[u]-ou;
	if(l<=r){
		assert(l%k==r%k);
		apmax(ans,seg::ask(rt,l%k*R+l/k,r%k*R+r/k));
	}
	return ans;
}
inline int T::ask2(int u,int v,int k){
	int w=lca(u,v),ans=0;
	v=go(v,(1+dep[u]-dep[w]+dep[v]-dep[w])%k),u=go(u,k-1);
	for(;dep[u]>=dep[w];u=go(u,k)){
		apmax(ans,pval[u]);
	}
	for(;dep[v]>=dep[w];v=go(v,k)){
		apmax(ans,pval[v]);
	}
	return ans;
}
int u[N],v[N],k[N],lst[N],ans[N];
inline int lscmp(int a,int b){
	return k[a]<k[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	for(int i=1;i<=tot;i++){
		u[i]=ni,v[i]=ni,k[i]=ni,lst[i]=i;
	}
	sort(lst+1,lst+tot+1,lscmp);
	for(int i=1;i<=tot;i++){
		int q=lst[i];
		if(k[q]<=rtN){
			if(k[q]!=k[lst[i-1]]){
				C=k[q],R=(n-1)/C+1;
				seg::n=seg::pol;
				rt=seg::build(0,R*C-1);
			}
			ans[q]=T::ask1(u[q],v[q],k[q]);
		}else{
			ans[q]=T::ask2(u[q],v[q],k[q]);
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
