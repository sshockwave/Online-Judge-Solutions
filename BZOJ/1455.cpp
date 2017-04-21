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
int pval[N];
struct unifind{
	int fa[N],rank[N];
	unifind(){
		memset(fa,0,sizeof(fa));
		memset(rank,0,sizeof(rank));
	}
	int root(int x){
		if(fa[x]==0){
			return x;
		}
		return fa[x]=root(fa[x]);
	}
	inline int uni(int u,int v){
		u=root(u),v=root(v);
		if(u==v){
			return u;
		}
		if(rank[u]<rank[v]){
			swap(u,v);
		}
		fa[v]=u;
		if(rank[u]==rank[v]){
			rank[u]++;
		}
		return u;
	}
}uf;
struct LHeap{
	int dis[N],lson[N],rson[N],root[N];
	LHeap(){
		memset(dis,0,sizeof(dis));
		memset(lson,0,sizeof(lson));
		memset(rson,0,sizeof(rson));
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
	inline int del(int u){
		return merge(lson[u],rson[u]);
	}
}H;
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
		H.root[i]=i;
	}
	memset(dead,0,sizeof(dead));
	for(int tot=ni;tot--;){
		if(nc()=='M'){
			int u=ni,v=ni;
			if(dead[u]||dead[v]){
				continue;
			}
			int nr=H.merge(H.root[uf.root(u)],H.root[uf.root(v)]);
			H.root[uf.uni(u,v)]=nr;
		}else{
			int x=ni;
			if(dead[x]){
				puts("0");
				continue;
			}
			x=H.root[uf.root(x)];
			printf("%d\n",pval[x]);
			H.root[uf.root(x)]=H.del(x);
		}
	}
}
