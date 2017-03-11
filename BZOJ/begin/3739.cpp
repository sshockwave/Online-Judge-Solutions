#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#define M 100010
#define N 110
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
struct edge{
	int u,v,c;
}e[M],cpy[M];
bool operator < (edge a,edge b){
	return a.c<b.c;
}
int fa[N],rank[N];
int root(int x){
	if(fa[x]){
		return fa[x]=root(fa[x]);
	}
	return x;
}
inline void uni(int u,int v){
	u=root(u),v=root(v);
	if(rank[u]<rank[v]){
		swap(u,v);
	}
	fa[v]=u;
	if(rank[u]==rank[v]){
		rank[u]++;
	}
}
int main(){
	freopen("highway.in","r",stdin);
	freopen("highway.out","w",stdout);
	int n=ni(),m=ni(),tot=ni();
	for(int i=1;i<=m;i++){
		e[i].u=ni(),e[i].v=ni(),e[i].c=ni();
	}
	while(tot--){
		int l=ni(),r=ni();
		for(int i=l;i<=r;i++){
			cpy[i]=e[i];
		}
		sort(cpy+l,cpy+r+1);
		memset(fa,0,sizeof(fa));
		memset(rank,0,sizeof(rank));
		int cost=0;
		for(int i=l;i<=r;i++){
			if(root(cpy[i].u)!=root(cpy[i].v)){
				uni(cpy[i].u,cpy[i].v);
				cost+=cpy[i].c;
			}
		}
		printf("%d\n",cost);
	}
}
