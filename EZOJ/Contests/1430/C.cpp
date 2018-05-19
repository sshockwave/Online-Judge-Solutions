#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1010,INF=0x7f7f7f7f;
namespace G{
	const int N=::N*2,E=1010*3*2;
	int to[E],bro[E],head[N],e=0,n=0,s,t;
	lint cap[E];
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		mset(dis+1,127,n);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	lint aug(int x,lint a){
		if(x==t||a==0)return a;
		lint r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(cap[i],r));
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
		for(;flow<INF&&(bfs(),dis[t]<INF);flow+=aug(s,INF));
		return flow;
	}
}
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.u!=b.u?a.u>b.u:a.v<b.v;
	}
}edg[N];
int nd[N],nd2[N],nd2v[N];
int colnd[N];
int nxt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
#endif
	G::init();
	int n=ni,m=ni;
	nxt[0]=1,nxt[n]=n+1;
	for(int i=1;i<n;i++){
		int &c=colnd[ni];
		if(c==0){
			c=G::nn();
		}
		nd[i]=c;
		nxt[i]=i+1;
	}
	for(int i=1;i<=m;i++){
		edg[i]=(Edge){ni,ni,ni};
	}
	sort(edg+1,edg+m+1);
	mset(nd2+1,0,n);
	for(int i=1;i<=m;i++){
		const int a=edg[i].u,b=edg[i].v,x=G::nn();
		bool hang=false;
		if(nd2[a]){
			G::ae(nd2[a],x,nd2v[a]);
			G::ae(x,nd2[a],INF);
		}else{
			G::add(G::s,x,INF),hang=true;
		}
		nd2[a]=x,nd2v[a]=edg[i].w;
		for(int &j=nxt[a];j!=b;j=nxt[j]){
			if(nd2[j]){
				G::ae(nd2[j],x,nd2v[j]);
				G::ae(x,nd2[j],INF);
			}else if(!hang){
				G::add(G::s,x,INF),hang=true;
			}
			G::ae(x,nd[j],INF);
			G::ae(nd[j],x,INF);
		}
	}
	for(int i=0;i<n;i=nxt[i]){
		if(nd2[i]){
			G::add(nd2[i],G::t,nd2v[i]);
			if(i){
				G::add(nd[i],G::t,INF);
			}
		}else{
			puts("-1");
			return 0;
		}
	}
	lint ans=G::dinic();
	printf("%lld\n",ans<INF?ans:-1);
	return 0;
}
