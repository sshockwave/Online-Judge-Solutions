#include <iostream>
#include <cstdio>
#include <cstring>
#define N 500010
using namespace std;
int rest[N*3],lson[N*3],rson[N*3],lend[N*3],rend[N*3],mid[N*3],root,ntop=1;
void build(int &x,int l,int r){
	x=ntop++;
	lend[x]=l,rend[x]=r,mid[x]=l+r>>1;
	rest[x]=r-l+1;
	if(l!=r){
		build(lson[x],l,mid[x]);
		build(rson[x],mid[x]+1,r);
	}
}
void cover(int &x,int l,int r){
	if(lend[x]==l&&rend[x]==r){
		rest[x]=0;
		return;
	}
	if(r<=mid[x]){
		cover(lson[x],l,r);
	}else if(l>mid[x]){
		cover(rson[x],l,r);
	}else{
		cover(lson[x],l,mid[x]);
		cover(rson[x],mid[x]+1,r);
	}
	rest[x]=rest[lson[x]]+rest[rson[x]];
}
int main(){
	int n,m,l,r;
	scanf("%d%d",&n,&m);
	build(root,1,n);
	while(m--){
		scanf("%d%d",&l,&r);
		cover(root,l,r);
		printf("%d\n",rest[root]);
	}
}
