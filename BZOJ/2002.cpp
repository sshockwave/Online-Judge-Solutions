#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
#define lson(x) son[x][0]
#define rson(x) son[x][1]
#define LEFT 0
#define RIGHT 1
using namespace std;
int n,root[N],fa[N],son[N][2],size[N];
bool side[N];
inline void push_down(int x){
	//none
}
inline void push_up(int x){
	size[x]=1;
	if(~lson(x)){
		size[x]+=size[lson(x)];
	}
	if(~rson(x)){
		size[x]+=size[rson(x)];
	}
}
inline void rotate(int x,bool d){
	push_down(x),push_down(son[x][!d]);
	int y=son[x][!d];
	son[x][!d]=son[y][d];
	son[y][d]=x;
	fa[y]=fa[x];
	fa[x]=y;
	side[y]=side[x];
	side[x]=d;
	if(~son[x][!d]){
		side[son[x][!d]]=!d;
	}
	if(~fa[y]){
		son[fa[y]][side[d]]=y;
	}
	push_up(x),push_up(y);
}
inline void splay(int x){
	while(~fa[x]){
		rotate(fa[x],!side[x]);
	}
}
inline int first(int x){
	for(;~lson(x);x=lson(x));
	return x;
}
inline void access(int x){
	splay(x);
	root[rson(x)]=x;
	fa[rson(x)]=-1;
	while(~root[x=first(root[x])]){
		splay(root[x]);
		splay(x);
		fa[rson(root[x])]=-1;
		root[rson(root[x])]=root[x];
		rson(root[x])=x;
		fa[x]=root[x];
		side[x]=RIGHT;
		push_up(root[x]);
	}
}
inline void link(int u,int v){
	access(u);
	splay(u);
	splay(v);
	rson(u)=v;
	side[v]=RIGHT;
	fa[v]=u;
	push_up(u);
}
inline void cut(int x){
	access(x);
	splay(x);
	fa[lson(x)]=-1;
	root[x]=-1;
	push_up(x);
}
int main(){
	memset(root,-1,sizeof(root));
	memset(fa,-1,sizeof(fa));
	memset(son,-1,sizeof(son));
	int tot,op,p,val;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		size[i]=1;
	}
	for(int i=0;i<n;i++){
		scanf("%d",val);
		if(val+i<n){
			link(val+i,i);
		}
	}
	for(scanf("%d",&tot);tot--;){
		scanf("%d%d",&op,&p);
		if(op==1){
			access(p);
			splay(p);
			if(lson(p)==-1){
				printf("1\n");
			}else{
				printf("%d\n",size[lson(p)]+1);
			}
		}else{
			scanf("%d",&val);
			cut(p);
			if(val+p<n){
				link(val+p,p);
			}
		}
	}
}
