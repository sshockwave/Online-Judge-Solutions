#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
#define lson(x) son[x][0]
#define rson(x) son[x][1]
#define LEFT 0
#define RIGHT 1
#define ROOT -1
using namespace std;
int n,fa[N],son[N][2],size[N],side[N];
inline int nextInt(){
	char in;
	while(in=getchar(),in<'0'||in>'9');
	int num=0;
	while(in=getchar(),in>='0'&&in<='9'){
		num=num*10+in-'0';
	}
	return num;
}
inline void push_down(int x){
	//none
}
inline void push_up(int x){
	size[x]=size[lson(x)]+size[rson(x)]+1;
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
	side[son[x][!d]]=!d;
	if(~side[y]){
		son[fa[y]][side[y]]=y;
	}
	push_up(x),push_up(y);
}
inline void splay(int x){
	while(~side[x]){
		rotate(fa[x],!side[x]);
	}
}
inline void access(int x){
	int y=0;
	do{
		splay(x);
		side[rson(x)]=ROOT;
		rson(x)=y;
		side[y]=RIGHT;
		push_up(x);
		y=x;
	}while(x=fa[x]);
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
	fa[lson(x)]=fa[x];
	fa[x]=0;
	side[lson(x)]=ROOT;
	lson(x)=0;
	push_up(x);
}
int main(){
	memset(fa,0,sizeof(fa));
	memset(son,0,sizeof(son));
	int val;
	n=nextInt();
	size[0]=0;
	for(int i=1;i<=n;i++){
		size[i]=1;
		side[i]=-1;
	}
	for(int i=1;i<=n;i++){
		val=nextInt();
		if(val+i<=n){
			link(val+i,i);
		}
	}
	for(int tot=nextInt(),p;tot--;){
		if(nextInt()==1){
			p=nextInt()+1;
			access(p);
			splay(p);
			printf("%d\n",size[lson(p)]);
		}else{
			p=nextInt()+1;
			val=nextInt();
			cut(p);
			if(val+p<=n){
				link(val+p,p);
			}
		}
	}
}
