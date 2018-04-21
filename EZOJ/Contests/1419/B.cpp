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
namespace G{
	const int N=::N*::N*2;
	int edg[N][2],n=1;
	inline int nn(){
		return ++n;
	}
	int ans[N];
	int que[N],qh,qt,vis[N],vtim=0;
	bool okay[N];
	inline void reset(){
		qh=qt=0,++vtim;
	}
	inline bool pshque(int x){
		if(!okay[x])return false;
		que[qt++]=x,vis[x]=vtim;
		return true;
	}
	inline bool bfs(){
		while(qh<qt){
			int x=que[qh++];
			for(int i=0;i<2&&edg[x][i];i++){
				int v=edg[x][i];
				if(vis[v]<vtim){
					if(!pshque(v))return false;
				}
			}
		}
		return true;
	}
	int deg[N];
	int revedg[N][2];
	inline void add_rev(int u,int v){
		if(u){
			revedg[u][1]=revedg[u][0],revedg[u][0]=v;
			++deg[v];
		}
	}
	inline void main(){
		reset();
		mset(deg+1,0,n);
		for(int i=1;i<=n;i++){
			add_rev(edg[i][0],i);
			add_rev(edg[i][1],i);
			if(deg[i]==0){
				que[qt++]=i;
			}
		}
		mset(okay+1,0,n);
		while(qh<qt){
			int x=que[qh++];
			okay[x]=true;
			for(int i=0;i<2&&revedg[x][i];i++){
				int v=revedg[x][i];
				if(--deg[v]==0){
					que[qt++]=v;
				}
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
	mset(G::ans+1,127,G::n);
	for(int i=1;i<=n;i++){
		G::reset();
		for(int j=1;j<=m;j++){
			if(G::pshque(nd[i][j][1])&&G::bfs()){
				G::ans[nd[i][j][1]]=G::qt;
			}else break;
		}
		G::reset();
		for(int j=m;j>=1;j--){
			if(G::pshque(nd[i][j][3])&&G::bfs()){
				G::ans[nd[i][j][3]]=G::qt;
			}else break;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int a=min(G::ans[nd[i][j][0]],G::ans[nd[i][j][2]]);
			printf("%d ",a<INF?a<<1:-1);
		}
		putchar('\n');
	}
	return 0;
}
