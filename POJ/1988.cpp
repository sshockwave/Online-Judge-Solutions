#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 30010
using namespace std;
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int fa[N],down[N],top[N];
int root(int x){
	if(fa[x]==0){
		return x;
	}
	root(fa[x]);
	down[x]+=down[fa[x]];
	if(fa[fa[x]]){
		fa[x]=fa[fa[x]];
	}
	return fa[x];
}
int main(){
	memset(fa,0,sizeof(fa));
	memset(down,0,sizeof(down));
	for(int i=1;i<N;i++){
		top[i]=i;
	}
	int x,y;
	char op;
	for(int tot=nextInt();tot--;){
		while(op=getchar(),op!='M'&&op!='C');
		if(op=='M'){
			x=root(nextInt()),y=root(nextInt());
			fa[x]=top[y];
			down[x]=1;
			top[y]=top[x];
		}else if(op=='C'){
			x=nextInt();
			root(x);
			printf("%d\n",down[x]);
		}
	}
}
