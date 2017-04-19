#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int D=55,N=350,E=100000,INF=0x7f7f7f7f;
struct Graph{
	int to[E],cap[E],val[E],bro[E],head[N],etop,ntop;
	inline void reset(){
		etop=0,ntop=1;
		memset(head,-1,sizeof(head));
	}
	inline void add_edge(int u,int v,int c,int w){
		to[etop]=v;
		cap[etop]=c;
		val[etop]=w;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	inline void add(int u,int v,int c,int w){
		if(c){
			add_edge(u,v,c,w);
			add_edge(v,u,0,-w);
		}
	}
	inline int nn(){
		return ntop++;
	}
	int dis[N],que[N],pre[N];
	bool inque[N];
	inline void spfa(int s,int t){
		memset(dis,127,ntop<<2);
		memset(pre,-1,ntop<<2);
		memset(inque,0,ntop);
		int qhead=0,qtail=0;
		dis[s]=0;
		que[qtail++]=s;
		inque[s]=true;
		while(qhead!=qtail){
			int x=que[qhead++];
			if(qhead==N){
				qhead=0;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(cap[i]&&dis[v]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i];
					pre[v]=i;
					if(!inque[v]){
						inque[v]=true;
						que[qtail++]=v;
						if(qtail==N){
							qtail=0;
						}
					}
				}
			}
			inque[x]=false;
		}
	}
	int flow,cost;
	inline void mcmf(int s,int t){
		flow=cost=0;
		int delta;
		while(spfa(s,t),dis[t]<INF){
			delta=INF;
			for(int p=pre[t];~p;p=pre[to[p^1]]){
				apmin(delta,cap[p]);
			}
			flow+=delta;
			cost+=delta*dis[t];
			for(int p=pre[t];~p;p=pre[to[p^1]]){
				assert(val[p]==-val[p^1]);
				cap[p]-=delta,cap[p^1]+=delta;
			}
		}
	}
}G;
int day[D],used[D];
int main(){
	for(int toti=1,tot=ni();toti<=tot;toti++){
		G.reset();
		int n=ni(),shop=ni(),maint=ni(),s=G.nn(),t=G.nn(),buyer=G.nn(),rsum=0;
		day[0]=G.nn();
		for(int i=1;i<=n;i++){
			G.add(day[i-1],day[i]=G.nn(),INF,0);
			G.add(day[i-1],used[i]=G.nn(),INF,0);
			int r=ni();
			rsum+=r;
			G.add(s,used[i],r,0);
			G.add(day[i-1],t,r,0);
			G.add(used[i],buyer,INF,0);
		}
		G.add(day[n],buyer,INF,0);
		for(int i=1;i<=shop;i++){
			int c=ni(),p=ni();
			G.add(buyer,day[0],c,p);
		}
		for(int i=1;i<=maint;i++){
			int gap=ni(),w=ni();
			for(int j=1;gap+j<=n;j++){
				G.add(used[j],day[gap+j],INF,w);
			}
		}
		G.mcmf(s,t);
		if(G.flow<rsum){
			printf("Case %d: impossible\n",toti);
		}else{
			printf("Case %d: %d\n",toti,G.cost);
		}
	}
}
