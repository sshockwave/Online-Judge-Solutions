#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 200010
#define lson(x) son[x][0]
#define rson(x) son[x][1]
#define LEFT 0
#define RIGHT 1
#define ROOT -1
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
int fa[N],son[N][2],size[N],side[N];
inline void push_up(int x){
	size[x]=1;
	if(lson(x)){
		size[x]+=size[lson(x)];
	}
	if(rson(x)){
		size[x]+=size[rson(x)];
	}
}
inline void rotate(int x){
	assert(side[x]!=ROOT);
	bool r=!side[x];
	son[fa[x]][!r]=son[x][r];
	if(~son[x][r]){
		fa[son[x][r]]=fa[x];
		side[son[x][r]]=!r;
	}
	son[x][r]=fa[x];
	side[x]=side[fa[x]];
	side[fa[x]]=r;
	fa[x]=fa[fa[x]];
	fa[son[x][r]]=x;
	if(~side[x]){
		son[fa[x]][side[x]]=x;
	}
	push_up(son[x][r]),push_up(x);
}
inline void splay(int x){
	while(side[x]!=ROOT){
		if(side[fa[x]]==ROOT){
			rotate(x);
		}else if(side[fa[x]]==side[x]){
			rotate(fa[x]),rotate(x);
		}else{
			rotate(x),rotate(x);
		}
	}
}
inline void access(int x){
	splay(x);
	if(~rson(x)){
		side[rson(x)]=ROOT;
		rson(x)=-1;
		push_up(x);
	}
	while(~fa[x]){
		splay(fa[x]);
		if(~rson(fa[x])){
			side[rson(fa[x])]=ROOT;
		}
		side[x]=RIGHT;
		rson(fa[x])=x;
		push_up(fa[x]);
		rotate(x);
	}
}
int main(){
	memset(side,ROOT,sizeof(side));
	memset(son,-1,sizeof(son));
	int n=next_int();
	for(int i=0;i<n;i++){
		size[i]=1;
		fa[i]=i+next_int();
		if(fa[i]>=n){
			fa[i]=-1;
		}
	}
	for(int tot=next_int();tot--;){
		if(next_int()==1){
			int x=next_int();
			access(x);
			printf("%d\n",size[x]);
		}else{
			int x=next_int();
			access(x);
			if(~lson(x)){
				side[lson(x)]=-1;
				fa[lson(x)]=-1;
				lson(x)=-1;
				push_up(x);
			}
			fa[x]=x+next_int();
			if(fa[x]>=n){
				fa[x]=-1;
			}
		}
	}
}
