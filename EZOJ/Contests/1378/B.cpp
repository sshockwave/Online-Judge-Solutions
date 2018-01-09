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
const int N=110,E=2510,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G2{
	const int E=::E*4;
	int to[E],bro[E],head[N],e=0,s,t;
	lint cap[E];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,lint c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,lint c){
		ae(u,v,c),ae(v,u,0);
	}
	inline void add_dir(int u,int v,lint c){
		add(u,v,c),add(v,u,LINF);
	}
	int dis[N],que[N];
	inline void bfs(){
		memset(dis,127,(t+1)<<2);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	lint aug(int x,lint a){
		if(x==t)return a;
		lint r=a,d;
		for(int i=head[x],v;r&&~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(cap[i],r));
				cap[i]-=d,cap[i^1]+=d,r-=d;
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
namespace G1{
	int fr[E],to[E],bro[E],val[E],head[N],e=0;
	int dfn[N],low[N],tim=0;
	int bln[N];
	int stk[N],ss=0;
	bool instk[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(bln,-1,sizeof(bln));
		memset(instk,0,sizeof(instk));
	}
	inline void ae(int u,int v,int w){
		fr[e]=u,to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				tarjan(v);
				apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],dfn[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do v=stk[--ss],instk[v]=false,bln[v]=x;
			while(v!=x);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("hack.in","r",stdin);
	freopen("hack.out","w",stdout);
#endif
	int n=ni;
	G1::init();
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G1::ae(u,v,ni);
	}
	G1::tarjan(0);
	assert(G1::dfn[n-1]);
	if(G1::bln[0]==G1::bln[n-1]){
		puts("-1");
		return 0;
	}
	G2::init(),G2::s=G1::bln[0],G2::t=G1::bln[n-1];
	for(int i=0;i<G1::e;i++){
		using namespace G1;
		if(dfn[fr[i]]&&bln[fr[i]]!=bln[to[i]]){
			G2::add_dir(bln[fr[i]],bln[to[i]],val[i]);
		}
	}
	printf("%lld\n",G2::dinic());
	return 0;
}
