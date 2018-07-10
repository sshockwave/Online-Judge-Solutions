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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
const int N=510,E=1010,INF=0x7f7f7f7f;
namespace G{
	const int N=::N<<1,E=(::N*3+::E*2)<<1;
	int to[E],bro[E],head[N],e=0,n=0,s,t;
	lint cap[E];
	inline int nn(){
		assert(n+1<N);
		return ++n,head[n]=-1,n;
	}
	inline void init(){
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c){
		assert(e<E);
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		if(c){
			ae(u,v,c),ae(v,u,0);
		}
	}
	inline void add_1w(int u,int v,int c){
		ae(u,v,c),ae(v,u,INF);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		int qh=0,qt=0;
		mset(dis+1,127,n);
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
	int aug(const int x,const int a){
		if(x==t||a==0)return a;
		int r=a,d;
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
		for(;bfs(),dis[t]<INF;flow+=aug(s,INF));
		return flow;
	}
}
int nd[N][2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("permutation.in","r",stdin);
	freopen("permutation.out","w",stdout);
#endif
	G::init();
	const int n=ni;
	int tot=ni;
	int sum=0;
	for(int i=1;i<=n;i++){
		nd[i][0]=G::nn();
		nd[i][1]=G::nn();
		const int v=ni;
		if(v>0){
			sum+=v;
			G::add_1w(G::s,nd[i][0],v);
			G::add_1w(nd[i][0],nd[i][1],0);
			G::add_1w(nd[i][1],G::t,v);
		}else{
			G::add_1w(nd[i][0],nd[i][1],-v);
		}
	}
	for(;tot--;){
		const int u=ni,v=ni;
		G::add(nd[v][0],nd[u][0],INF);
		G::add(nd[v][1],nd[u][1],INF);
	}
	printf("%lld\n",sum-G::dinic());
	return 0;
}
