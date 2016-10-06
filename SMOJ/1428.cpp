#include <iostream>
#include <cstdio>
#include <cstring>
//#include <ctime>
#define N 260
#define M 10010
#define INF 2147483647
using namespace std;
int to[M<<1],bro[M<<1],val[M<<1],head[N],etop=0,
	c[N],eid[N][N],cost[N][N],
	dis[N*M],maxc[N*M],rbro[N*M],from[N*M],dhead[N],dtop,
	que[N*M*3],qhead,qtail;
bool inque[N*M];
inline void add_edge(int u,int v,int w){
	if(~eid[u][v]){
		if(w<val[eid[u][v]]){
			val[eid[u][v]]=w;
		}
		return;
	}
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	eid[u][v]=etop;
	head[u]=etop++;
}
inline int max(int a,int b){
	return a>b?a:b;
}
inline void enque(int &x,int d,int w,int node){
	if(x==-1){
		x=dtop++;
		dis[x]=d,maxc[x]=w,rbro[x]=-1,from[x]=node;
		inque[x]=true;
		que[qtail++]=x;
	}else{
		if(d<=dis[x]&&w<=maxc[x]){
			dis[x]=d,maxc[x]=w;
			if(!inque[x]){
				inque[x]=true;
				que[qtail++]=x;
			}
		}else if(d<dis[x]||w<maxc[x]){
			enque(rbro[x],d,w,node);
		}
	}
}
int main(){
	freopen("toll.in","r",stdin);
	freopen("toll.out","w",stdout);
	memset(eid,-1,sizeof(eid));
	memset(head,-1,sizeof(head));
	int n,m,k,u,v,w;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",c+i);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	//SPFA
//	cout<<"SPFA"<<endl;
	for(int p=1,x;p<=n;p++){
//		cout<<"From:"<<p<<endl;
		qhead=qtail=dtop=0;
		memset(inque,0,sizeof(inque));
		memset(dhead,-1,sizeof(dhead));
		enque(dhead[p],0,c[p],p);
		while(qhead!=qtail){
			x=que[qhead++];
//			cout<<"\tCur:"<<from[x]<<"\tdis="<<dis[x]<<"\tmaxc="<<maxc[x]<<endl;
			inque[x]=false;
			for(int i=head[from[x]];~i;i=bro[i]){
				enque(dhead[to[i]],dis[x]+val[i],max(maxc[x],c[to[i]]),to[i]);
			}
		}
		for(int i=p;i<=n;i++){
			cost[p][i]=INF;
			for(int j=dhead[i];~j;j=rbro[j]){
				if(dis[j]+maxc[j]<cost[p][i]){
					cost[p][i]=dis[j]+maxc[j];
				}
			}
			cost[i][p]=cost[p][i];
		}
	}
	while(k--){
		scanf("%d%d",&u,&v);
		printf("%d\n",cost[u][v]);
	}
//	printf("\n%dms",clock());
}
