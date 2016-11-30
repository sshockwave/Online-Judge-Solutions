#include <iostream>
#include <cstdio>
#include <cstring>
#define N 30010
using namespace std;
int fa[N],size[N],ord[N];
inline int abs(int a){
	return a>0?a:-a;
}
int root(int x){
	if(fa[x]==0){
		return x;
	}
	int tfa=fa[x];
	fa[x]=root(fa[x]);
	ord[x]+=ord[tfa];
	return fa[x];
}
int main(){
	memset(ord,0,sizeof(ord));
	memset(fa,0,sizeof(fa));
	for(int i=0;i<N;i++){
		size[i]=1;
	}
	int tot,i,j;
	char op;
	scanf("%d",&tot);
	while(tot--){
		while(op=getchar(),op!='M'&&op!='C');
		scanf("%d%d",&i,&j);
		if(op=='M'){
			i=root(i),j=root(j);
			ord[i]=size[j];
			size[j]+=size[i];
			fa[i]=j;
		}else{
			if(root(i)==root(j)){
				printf("%d\n",abs(ord[i]-ord[j])-1);
			}else{
				printf("-1\n");
			}
		}
	}
}
