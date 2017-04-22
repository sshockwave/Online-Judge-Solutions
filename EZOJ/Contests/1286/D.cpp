#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=100010,E=N*2;
int pval[N];
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid,sum,delta;
	node *lson,*rson;
	inline void build(int,int);
	inline void up(){
		sum=lson->sum+rson->sum;
	}
	inline void down(){
		assert(lend!=rend);
		if(delta){
			lson->cover(lend,mid,delta);
			rson->cover(mid+1,rend,delta);
			delta=0;
		}
	}
	int ask(int l,int r){
		if(l>r){
			return 0;
		}
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			return sum;
		}
		down();
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return lson->ask(l,mid)+rson->ask(mid+1,r);
	}
	inline int operator [] (int x){
		return ask(x,x);
	}
	void cover(int l,int r,int c){
		if(l>r){
			return;
		}
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			sum+=(r-l+1)*c;
			delta+=c;
			return;
		}
		down();
		if(r<=mid){
			lson->cover(l,r,c);
		}else if(l>mid){
			rson->cover(l,r,c);
		}else{
			lson->cover(l,mid,c);
			rson->cover(mid+1,r,c);
		}
		up();
	}
}seg;
struct Tree{
	typedef int info[N];
	int to[E],bro[E],head[N];
	Tree(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		fa[1]=tim=dep[1]=size[0]=0;
		top[1]=1;
	}
	inline void add_edge(int u,int v){
		static int etop=0;
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	info fa,son,size,dep,top,dfn,st,end,id;
	void dfs1(int x,int f){
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs1(v,x);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	int tim;
	void dfs2(int x,int f){
		st[x]=tim+1;
		if(son[x]){
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(v!=f){
					id[dfn[v]=++tim]=v;
				}
			}
			end[x]=tim;
			top[son[x]]=top[x];
			dfs2(son[x],x);
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(v!=f&&v!=son[x]){
					top[v]=v;
					dfs2(v,x);
				}
			}
		}else{
			end[x]=tim;
		}
	}
	inline int ask(int u,int v){
		int ans=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
			ans+=seg.ask(st[top[u]],end[u]);
			u=fa[top[u]];
		}
		if(dep[u]>dep[v]){
			swap(u,v);
		}
		ans+=seg.ask(st[u],end[v])+seg[dfn[u]];
		if(fa[u]){
			ans+=seg[dfn[fa[u]]];
		}
		return ans;
	}
	inline void alter(int u,int v,int c){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
			seg.cover(st[top[u]],end[u],c);
			u=fa[top[u]];
		}
		if(dep[u]>dep[v]){
			swap(u,v);
		}
		seg.cover(st[u],end[v],c);
		seg.cover(dfn[u],dfn[u],c);
		if(fa[u]){
			seg.cover(dfn[fa[u]],dfn[fa[u]],c);
		}
	}
}T;
inline void SegmentTree::build(int l,int r){
	static node *n=new node[N*2];
	lend=l,rend=r,mid=(l+r)>>1;
	if(l==r){
		sum=pval[T.id[l]];
	}else{
		(lson=n++)->build(l,mid);
		(rson=n++)->build(mid+1,r);
		up();
	}
}
int main(){
	int n=ni;
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T.add_edge(u,v);
		T.add_edge(v,u);
	}
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	T.id[T.dfn[1]=++T.tim]=1;
	T.dfs1(1,0),T.dfs2(1,0);
	seg.build(1,n);
	for(int tot=ni;tot--;){
		if(ni==1){
			int x=ni,y=ni;
			T.alter(x,y,ni);
		}else{
			printf("%d\n",T.ask(ni,ni));
		}
	}
}
