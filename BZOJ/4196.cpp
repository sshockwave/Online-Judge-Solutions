#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 100010
#define D 200010
#define lson(x) sson[x][0]
#define rson(x) sson[x][1]
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int fa[N],to[N],bro[N],head[N],size[N],son[N],dfn[N],dfe[N],top[N],tim=0,etop=0,
	sum[D],sson[D][2],lend[D],rend[D],mid[D],ntop=0;
bool mark[D];
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
void dfs1(int x){
	size[x]=1;
	son[x]=-1;
	for(int i=head[x];~i;i=bro[i]){
		dfs1(to[i]);
		size[x]+=size[to[i]];
		if(son[x]==-1||size[son[x]]<size[to[i]]){
			son[x]=to[i];
		}
	}
}
void dfs2(int x){
	dfn[x]=tim++;
	if(~fa[x]&&son[fa[x]]==x){
		top[x]=top[fa[x]];
	}else{
		top[x]=x;
	}
	if(son[x]){
		dfs2(x);
	}
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=son[x]){
			dfs2(to[i]);
		}
	}
	dfe[x]=tim-1;
}
int build(int l,int r){
	int x=ntop++;
	lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1,sum[x]=0;
	if(l!=r){
		lson(x)=build(l,mid[x]);
		rson(x)=build(mid[x]+1,r);
	}
	return x;
}
inline void push_down(int x){
	if(lend[x]!=rend[x]&&mark[x]){
		if(sum[x]==0){
			sum[lson(x)]=sum[rson(x)]=0;
		}else{
			sum[lson(x)]=mid[x]-lend[x]+1;
			sum[rson(x)]=rend[x]-mid[x];
		}
		mark[lson(x)]=mark[rson(x)]=true;
	}
}
inline void push_up(int x){
	assert(lend[x]!=rend[x]);
	sum[x]=sum[lson(x)]+sum[rson(x)];
}
int query(int x,int l,int r){
	if(l==lend[x]&&r==rend[x]){
		return sum[x];
	}
	push_down(x);
	if(r<=mid[x]){
		return query(lson(x),l,r);
	}else if(l>mid[x]){
		return query(rson(x),l,r);
	}else{
		return query(lson(x),l,mid[x])+query(rson(x),mid[x]+1,r);
	}
}
void install(int x,int l,int r){
	if(l==lend[x]&&r==rend[x]){
		sum[x]=r-l+1;
		mark[x]=true;
		return;
	}
	push_down(x);
	if(r<=mid[x]){
		install(lson(x),l,r);
	}else if(l>mid[x]){
		install(rson(x),l,r);
	}else{
		install(lson(x),l,mid[x]);
		install(rson(x),mid[x]+1,r);
	}
	push_up(x);
}
void clear(int x,int l,int r){
	push_down(x);
	if(l==lend[x]&&r==rend[x]){
		sum[x]=0;
		mark[x]=true;
		return;
	}
	if(r<=mid[x]){
		clear(lson(x),l,r);
	}else if(l>mid[x]){
		clear(rson(x),l,r);
	}else{
		clear(lson(x),l,mid[x]);
		clear(rson(x),mid[x]+1,r);
	}
	push_up(x);
}
char s[15];
int main(){
//	freopen("4196.in","r",stdin);
	memset(head,-1,sizeof(head));
	int n=next_int();
	fa[0]=-1;
	for(int i=1;i<n;i++){
		add_edge(fa[i]=next_int(),i);
	}
	dfs1(0),dfs2(0);
	memset(son,-1,sizeof(son));
	memset(mark,0,sizeof(mark));
	int root=build(0,n-1);
	for(int tot=next_int(),x;tot--;){
		scanf("%s%d",s,&x);
		if(s[0]=='i'){
			int cnt=0;
			for(;~x;x=fa[top[x]]){
				cnt+=dfn[x]-dfn[top[x]]+1-query(root,dfn[top[x]],dfn[x]);
				install(root,dfn[top[x]],dfn[x]);
			}
			printf("%d\n",cnt);
		}else{
			printf("%d\n",query(root,dfn[x],dfe[x]));
			clear(x,dfn[x],dfe[x]);
		}
	}
}
