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
const int N=100010,E=200010,D=E,INF=0x7f7f7f7f;
struct Edge{
	int u,v,w;
	inline bool contain(int b){
		return u==b||v==b;
	}
	inline int other(int b){
		return u^v^b;
	}
}e[E];
#define lson(x) son[x][0]
#define rson(x) son[x][1]
struct SegmentTree{
	int lend[D],rend[D],mid[D],son[D][2],val[D],ntop;//root=1
	SegmentTree(){
		ntop=1;
		memset(val,127,sizeof(val));
	}
	int build(int l,int r){
		int x=ntop++;
		lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
		if(l!=r){
			lson(x)=build(l,mid[x]);
			rson(x)=build(mid[x]+1,r);
		}
		return x;
	}
	void alter(int p,int v,int x=1){
		if(lend[x]==rend[x]){
			assert(lend[x]==p);
			val[x]=v;
		}else{
			alter(p,v,son[x][p>mid[x]]);
			val[x]=min(val[lson(x)],val[rson(x)]);
		}
	}
	int ask_min(int l,int r,int x=1){
		assert(l<=r);
		assert(lend[x]<=l&&r<=rend[x]);
		if(l==lend[x]&&r==rend[x]){
			return val[x];
		}
		if(r<=mid[x]){
			return ask_min(l,r,lson(x));
		}
		if(l>mid[x]){
			return ask_min(l,r,rson(x));
		}
		return min(ask_min(l,mid[x],lson(x)),ask_min(mid[x]+1,r,rson(x)));
	}
}rseg,tseg;
struct Graph{
	int to[E*2],bro[E*2],head[N];
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
	int stk[N],stop,dfn[N],low[N],tim,bln[N],fa[N],con[N];
	bool instk[N];
	int pos[N],ptop,st[N],end[N],ntop;//pos[eid]
	Undirected(){
		stop=ntop=0;
		ptop=tim=1;
		memset(dfn,0,sizeof(dfn));
		memset(con,0,sizeof(con));
		memset(instk,0,sizeof(instk));
	}
	void tarjan(int x){
		dfn[x]=low[x]=tim++;
		stk[stop++]=x;
		instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(instk[v]){
				if(v!=fa[x]&&dfn[v]<dfn[x]){
					low[x]=dfn[v];
					con[v]=i>>1;
				}
			}else{
				assert(dfn[v]==0);
				fa[v]=x;
				con[v]=i>>1;
				tarjan(v);
				apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			ntop++;
			st[x]=ptop;
			int v;
			do{
				assert(stop>0);
				v=stk[--stop];
				bln[v]=x;
				if(con[v]){
					rseg.alter(ptop,e[con[v]].w);
				}
				pos[con[v]]=ptop++;
			}while(x!=v);
			end[x]=ptop-1;
			assert(st[x]<=end[x]);
		}
	}
	inline int ring(int u,int v){
		assert(bln[u]==bln[v]);
		if(u==v){
			return INF;
		}
		int b=bln[u],s=st[b],t=end[b];
		u=pos[con[u]],v=pos[con[v]];
		if(u>v){
			swap(u,v);
		}
		int ans=INF;
		if(u!=s){
			assert(u>s);
			apmin(ans,rseg.ask_min(s,u-1));
		}
		apmin(ans,rseg.ask_min(v,t));
		assert(u<v);
		return ans+rseg.ask_min(u,v-1);
	}
}g;
struct Tree:Graph{
	int fa[N],son[N],size[N],dep[N],con[N];
	int top[N],dfn[N],rdfn[N],tim;
	Tree(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		fa[1]=size[0]=son[0]=0;
		tim=top[1]=dep[1]=1;
	}
	inline void renew(int x){
		assert(son[x]);
		tseg.alter(dfn[son[x]],min(e[con[son[x]]].w,g.ring(x,fa[son[x]])));
	}
	void dfs1(int x){
		assert(x==g.bln[x]);
		size[x]=1;
		int bf=g.bln[fa[x]];
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=bf){
				fa[v]=e[i>>1].other(v);
				dep[v]=dep[x]+1;
				con[v]=i>>1;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	void dfs2(int x){
		dfn[x]=tim;
		rdfn[tim++]=x;
		if(son[x]){
			top[son[x]]=x;
			dfs2(son[x]);
			renew(x);
			int bf=g.bln[fa[x]];
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(v!=bf&&v!=son[x]){
					top[v]=v;
					dfs2(v);
				}
			}
		}
	}
	inline int approach(int &u,int v,int w){
		int ans=INF;
		if(g.bln[u]==g.bln[w]){
			ans=g.ring(u,w);
			u=w;
			return ans;
		}
		assert(dep[g.bln[u]]>dep[g.bln[w]]);
		if(u!=g.bln[u]){
			apmin(ans,g.ring(u,g.bln[u]));
			u=g.bln[u];
		}
		assert(w==g.bln[w]);
		int to=dfn[v];
		if(dfn[u]>to){
			apmin(ans,tseg.ask_min(to,dfn[u]));
			u=v;
		}
		assert(dfn[u]==to);
		apmin(ans,e[con[u]].w);
		u=fa[u];
		apmin(ans,g.ring(u,w));
		u=w;
		return ans;
	}
	inline int query(int u,int v){
		int ans=INF;
		while(top[g.bln[u]]!=top[g.bln[v]]){
			if(dep[top[g.bln[u]]]<dep[top[g.bln[v]]]){
				swap(u,v);
			}
			apmin(ans,approach(u,top[g.bln[u]],fa[top[g.bln[u]]]));
		}
		if(dep[g.bln[u]]<dep[g.bln[v]]){
			swap(u,v);
		}
		apmin(ans,approach(u,rdfn[dfn[v]+1],v));
		return ans;
	}
}t;
int main(){
	int n=ni(),m=ni();
	for(int i=1,u,v,w;i<=m;i++){
		e[i]=(Edge){ni(),ni(),ni()};
		g.add_edge(i<<1,e[i].u,e[i].v);
		g.add_edge((i<<1)|1,e[i].v,e[i].u);
	}
	rseg.build(1,m);
	g.fa[1]=0,g.tarjan(1);
	for(int i=1,u,v;i<=m;i++){
		u=g.bln[e[i].u];
		v=g.bln[e[i].v];
		if(u!=v){
			t.add_edge(i<<1,u,v);
			t.add_edge((i<<1)|1,v,u);
		}
	}
	assert(g.bln[1]==1);
	tseg.build(1,g.ntop);
	t.dfs1(1),t.dfs2(1);
	for(int tot=ni(),op,u,v;tot--;){
		if(ni()){
			int eid=ni();
			e[eid].w=ni();
			int u=g.bln[e[eid].u],v=g.bln[e[eid].v];
			if(u==v){
				rseg.alter(g.pos[eid],e[eid].w);
				assert(g.pos[eid]);
				t.renew(u);
			}else if(t.dep[u]<t.dep[v]){
				t.renew(u);
			}else{
				t.renew(v);
			}
		}else{
			printf("%d\n",t.query(ni(),ni()));
		}
	}
}
