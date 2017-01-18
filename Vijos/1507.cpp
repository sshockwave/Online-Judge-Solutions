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
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline bool isW(char c){
	return isNum(c)||(c>='A'&&c<='Z')||(c>='a'&&c<='z');
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline char nextChar(){
	char c;
	while(!isW(c=getchar()));
	return c;
}
int val[N],son[N][2],fa[N],size[N],side[N],ntop=1,root=0;
inline void push_up(int x){
	size[x]=size[lson(x)]+size[rson(x)]+1;
}
inline void rotate(int x){
	bool d=side[x];
	son[fa[x]][d]=son[x][!d];
	side[son[x][!d]]=side[x];
	fa[son[x][!d]]=fa[x];
	son[x][!d]=fa[x];
	push_up(fa[x]);
	side[x]=side[fa[x]];
	side[fa[x]]=!d;
	fa[x]=fa[fa[x]];
	fa[son[x][!d]]=x;
	if(side[x]==ROOT){
		root=x;
	}else{
		son[fa[x]][side[x]]=x;
	}
	push_up(x);
}
inline void splay(int x){
	while(side[x]!=ROOT){
		if(side[fa[x]]==ROOT){
			rotate(x);
		}else if(side[x]==side[fa[x]]){
			rotate(fa[x]),rotate(x);
		}else{
			rotate(x),rotate(fa[x]);
		}
	}
}
bool insert(int &x,int key){
	if(x==0){
		x=ntop++;
		val[x]=key;
		son[x][0]=son[x][1]=0;
		size[x]=1;
		return true;
	}
	size[x]++;
	int &s=son[x][key>val[x]];
	if(insert(s,key)){
		side[s]=key>val[x];
		fa[s]=x;
		splay(s);
	}
	return false;
}
inline void insert(int key){
	if(insert(root,key)){
		side[root]=-1;
	}
}
void drop(int &x,int v){
	if(x==0){
		return;
	}
	int sidex=side[x],fax=fa[x];
	while(x&&val[x]<v){
		x=rson(x);
	}
	if(x==0){
		return;
	}
	side[x]=sidex,fa[x]=fax;
	drop(lson(x),v);
	push_up(x);
}
int rankval(int x,int ord){
	if(ord<=size[rson(x)]){
		return rankval(rson(x),ord);
	}
	if(ord>size[rson(x)]+1){
		return rankval(lson(x),ord-size[rson(x)]-1);
	}
	return val[x];
}
int main(){
	int tot=nextInt(),low=nextInt(),leaves=0,delta=0;
	while(tot--){
		switch(nextChar()){
			case 'I':{
				int k=nextInt();
				if(k<low){
					leaves++;
				}else{
					insert(k-delta);
				}
				break;
			}
			case 'A':{
				delta+=nextInt();
				break;
			}
			case 'S':{
				delta-=nextInt();
				leaves+=size[root];
				drop(root,low-delta);
				leaves-=size[root];
				break;
			}
			case 'F':{
				int k=nextInt();
				if(k>size[root]){
					puts("-1");
				}else{
					printf("%d\n",rankval(root,k)+delta);
				}
				break;
			}
		}
	}
	printf("%d",leaves);
}
