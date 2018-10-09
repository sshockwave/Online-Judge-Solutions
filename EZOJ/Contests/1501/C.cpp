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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=10,M=10010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G{
	const int N=::N*::M,E=(N*3)<<1;
	int to[E],bro[E],cap[E],head[N],e,n=0,s,t;
	inline int nn(){
		return ++n;
	}
	inline void pre_init(){
		s=nn(),t=nn();
	}
	inline void init(){
		mset(head+1,-1,n);
		e=0;
	}
	inline void ae(const int u,const int v,const int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(const int u,const int v,const int c){
		ae(u,v,c),ae(v,u,0);
	}
	inline void add2(const int u,const int v,const int c){
		ae(u,v,c),ae(v,u,c);
	}
	inline void add_noregret(const int u,const int v,const int c){
		ae(u,v,c);
		to[e]=u,cap[e]=0,e++;
		//add(u,v,c);//cout
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		mset(dis+1,127,n);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		for(;qh<qt;){
			const int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	inline lint aug(const int x,const lint a){
		if(x==t||a==0)return a;
		lint r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min<lint>(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		if(r){
			dis[x]=INF;
		}
		return a-r;
	}
	inline lint dinic(){
		lint flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,LINF));
		return flow;
	}
}
int a[N][M],b[N][M],c1[N][M],c2[N][M];
int nd[N][M];
inline lint solve(const int n,const int m,const int sh){
	G::init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((a[i][j]>>sh)&1){
				G::add_noregret(G::s,nd[i][j],b[i][j]);
			}else{
				G::add_noregret(nd[i][j],G::t,b[i][j]);
			}
			if(j<m){
				G::add2(nd[i][j],nd[i][j+1],c1[i][j]);
			}
			G::add2(nd[i][j],nd[i+1][j],c2[i][j]);
		}
	}
	return G::dinic();
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chessboard.in","r",stdin);
	freopen("chessboard.out","w",stdout);
#endif
	const int n=ni,m=ni;
	G::pre_init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			nd[i][j]=G::nn();
		}
	}
	for(int j=1;j<=m;j++){
		nd[n+1][j]=nd[1][j];
	}
	G::init();
	int mx_a=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=ni;
			apmax(mx_a,a[i][j]);
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=ni;
	for(int i=1;i<=n;i++)for(int j=1;j<m;j++)c1[i][j]=ni;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c2[i][j]=ni;
	lint ans=0;
	for(int i=0;(1<<i)<=mx_a;i++){
		ans+=solve(n,m,i)<<i;
	}
	printf("%lld\n",ans);
	return 0;
}
