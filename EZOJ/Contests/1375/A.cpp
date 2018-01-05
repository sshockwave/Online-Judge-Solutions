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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=210,K=16,INF=0x7f7f7f7f;
namespace G{
	const int N=::N,E=N*2*2;
	int to[E],bro[E],cap[E],val[E],head[N],e=0,n=0,s,t;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		s=nn(),t=nn();
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int c,int w){
		to[e]=v,bro[e]=head[u],cap[e]=c,val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int c,int w){
		ae(u,v,c,w),ae(v,u,0,-w);
	}
	int dis[N],pre[N],que[N];
	bool inque[N];
	inline void spfa(){
		memset(dis+1,127,n<<2);
		memset(inque+1,0,n);
		int qh=0,qt=0;
		dis[s]=0,pre[s]=-1;
		inque[s]=true,que[qt++]=s;
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			inque[x]=false;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i],pre[v]=i;
					if(!inque[v]){
						inque[v]=true;
						que[qt++]=v;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
		}
	}
	inline int aug(){
		int dt=INF;
		for(int p=t;p!=s;p=to[pre[p]^1]){
			apmin(dt,cap[pre[p]]);
		}
		for(int p=t;p!=s;p=to[pre[p]^1]){
			cap[pre[p]]-=dt;
			cap[pre[p]^1]+=dt;
		}
		return dt;
	}
	inline int mcmf(){
		int cost=0;
		for(;spfa(),dis[t]<INF;cost+=dis[t]*aug());
		return cost;
	}
}
int node[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("prince.in","r",stdin);
	freopen("prince.out","w",stdout);
#endif
	int n=ni,k=ni,p=ni,q=ni;
	G::init();
	node[0]=G::s,node[n-k+2]=G::t;
	for(int i=n-k+1;i>=1;i--){
		G::add(node[i]=G::nn(),node[i+1],k-p-q,0);
	}
	G::add(G::s,node[1],k-p,0);
	int ans=0;
	for(int i=1;i<=n;i++){
		int x=ni,y=ni;
		ans+=x;
		G::add(node[max(1,i-k+1)],node[min(n-k+1,i)+1],1,x-y);
	}
	printf("%d\n",ans-G::mcmf());
	return 0;
}
