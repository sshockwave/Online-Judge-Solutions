#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
const int N=30010,SHIFT=14,E=N*2,D=E;
int pval[N],psum[SHIFT];
struct Tree{
	int to[E],bro[E],val[E],head[N],etop;
	int fa[N],son[N],size[N],tofa[N];
	int c[N][SHIFT];
	Tree(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		etop=fa[1]=size[0]=son[0]=0;
	}
	inline void add_edge(int u,int v,int w){
		to[etop]=v;
		bro[etop]=head[u];
		val[etop]=w;
		head[u]=etop++;
	}
	void dfs1(int x){
		size[x]=1;
		for(int i=0;i<SHIFT;i++){
			c[x][i]=(pval[x]>>i)&1;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=fa[x]){
				fa[v]=x;
				tofa[v]=i^1;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
				for(int i=0;i<SHIFT;i++){
					c[x][i]+=c[v][i];
				}
			}
		}
	}
}tree;
int main(){
	int n=ni();
	for(int i=1;i<=n;i++){
		pval[i]=ni();
		for(int j=0;j<SHIFT;j++){
			psum[j]+=(pval[i]>>j)&1;
		}
	}
	for(int i=1,u,v,w;i<n;i++){
		u=ni(),v=ni(),w=ni();
		tree.add_edge(u,v,w);
		tree.add_edge(v,u,w);
	}
	for(int tot=ni();tot--;){
		int x=ni();
		for(int i=0;i<SHIFT;i++){
			psum[i]-=(pval[x]>>i)&1;
		}
		pval[x]=ni();
		for(int i=0;i<SHIFT;i++){
			psum[i]+=(pval[x]>>i)&1;
		}
		tree.dfs1(1);
		long long ans=0,subans;
		for(int i=0;i<SHIFT;i++){
			subans=0;
			for(int x=2;x<=n;x++){
				subans+=tree.val[tree.tofa[x]]*(tree.c[x][i]*(n-tree.size[x]-psum[i]+tree.c[x][i])+(tree.size[x]-tree.c[x][i])*(psum[i]-tree.c[x][i]));
			}
			ans+=subans<<i;
		}
		printf("%lld\n",ans);
	}
}
