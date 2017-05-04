#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=1010,E=10010,INF=0x7f7f7f7f;
int to[E],bro[E],val[E],cap[E],head[N];
inline void add_edge(int u,int v,int c,int w){
	static int etop=0;
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	cap[etop]=c;
	head[u]=etop++;
}
int que[N],dis[N],pre[N];
bool inque[N],use[N];
inline bool bfs(int s,int t){
	memset(dis,127,sizeof(dis));
	dis[s]=0;
	int qhead=0,qtail=0;
	que[qtail++]=s;
	while(qhead<qtail){
		int x=que[qhead++];
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(cap[i]&&dis[v]==INF){
				dis[v]=dis[x]+1;
				if(v==t){
					return true;
				}
				que[qtail++]=v;
			}
		}
	}
	return false;
}
inline void spfa(int s,int t){
	memset(dis,127,sizeof(dis));
	memset(inque,0,sizeof(inque));
	memset(pre,-1,sizeof(pre));
	memset(use,0,sizeof(use));
	dis[s]=0;
	int qhead=0,qtail=0;
	que[qtail++]=s;
	inque[s]=true;
	while(qhead!=qtail){
		int x=que[qhead++];
		if(qhead==N){
			qhead=0;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(dis[v]>dis[x]+(cap[i]>0?0:val[i])){
				dis[v]=dis[x]+(cap[i]>0?0:val[i]);
				if(dis[v]==dis[x]+val[i]){
					use[i]=true;
				}
				pre[v]=i^1;
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
int dinic(int x,int t,int alloc){
	if(x==t){
		return alloc;
	}
	int rest=alloc,delta;
	for(int i=head[x],v;rest&&(~i);i=bro[i]){
		v=to[i];
		if(cap[i]&&dis[v]==dis[x]+1){
			delta=dinic(v,t,min(rest,cap[i]));
			cap[i]-=delta,cap[i^1]+=delta;
			rest-=delta;
		}
	}
	return alloc-rest;
}
inline void aug(int p,int delta){
	for(;~pre[p];p=to[pre[p]]){
		cap[pre[p]]+=delta,cap[pre[p]^1]-=delta;
	}
}
int main(){
	memset(head,-1,sizeof(head));
	int n=ni(),m=ni(),k=ni();
	for(int i=0;i<m;i++){
		int u=ni(),v=ni(),c=ni(),w=ni();
		add_edge(u,v,c,w);
		add_edge(v,u,0,INF);
	}
	int flow=0,delta,cost=0;
	while(bfs(1,n)){
		flow+=dinic(1,n,INF);
	}
	while(k){
		spfa(1,n);
		delta=k;
		for(int p=n;~pre[p];p=to[pre[p]]){
			if(!use[pre[p]^1]){
				apmin(delta,cap[pre[p]^1]);
			}
		}
		aug(n,delta);
		k-=delta;
		cost+=delta*dis[n];
	}
	printf("%d %d",flow,cost);
}
