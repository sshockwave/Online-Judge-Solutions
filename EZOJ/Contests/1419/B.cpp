#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=410,INF=0x7f7f7f7f;
namespace G2{
	const int N=::N*::N*2,E=N*2;
	int to[E],bro[E],head[N],n,e=0;
	inline void init(int _n){
		mset(head+1,-1,n=_n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int deg[N];
	int que[N],qh=0,qt=0;
	inline void topsort();
}
namespace G{
	const int N=::N*::N*2;
	int edg[N][2],n=1;
	inline int nn(){
		return ++n;
	}
	int dfn[N],low[N],bln[N],sz[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		assert(!instk[x]);
		stk[ss++]=x,instk[x]=true;
		for(int i=0;i<2&&edg[x][i];i++){
			int v=edg[x][i];
			if(dfn[v]==0){
				tarjan(v);
				apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],dfn[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			sz[x]=0;
			do{
				v=stk[--ss];
				bln[v]=x;
				++sz[x];
				instk[v]=false;
			}while(x!=v);
		}
	}
	int ans[N];
	int que[N],vis[N],vtim=0;
	inline void bfs(int s){
		if(sz[s]>1)return;
		assert(sz[bln[s]]==1);
		int qh=0,qt=0;
		que[qt++]=s,vis[s]=++vtim;
		while(qh<qt){
			int x=que[qh++];
			for(int i=0;i<2&&edg[x][i];i++){
				int v=edg[x][i];
				if(vis[v]<vtim){
					if(ans[v]==INF)return;
					if((v^s)==1)return;
					assert(sz[bln[v]]<INF);
					que[qt++]=v,vis[v]=vtim;
				}
			}
		}
		ans[s]=qt;
	}
	inline void main(){
		mset(dfn+1,0,n);
		for(int i=2;i<=n;i++){
			if(dfn[i]==0){
				tarjan(i);
			}
		}
		G2::init(n);
		for(int i=2;i<=n;i++){
			if(edg[i][0]){
				if(bln[edg[i][0]]!=bln[i]){
					G2::ae(bln[i],bln[edg[i][0]]);
				}
				if(edg[i][1]&&bln[edg[i][1]]!=bln[i]){
					G2::ae(bln[i],bln[edg[i][1]]);
				}
			}
		}
		G2::topsort();
		mset(ans+1,127,n);
		for(int i=G2::qt-1;i>=0;i--){
			bfs(G2::que[i]);
		}
	}
}
inline void G2::topsort(){
	mset(deg+1,0,n);
	for(int i=0;i<e;i++){
		++deg[to[i]];
	}
	for(int x=1;x<=n;x++){
		if(G::bln[x]==x&&deg[x]==0){
			que[qt++]=x;
		}
	}
	while(qh<qt){
		int x=que[qh++];
		for(int i=head[x],v;~i;i=bro[i]){
			if(--deg[v=to[i]]==0){
				que[qt++]=v;
			}
		}
	}
}
int nd[N][N][4];
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sandwich.in","r",stdin);
	freopen("sandwich.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='N'){
				nd[i][j][0]=nd[i][j][1]=G::nn();
				nd[i][j][2]=nd[i][j][3]=G::nn();
			}else{
				nd[i][j][0]=nd[i][j][3]=G::nn();
				nd[i][j][1]=nd[i][j][2]=G::nn();
			}
		}
	}
	using G::edg;
	memset(edg,0,sizeof(edg));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int *p=nd[i][j];
			if(i<n){
				edg[p[0]][0]=nd[i+1][j][0];
			}
			if(i>1){
				edg[p[2]][0]=nd[i-1][j][2];
			}
			if(j>1){
				edg[p[1]][1]=nd[i][j-1][1];
			}
			if(j<m){
				edg[p[3]][1]=nd[i][j+1][3];
			}
			if(edg[p[0]][0]==0){
				swap(edg[p[0]][0],edg[p[0]][1]);
			}
			if(edg[p[2]][0]==0){
				swap(edg[p[2]][0],edg[p[2]][1]);
			}
		}
	}
	G::main();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int a=min(G::ans[nd[i][j][0]],G::ans[nd[i][j][2]]);
			printf("%d ",a<INF?a<<1:-1);
		}
		putchar('\n');
	}
	return 0;
}
