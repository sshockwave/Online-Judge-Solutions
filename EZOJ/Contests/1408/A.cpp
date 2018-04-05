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
const int N=310,INF=0x7f7f7f7f;
namespace G{
	const int N=::N*2,E=(N+::N+N+::N)*2;//cout
	int to[E],bro[E],cap[E],val[E],head[N],e=0,n=0,s,t;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		s=nn(),t=nn();
	}
	inline void reset(){
		for(int i=0;i<e;i+=2){
			cap[i]+=cap[i^1],cap[i^1]=0;
		}
	}
	inline void ae(int u,int v,int c,int w){
		to[e]=v,bro[e]=head[u],cap[e]=c,val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int c,int w){
		ae(u,v,c,w),ae(v,u,0,-w);
	}
	int dis[N],que[N*2];
	int vis[N],tim=0;
	inline void dij(){
		memset(dis+1,127,n*sizeof(dis[0]));
		memset(vis+1,0,n*sizeof(vis[0]));
		int qh=N,qt=N;
		dis[s]=0,que[qt++]=s;
		tim++;
		while(qh<qt){
			int x=que[qh++];
			if(vis[x]==tim)continue;
			vis[x]=tim;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i];
					assert(vis[v]<tim);
					if(val[i]==0){
						que[--qh]=v;
					}else if(val[i]==1){
						que[qt++]=v;
					}else assert(false);
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t||a==0)return a;
		assert(vis[x]<tim);
		vis[x]=tim;
		int r=a,d;
		for(int i=head[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+val[i]&&vis[v]<tim){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		if(r==0){//cout
			vis[x]=tim-1;
		}
		return a-r;
	}
	inline int mcmf(){
		int cost=0;
		for(;dij(),dis[t]<INF;tim++,cost+=dis[t]*aug(s,INF));
		return cost;
	}
}
int innd[N],ound[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("pheno.in","r",stdin);
	freopen("pheno.out","w",stdout);
#endif
	int n=ni,tot=ni;
	G::init();
	int midpt=G::nn();
	for(int i=1;i<=n;i++){
		G::add(midpt,innd[i]=G::nn(),INF,1);
		G::add(ound[i]=G::nn(),midpt,INF,0);
		G::add(G::s,ound[i],1,0);
		G::add(innd[i],G::t,1,0);
		G::add(innd[i],ound[i],INF,0);
	}
	while(tot--){
		int u=ni,v=ni;
		G::reset();
		G::add(ound[u],innd[v],INF,0);
		printf("%d\n",G::mcmf());
	}
	return 0;
}
