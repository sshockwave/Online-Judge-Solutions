#include <iostream>
#include <cstdio>
#include <cstring>
#define N 60
#define C 10010
#define INF 2147483647
using namespace std;
int to[N<<1],bro[N<<1],val[N<<1],head[N],etop=0,qhead,qtail,quei[N*C*2],quec[N*C*2];
long long reach[N][C];
bool inq[N][C];
inline int add_edge(int u,int v,int w){
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
int main(){
	freopen("1424.in","r",stdin);
	freopen("1424.out","w",stdout);
	int tot,n,m,u,v,w,modder,x,hash,cur,chash;
	long long t;
	for(scanf("%d",&tot);tot--;){
		memset(head,-1,sizeof(head));
		memset(reach,-1,sizeof(reach));
		memset(inq,0,sizeof(inq));
		cin>>n>>m>>t;
		while(m--){
			scanf("%d%d%d",&u,&v,&w);
			add_edge(u,v,w);
			add_edge(v,u,w);
		}
		modder=INF;
		for(int i=head[0];~i;i=bro[i]){
			if(val[i]<modder){
				modder=val[i];
			}
		}
		if(modder==INF){
			printf("Impossible\n");
			continue;
		}
		modder<<=1;
		qhead=qtail=0;
		reach[0][0]=0;
		inq[0][0]=true;
		quei[qtail]=0,quec[qtail]=0,qtail++;
		while(qhead!=qtail){
			x=quei[qhead],hash=quec[qhead],qhead++;
			inq[x][hash]=false;
			for(int i=head[x];~i;i=bro[i]){
				cur=to[i],chash=(hash+val[i])%modder;
				if(reach[cur][chash]==-1||reach[cur][chash]>reach[x][hash]+val[i]){
					reach[cur][chash]=reach[x][hash]+val[i];
					if(!inq[cur][chash]){
						inq[cur][chash]=true;
						quei[qtail]=cur,quec[qtail]=chash,qtail++;
					}
				}
			}
		}
		if(reach[n-1][t%modder]!=-1&&reach[n-1][t%modder]<=t){
			printf("Possible\n");
		}else{
			printf("Impossible\n");
		}
	}
	return 0;
}
