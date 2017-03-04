#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 30010
#define D (N*2)
#define lson(x) lson[x]
#define rson(x) rson[x]
#define INF 0x7f7f7f7f
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
int to[D],bro[D],head[N],etop=0,fa[N],dep[N],son[N],size[N],top[N],dfn[N],dtop=1,
	lson[D],rson[D],lend[D],rend[D],mid[D],sum[D],mx[D],ntop=0,root;
char s[10];
inline void add_edge(int u,int v,bool d){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
	if(d){
		add_edge(v,u,false);
	}
}
void dfs1(int x){
	dep[x]=dep[fa[x]]+1;
	son[x]=0;
	size[x]=1;
	for(int i=head[x],v;~i;i=bro[i]){
		v=to[i];
		if(v!=fa[x]){
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
	dfn[x]=dtop++;
	if(son[fa[x]]==x){
		top[x]=top[fa[x]];
	}else{
		top[x]=x;
	}
	if(son[x]){
		dfs2(son[x]);
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=fa[x]&&v!=son[x]){
				dfs2(v);
			}
		}
	}
}
int build(int l,int r){
	int x=ntop++;
	lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
	if(l==r){
		return x;
	}
	lson[x]=build(l,mid[x]);
	rson[x]=build(mid[x]+1,r);
	return x;
}
inline void push_up(int x){
	assert(lend[x]!=rend[x]);
	mx[x]=max(mx[lson(x)],mx[rson(x)]);
	sum[x]=sum[lson(x)]+sum[rson(x)];
}
void alter(int x,int i,int w){
	if(lend[x]==rend[x]){
		assert(lend[x]==i&&rend[x]==i);
		mx[x]=sum[x]=w;
		return;
	}
	if(i<=mid[x]){
		alter(lson(x),i,w);
	}else{
		alter(rson(x),i,w);
	}
	push_up(x);
}
typedef int(*joiner)(int,int);
int ask(int x,int l,int r,int *val,joiner join){
	assert(l<=r);
	if(l==lend[x]&&r==rend[x]){
		return val[x];
	}
	if(r<=mid[x]){
		return ask(lson(x),l,r,val,join);
	}else if(l>mid[x]){
		return ask(rson(x),l,r,val,join);
	}
	return join(ask(lson(x),l,mid[x],val,join),ask(rson(x),mid[x]+1,r,val,join));
}
int join_sum(int a,int b){
	return a+b;
}
int join_mx(int a,int b){
	return max(a,b);
}
int query(int u,int v,int *val,joiner join,int ans){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]){
			swap(u,v);
		}
		ans=join(ans,ask(root,dfn[top[u]],dfn[u],val,join));
		u=fa[top[u]];
	}
	if(u==v){
		return join(ans,ask(root,dfn[u],dfn[v],val,join));
	}
	if(dep[u]<dep[v]){
		swap(u,v);
	}
	return join(ans,ask(root,dfn[v],dfn[u],val,join));
}
int main(){
	int n=ni();
	memset(head,-1,sizeof(head));
	for(int i=1;i<n;i++){
		add_edge(ni(),ni(),true);
	}
	fa[1]=dep[0]=size[0]=son[0]=0;
	dfs1(1),dfs2(1),root=build(1,n);
	for(int i=1,w;i<=n;i++){
		scanf("%d",&w);
		alter(root,dfn[i],w);
	}
	for(int tot=ni(),u,v;tot--;){
		scanf("%s%d%d",s,&u,&v);
		if(s[0]=='C'){//change
			alter(root,dfn[u],v);
		}else if(s[1]=='M'){//qmax
			printf("%d\n",query(u,v,mx,join_mx,-INF));
		}else{//qsum
			printf("%d\n",query(u,v,sum,join_sum,0));
		}
	}
}
