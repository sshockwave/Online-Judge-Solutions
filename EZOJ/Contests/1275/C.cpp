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
const int N=1010,E=2010,INF=0x7f7f7f7f;
int to[E],bro[E],cap[E],head[N],etop=0;
inline void add_edge(int u,int v,int c){
	to[etop]=v;
	bro[etop]=head[u];
	cap[etop]=c;
	head[u]=etop++;
}
int que[N],dis[N];
inline bool bfs(int s,int t){
	int qhead=0,qtail=0;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	que[qtail++]=s;
	while(qhead<qtail){
		int x=que[qhead++];
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(dis[v]==-1&&cap[i]){
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
int aug(int x,int alloc,int t){
	if(x==t){
		return alloc;
	}
	int rest=alloc,delta;
	for(int i=head[x],v;rest&&(~i);i=bro[i]){
		v=to[i];
		if(cap[i]&&dis[v]==dis[x]+1){
			if(delta=aug(v,min(rest,cap[i]),t)){
				rest-=delta;
				cap[i]-=delta,cap[i^1]+=delta;
			}
		}
	}
	if(rest==0){
		dis[x]=INF;
	}
	return alloc-rest;
}
inline int dinic(int s,int t){
	int flow=0;
	while(bfs(s,t)){
		flow+=aug(s,INF,t);
	}
	return flow;
}
int main(){
	int n=ni(),e=ni();
	memset(head,-1,sizeof(head));
	for(int i=1;i<=e;i++){
		int u=ni(),v=ni(),w=ni();
		add_edge(u,v,w);
		add_edge(v,u,0);
	}
	for(int tot=ni();tot--;){
		if(ni()){
			int id=(ni()-1)<<1;
			cap[id]=ni();
		}else{
			int s=ni(),t=ni();
			printf("%d\n",dinic(s,t));
			for(int i=0;i<e;i++){
				cap[i<<1]+=cap[(i<<1)|1];
				cap[(i<<1)|1]=0;
			}
		}
	}
}
