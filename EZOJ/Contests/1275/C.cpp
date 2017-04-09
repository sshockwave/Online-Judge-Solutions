#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=100010,E=200010,INF=0x7f7f7f7f;
struct Edge{
	int u,v,w;
	inline int other(int b){
		return u^v^b;
	}
}e[E];
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid,val;
	node *lson,*rson;
	SegmentTree(){
		val=INF;
	}
	void build(int l,int r){
		static node pool[E*4],*new_node=pool+1;
		lend=l,rend=r,mid=(l+r)>>1;
		if(l!=r){
			(lson=new_node++)->build(l,mid);
			(rson=new_node++)->build(mid+1,r);
		}
	}
	void alter(int x,int v){
		if(lend==rend){
			assert(x==lend);
			val=v;
		}else{
			(x<=mid?lson:rson)->alter(x,v);
			val=min(lson->val,rson->val);
		}
	}
	int ask(int l,int r){
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			return val;
		}
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return min(lson->ask(l,mid),rson->ask(mid+1,r));
	}
}rseg,tseg;
int bln[N];
struct Graph{
	typedef int info[N];
	int to[E*2],bro[E*2];
	info head;
	Graph(){
		memset(head,-1,sizeof(head));
	}
	inline void add_edge(int id,int u,int v){
		to[id]=v;
		bro[id]=head[u];
		head[u]=id;
	}
};
struct Undirected:Graph{
	info con,pos,st,end;
	Undirected(){
		memset(bln,0,sizeof(bln));
	}
	void dfs(int x,int fa){
		static bool vis[N]={0};
		static int stk[N],stop=0;
		vis[x]=true;
		stk[stop++]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v==fa){
				continue;
			}
			con[v]=i>>1;
			if(vis[v]){
				assert(bln[v]==0);
				static int ptop=1;
				st[v]=ptop;
				int u;
				do{
					u=stk[--stop];
					bln[u]=v;
					rseg.alter(ptop,e[con[u]].w);
					pos[con[u]]=ptop++;
				}while(u!=v);
				end[v]=ptop-1;
			}else{
				dfs(v,x);
			}
		}
		if(bln[x]==0){
			stop--;
			assert(stk[stop]==x);
			bln[x]=x;
		}
	}
	int ring(int u,int v){
		assert(bln[u]==bln[v]);
		if(u==v){
			return INF;
		}
		int ans=INF,s=st[bln[u]],t=end[bln[v]];
		u=pos[con[u]],v=pos[con[v]];
		if(u>v){
			swap(u,v);
		}
		if(u>s){
			apmin(ans,rseg.ask(s,u-1));
		}
		apmin(ans,rseg.ask(v,t));
		return ans+rseg.ask(u,v-1);
	}
}G;
struct Tree:Graph{
	info fa,son,size,dep,con,dfn,top;
	Tree(){
		size[0]=0;
		dep[1]=top[1]=1;
		memset(son,0,sizeof(son));
	}
	inline int ask(int x){
		return min(e[con[x]].v,G.ring(fa[x],bln[fa[x]]));
	}
	void dfs1(int x,int f){
		assert(bln[x]==x);
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				con[v]=i>>1;
				fa[v]=e[i>>1].other(v);
				dep[v]=dep[x]+1;
				dfs1(v,x);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	void dfs2(int x,int f){
		assert(bln[x]==x);
		static int tim=1;
		dfn[x]=tim++;
		if(son[x]){
			top[son[x]]=top[x];
			dfs2(son[x],x);
			tseg.alter(dfn[son[x]],ask(son[x]));
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(v!=son[x]&&v!=f){
					top[v]=v;
					dfs2(v,x);
				}
			}
		}
	}
	int query(int u,int v){
		assert(u!=v);
		if(bln[u]==bln[v]){
			return G.ring(u,v);
		}
		int ans=INF;
		while(top[bln[u]]!=top[bln[v]]){
			if(dep[top[bln[u]]]<dep[top[bln[v]]]){
				swap(u,v);
			}
			assert(dep[top[bln[u]]]>dep[top[bln[v]]]);
			if(u!=bln[u]){
				apmin(ans,G.ring(u,bln[u]));
				u=bln[u];
			}
			if(u!=top[u]){
				apmin(ans,tseg.ask(dfn[top[u]]+1,dfn[u]));
				u=top[u];
			}
			apmin(ans,e[con[u]].w);
			u=fa[u];
		}
		if(bln[u]==bln[v]){
			return min(ans,G.ring(u,v));
		}
		if(dep[bln[u]]<dep[bln[u]]){
			swap(u,v);
		}
		if(u!=bln[u]){
			apmin(ans,G.ring(u,bln[u]));
			u=bln[u];
		}
		if(dfn[u]>dfn[v]+1){
			apmin(ans,tseg.ask(dfn[v]+2,dfn[u]));
			u=son[v];
		}
		assert(u==son[v]);
		apmin(ans,e[con[u]].w);
		u=fa[u];
		return min(ans,G.ring(u,v));
	}
}T;
int main(){
	int n=ni(),m=ni();
	rseg.build(1,n),tseg.build(1,n);
	for(int i=1;i<=m;i++){
		e[i]=(Edge){ni(),ni(),ni()};
		G.add_edge(i<<1,e[i].u,e[i].v);
		G.add_edge((i<<1)|1,e[i].v,e[i].u);
	}
	G.dfs(1,0);
	for(int i=1,u,v;i<=m;i++){
		u=bln[e[i].u];
		v=bln[e[i].v];
		if(u!=v){
			T.add_edge(i<<1,u,v);
			T.add_edge((i<<1)|1,v,u);
		}
	}
	T.dfs1(1,0),T.dfs2(1,0);
	for(int tot=ni();tot--;){
		if(ni()){
			int eid=ni(),u,v;
			e[eid].w=ni();
			u=bln[e[eid].u];
			v=bln[e[eid].v];
			if(u==v){
				assert(G.pos[eid]);
				rseg.alter(G.pos[eid],e[eid].w);
				if(v=T.son[u]){
					tseg.alter(T.dfn[v],T.ask(v));
				}
			}
		}else{
			printf("%d\n",T.query(ni(),ni()));
		}
	}
}
