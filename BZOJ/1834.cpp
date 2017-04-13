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
			if(dis[v]>dis[x]+(cap[i]?0:val[i])){
				dis[v]=dis[x]+(cap[i]?0:val[i]);
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
inline int amtcnt(int p){
	int delta=INF;
	for(;~pre[p];p=to[pre[p]]){
		apmin(delta,cap[pre[p]^1]);
	}
	return delta;
}
inline int amtcnt2(int p){
	int delta=INF;
	for(;~pre[p];p=to[pre[p]]){
		if(!use[pre[p]^1]){
			apmin(delta,cap[pre[p]^1]);
		}
	}
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
	int flow=0,delta,cost;
	while(spfa(1,n),dis[n]==0){
		delta=amtcnt(n);
		aug(n,delta);
		flow+=delta;
	}
	while(k){
		spfa(1,n);
		delta=min(k,amtcnt2(n));
		aug(n,delta);
		k-=delta;
		cost+=delta*dis[n];
	}
	printf("%d %d",flow,cost);
}
