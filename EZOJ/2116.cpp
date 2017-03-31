#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int a,int b){
	if(a>b){
		a=b;
	}
}
const int N=1010,E=22010,INF=0x7f7f7f7f;
const long long LINF=0x7f7f7f7f7f7f7f7fll;
int to[E],bro[E],val[E],cap[E],head[N],pre[N],etop=0;
inline void add_edge(int u,int v,int w,int c,bool d){
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	cap[etop]=c;
	head[u]=etop++;
	if(d){
		add_edge(v,u,-w,0,0);
	}
}
int que[N];
long long dis[N];
bool inque[N];
inline void spfa(int s){
	int qhead=0,qtail=0;
	memset(inque,0,sizeof(inque));
	memset(pre,-1,sizeof(pre));
	memset(dis,127,sizeof(dis));
	dis[s]=0;
	inque[s]=true;
	que[qtail++]=s;
	while(qhead!=qtail){
		int x=que[qhead++];
		if(qhead==N){
			qhead=0;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(cap[i]&&dis[v]>dis[x]+val[i]){
				dis[v]=dis[x]+val[i];
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
int main(){
	int n=ni(),tot=ni(),s=0,t=n+2,last=0;
	memset(head,-1,sizeof(head));
	for(int i=1,cur;i<=n;i++){
		cur=ni();
		if(last>cur){
			add_edge(s,i,0,last-cur,1);
		}else{
			add_edge(i,t,0,cur-last,1);
		}
		last=cur;
		add_edge(i,i+1,0,INF,1);
	}
	add_edge(s,n+1,0,last,1);
	while(tot--){
		int s=ni(),t=ni(),c=ni();
		add_edge(t+1,s,c,INF,1);
	}
	long long cost=0;
	while(spfa(s),dis[t]<LINF){
		int delta=INF;
		for(int p=t;~p;p=to[pre[p]]){
			apmin(delta,cap[pre[p]^1]);
		}
		cost+=dis[t]*delta;
		for(int p=t;~p;p=to[pre[p]]){
			cap[pre[p]]+=delta,cap[pre[p]^1]-=delta;
		}
	}
	printf("%lld",cost);
}
