#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=1010,N2=N*N;
namespace G{
	const int N=N2,E=N<<2;
	int to[E],bro[E],head[N],n=0,e=0;
	inline int nn(){
		return ++n;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfn[N],idx[N],tim=0;
	void dfs(int x){
		idx[dfn[x]=++tim]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				dfs(v);
			}
		}
	}
	int idom[N],sdom[N],fa[N],val[N];
	int root(int x){
		if(fa[x]==x){
			return x;
		}
		int rt=root(fa[x]);
		if(dfn[sdom[val[fa[x]]]]<dfn[sdom[val[x]]]){
			val[x]=val[fa[x]];
		}
		return fa[x]=rt;
	}
	namespace bucket{
		int bro[N],head[N];
		inline void init(){
			memset(head,-1,sizeof(head));
		}
		inline void ae(int u,int v){
			bro[v]=head[u],head[u]=v;
		}
		inline void clr(int x){
			for(int i=head[x];~i;i=bro[i]){
				root(i);
				idom[i]=val[i];
			}
		}
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		bucket::init();
	}
	inline void LT(){
		memset(dfn+1,0,n<<2);
		G::dfs(1);
		for(int i=1;i<=n;i++){
			idom[i]=sdom[i]=fa[i]=val[i]=i;
		}
		for(int s=tim;s>=1;s--){
			int x=idx[s];
			bucket::clr(x);
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(dfn[sdom[v]]<dfn[sdom[x]]){
					sdom[x]=sdom[v];
				}
				if(dfn[v]>dfn[x]&&fa[v]==v){
					fa[v]=x;
				}
			}
			bucket::ae(sdom[x],x);
		}
		for(int s=1;s<=tim;s++){
			int x=idx[s];
			idom[x]=sdom[idom[x]]==sdom[x]?sdom[x]:idom[idom[x]];
		}
	}
}
int node[N][N];
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
#endif
	int n=ni,m=ni;
	memset(node,0,sizeof(node));
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			node[i][j]=s[j]=='.';
		}
	}
	G::init();
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(node[i][j]){
				node[i][j]=G::nn();
			}
		}
	}/*
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<node[i][j]<<" ";
		}
		cout<<endl;
	}*/
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(node[i][j]){
				static int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
				for(int d=0;d<4;d++){
					int tx=i+dx[d],ty=j+dy[d];
					if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&node[tx][ty]){
						G::ae(node[i][j],node[tx][ty]);
					}
				}
			}
		}
	}
	G::LT();
	int cnt=1;
	for(int i=G::n;G::idom[i]!=i;i=G::idom[i],cnt++);
	printf("%d\n",cnt);
	return 0;
}
