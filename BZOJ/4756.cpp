#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
#define LEFT 0
#define RIGHT 1
#define ROOT -1
#define lson(x) son[x][0]
#define rson(x) son[x][1]
using namespace std;
inline bool isNum(char c) {
	return c>='0'&&c<='9';
}
inline int nextInt() {
	int i=0;
	char c;
	while(!isNum(c=getchar()));
	for(; isNum(c); i=i*10-'0'+c,c=getchar());
	return i;
}
int val[N],ans[N],to[N],bro[N],head[N],etop=0,fa[N],side[N],son[N][2],size[N];
inline void push_up(int x) {
	size[x]=size[lson(x)]+size[rson(x)]+1;
}
inline void rotate(int x) {
	bool d=side[x];
	son[fa[x]][d]=son[x][!d];
	if(son[x][!d]){
		fa[son[x][!d]]=fa[x];
		side[son[x][!d]]=d;
	}
	push_up(fa[x]);
	side[x]=side[fa[x]];
	side[fa[x]]=!d;
	son[x][!d]=fa[x];
	fa[x]=fa[fa[x]];
	fa[son[x][!d]]=x;
	if(side[x]!=ROOT) {
		son[fa[x]][side[x]]=x;
	}
	push_up(x);
	//tocheck
}
inline void splay(int x) {
	while(side[x]!=ROOT) {
		if(side[fa[x]]==ROOT) {
			rotate(x);
		} else if(side[fa[x]]==side[x]) {
			rotate(fa[x]),rotate(x);
		} else {
			rotate(x),rotate(x);
		}
	}
}
void insert(int x,int node) {
	int &s=son[x][val[node]>val[x]];
	size[x]++;
	if(s) {
		insert(s,node);
		return;
	}
	s=node;
	fa[s]=x;
	side[s]=val[s]>val[x];
	lson(s)=rson(s)=0;
	size[s]=1;
	splay(s);
}
void merge_dfs(int u,int v) {
	if(v==0) {
		return;
	}
	merge_dfs(u,lson(v)),merge_dfs(u,rson(v));
	splay(u);
	insert(u,v);
}
inline void merge(int u,int v) {
	splay(u),splay(v);
	if(size[u]<size[v]) {
		swap(u,v);
	}
	merge_dfs(u,v);
}
void dfs(int x) {
	for(int i=head[x]; ~i; i=bro[i]) {
		dfs(to[i]);
		merge(x,to[i]);
	}
	splay(x);
	ans[x]=size[rson(x)];
}
inline void add_edge(int u,int v) {
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
int main() {
//	freopen("4756.in","r",stdin);
	int n=nextInt();
	size[0]=val[0]=0;
	for(int i=1; i<=n; i++) {
		val[i]=nextInt();
		size[i]=1;
	}
	memset(head,-1,sizeof(head));
	for(int i=2; i<=n; i++) {
		add_edge(nextInt(),i);
	}
	memset(fa,0,sizeof(fa));
	memset(side,-1,sizeof(side));
	dfs(1);
	for(int i=1; i<=n; i++) {
		printf("%d\n",ans[i]);
	}
}
