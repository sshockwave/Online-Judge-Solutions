#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<typename T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
const int N=1000010;
bool dead[N];
int pval[N],fa[N],dis[N],lson[N],rson[N];
int root(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=root(fa[x]);
}
inline int merge(int u,int v){
	if(u==0||v==0){
		return u+v;
	}
	if(u==v){
		return u;
	}
	if(pval[u]>pval[v]){
		swap(u,v);
	}
	rson[u]=merge(rson[u],v);
	if(dis[rson[u]]>dis[lson[u]]){
		swap(lson[u],rson[u]);
	}
	dis[u]=dis[rson[u]]+1;
	return u;
}
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
		fa[i]=i;
	}
	memset(dead,0,sizeof(dead));
	for(int tot=ni;tot--;){
		if(nc()=='M'){
			int u=ni,v=ni;
			if(dead[u]||dead[v]){
				continue;
			}
			int nr=merge(u=root(u),v=root(v));
			fa[u]=fa[v]=nr;
		}else{
			int x=ni;
			if(dead[x]){
				puts("0");
				continue;
			}
			x=root(x);
			dead[x]=true;
			printf("%d\n",pval[x]);
			fa[x]=merge(lson[x],rson[x]);
			fa[fa[x]]=fa[x];
		}
	}
}
