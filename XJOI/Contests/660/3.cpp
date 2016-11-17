#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
#define M 100010
#define V (N+M)
using namespace std;
int to[V<<1],bro[V<<1],val[V<<1],head[N],etop=0,dis[N],que[N],qhead,qtail;
bool inq[N];
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	head[u]=etop++;
}
int main(){
	memset(head,-1,sizeof(head));
	memset(inq,0,sizeof(inq));
	memset(dis,127,sizeof(dis));
	int n,m,u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		add_edge(i,i+1,1);
		add_edge(i+1,i,0);
	}
	while(m--){
		scanf("%d%d",&u,&v);
		add_edge(u,v+1,1);
		add_edge(v+1,u,-1);
	}
	dis[1]=0;
	inq[1]=true;
	qhead=qtail=0;
	que[qtail++]=1;
	while(qhead!=qtail){
		int x=que[qhead++];
		qhead%=N;
		inq[x]=false;
		for(int i=head[x];~i;i=bro[i]){
			if(dis[to[i]]>dis[x]+val[i]){
				dis[to[i]]=dis[x]+val[i];
				if(!inq[to[i]]){
					inq[to[i]]=true;
					if(dis[to[i]]<dis[que[qhead]]){
						(qhead+=N-1)%=N;
						que[qhead]=to[i];
					}else{
						que[qtail++]=to[i];
						qtail%=N;
					}
				}
			}
		}
	}
	printf("%d",dis[n+1]);
	return 0;
}
