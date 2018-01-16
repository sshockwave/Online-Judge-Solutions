#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=110,M=1010,INF=0x7f7f7f7f;
namespace G{
	const int N=::N+::M*2,E=(::N+::M*10+::M+::M)*2;
	int to[E],bro[E],val[E],cap[E],head[N],e=0;
	int n,s,t;
	inline int nn(){
		assert(n+1<N);
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		n=0,s=nn(),t=nn();
	}
	inline void ae(int u,int v,int w,int c){
		assert(e<E);
		to[e]=v,bro[e]=head[u],val[e]=w,cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int w,int c){
		ae(u,v,w,c),ae(v,u,-w,0);
	}
	int dis[N],que[N];
	bool vis[N];
	inline void spfa(){
		memset(dis+1,127,n<<2);
		memset(vis+1,0,n);
		int qh=0,qt=0;
		dis[s]=0,vis[s]=true,que[qt++]=s;
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			vis[x]=false;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i];
					if(!vis[v]){
						vis[v]=true,que[qt++]=v;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t)return a;
		vis[x]=true;
		int r=a,d;
		for(int i=head[x],v;r&&~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+val[i]&&!vis[v]){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		return a-r;
	}
}
int nodebox[N],nodekey[M],nodeshop[M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("alice.in","r",stdin);
	freopen("alice.out","w",stdout);
#endif
	int n=ni,m=ni,d=ni;
	G::init();
	{//Nodes
		for(int i=1;i<=n;i++){
			nodebox[i]=G::nn();
		}
		for(int i=1;i<=m;i++){
			nodekey[i]=G::nn();
		}
		for(int i=1;i<=d;i++){
			nodeshop[i]=G::nn();
		}
	}
	{//Edges
		for(int i=1;i<=n;i++){
			G::add(G::s,nodebox[i],0,1);
		}
		for(int i=1;i<=m;i++){
			int w=ni;
			G::add(nodekey[i],nodeshop[ni],w,1);
			for(int tot=ni;tot--;){
				G::add(nodebox[ni],nodekey[i],0,1);
			}
		}
		for(int i=1;i<=d;i++){
			G::add(nodeshop[i],G::t,0,ni);
		}
	}
	int flow=0,cost=0;
	for(int dt;G::spfa(),G::dis[G::t]<INF;dt=G::aug(G::s,INF),flow+=dt,cost+=dt*G::dis[G::t]);
	printf("%d\n",flow==n?cost:-1);
	return 0;
}
