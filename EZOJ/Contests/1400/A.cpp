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
const int N=110,INF=0x7f7f7f7f;
namespace G{
	const int E=(510*2+N*2)<<1;
	int to[E],bro[E],val[E],cap[E],head[N],e=0,n,s,t;
	int deg[N];//out
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(deg,0,sizeof(deg));
	}
	inline void reset(){
		for(int i=0;i<e;i+=2){
			cap[i]+=cap[i^1],cap[i^1]=0;
		}
	}
	inline void ae(int u,int v,int w,int c){
		to[e]=v,bro[e]=head[u],val[e]=w,cap[e]=c,head[u]=e++;
	}
	int sum=0;
	inline void add(int u,int v,int w,int c){
		if(w<0){
			deg[u]+=c,deg[v]-=c;
			swap(u,v),sum+=w,w=-w;
		}
		ae(u,v,w,c),ae(v,u,-w,0);
	}
	inline void build(int n){
		for(int i=1;i<=n;i++){
			if(deg[i]>0){
				add(i,t,0,deg[i]);
			}else if(deg[i]<0){
				add(s,i,0,-deg[i]);
			}
		}
	}
	int dis[N],que[N];
	bool inque[N];
	inline void spfa(){
		memset(dis+1,127,n*sizeof(dis[0]));
		memset(inque+1,0,n*sizeof(inque[0]));
		int qh=0,qt=0;
		dis[s]=0;
		que[qt++]=s,inque[s]=true;
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i];
					if(!inque[v]){
						que[qt++]=v,inque[v]=true;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
			inque[x]=false;
		}
	}
	int tag[N],tim=0;
	int aug(int x,int a){
		if(x==t||a==0)return a;
		tag[x]=tim;
		int r=a,d;
		for(int i=head[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+val[i]&&tag[v]<tim){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		return a-r;
	}
	inline int mcmf(){
		int cost=0;
		for(;spfa(),dis[t]<INF;tim++,cost+=aug(s,INF)*dis[t]);
		return cost;
	}
}
int eid[N];
inline int calc(int v,int n){
	G::reset();
	for(int i=1;i<=n;i++){
		G::val[eid[i]]=v*(n+1)+1;
		G::val[eid[i]+1]=-G::val[eid[i]];
	}
	return G::mcmf();
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dag.in","r",stdin);
	freopen("dag.out","w",stdout);
#endif
	int n=ni,m=ni,q=ni,k=ni;
	G::init(),G::s=n+1,G::t=n+2,G::n=n+2;
	int sum=0;
	for(int i=1;i<=m;i++){
		int u=ni,v=ni,w=ni;
		G::add(u,v,0,q);
		G::add(u,v,-w*(q+1),1);
		sum+=w;
	}
	for(int i=1;i<=q;i++){
		int u=ni,v=ni;
		eid[i]=G::e;
		G::add(v,u,0,1);
	}
	G::build(n);
	int l=0,r=sum;
	while(l<r){
		int m=(l+r)>>1;
		if(calc(m,q)%(q+1)<=k){
			r=m;
		}else{
			l=m+1;
		}
	}
	printf("%d\n",-(calc(l,q)/(q+1)+G::sum/(q+1))+l*k);
	return 0;
}
