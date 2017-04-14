#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=100010,M=100010,E=N*2,logN=20;
int to[E],bro[E],head[N];
inline void add_edge(int u,int v){
	static int etop=0;
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
int fa[N][logN],dep[N],ldep[N];
void dfs(int x,int f){
	fa[x][0]=f;
	for(int &j=ldep[x];fa[x][j+1]=fa[fa[x][j]][j];j++);
	for(int i=head[x],v;~i;i=bro[i]){
		v=to[i];
		if(v!=f){
			dep[v]=dep[x]+1;
			dfs(v,x);
		}
	}
}
inline int lca(int u,int v){
	if(dep[u]<dep[v]){
		swap(u,v);
	}
	for(int j=ldep[u];j>=0;j--){
		if(dep[fa[u][j]]>=dep[v]){
			u=fa[u][j];
		}
	}
	if(u==v){
		return u;
	}
	for(int j=min(ldep[u],ldep[v]);j>=0;j--){
		if(fa[u][j]!=fa[v][j]){
			u=fa[u][j],v=fa[v][j];
		}
	}
	assert(fa[u][0]==fa[v][0]);
	return fa[u][0];
}
inline int dist(int u,int v){
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}
int color[N],cdis[M];
int lmost[M],rmost[M],diff[N];
inline void solvechain(int n,int m){
	memset(lmost+1,127,m<<2);
	memset(rmost+1,0,m<<2);
	for(int i=1;i<=n;i++){
		apmin(lmost[color[i]],i);
		apmax(rmost[color[i]],i);
	}
	memset(diff,0,sizeof(diff));
	for(int i=1;i<=m;i++){
		int l=lmost[i],r=rmost[i],mid=(l+r)>>1;
		if(r){
			diff[0]--;
			diff[mid+1]++;
			if((l+r)&1){
				diff[mid+2]++;
			}else{
				diff[mid+1]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		diff[i]+=diff[i-1];
	}
	diff[0]=0;
	for(int i=1;i<=m;i++){
		if(rmost[i]){
			diff[0]+=rmost[i];
		}
	}
	for(int i=1;i<=n;i++){
		diff[i]+=diff[i-1];
	}
	for(int i=1;i<=n;i++){
		diff[i]-=max(i-lmost[color[i]],rmost[color[i]]-i);
		printf("%d\n",diff[i]);
	}
}
int main(){
	int n=ni(),m=ni();
	for(int i=1;i<=n;i++){
		color[i]=ni();
	}
	memset(head,-1,sizeof(head));
	bool flag=true;
	for(int i=1,u,v,w;i<n;i++){
		u=ni(),v=ni();
		add_edge(u,v);
		add_edge(v,u);
		if(u!=i||v!=i+1){
			flag=false;
		}
	}
	if(flag){
		solvechain(n,m);
		return 0;
	}
	memset(fa,0,sizeof(fa));
	memset(ldep,0,sizeof(ldep));
	dep[1]=1;
	dfs(1,0);
	for(int i=1;i<=n;i++){
		memset(cdis+1,0,m<<2);
		for(int j=1;j<=n;j++){
			if(color[j]!=color[i]){
				apmax(cdis[color[j]],dist(i,j));
			}
		}
		int ans=0;
		for(int j=1;j<=m;j++){
			ans+=cdis[j];
		}
		printf("%d\n",ans);
	}
}
