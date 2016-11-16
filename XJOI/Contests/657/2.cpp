#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 310
#define M 40010
#define INF 0x7f7f7f7f
using namespace std;
int c[N],to[M<<1],bro[M<<1],val[M<<1],head[N],etop=0,dis[N][N],
	sumv[M],maxc[M],cbro[M],bln[M],chead[N],ctop;
bool inq[M];
queue<int>q;
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	head[u]=etop++;
}
int get_node(int &x,int sum,int mx,int bl){
	if(x==-1){
		x=ctop++;
		sumv[x]=sum;
		maxc[x]=mx;
		cbro[x]=-1;
		bln[x]=bl;
		return x;
	}
	if(sum<=sumv[x]&&mx<=maxc[x]){
		sumv[x]=sum;
		maxc[x]=mx;
		return x;
	}
	if(sum>=sumv[x]&&mx>=maxc[x]){
		return -1;
	}
	return get_node(cbro[x],sum,mx,bl);
}
int main(){
	int n,m,u,v,w,qury;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",c+i);
	}
	memset(head,-1,sizeof(head));
	while(m--){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	memset(inq,0,sizeof(inq));
	for(int i=1;i<n;i++){
		memset(chead,-1,sizeof(chead));
		ctop=0;
		q.push(get_node(chead[i],0,c[i],i));
		while(!q.empty()){
			int x=q.front();
			q.pop();
			for(int j=head[bln[x]];~j;j=bro[j]){
				int cnode=get_node(chead[to[j]],sumv[x]+val[j],max(maxc[x],c[to[j]]),to[j]);
				if(~cnode){
					if(!inq[cnode]){
						inq[cnode]=true;
						q.push(cnode);
					}
				}
			}
			inq[x]=false;
		}
		for(int j=i+1,p;j<=n;j++){
			dis[i][j]=INF;
			for(int p=chead[j];~p;p=cbro[p]){
				apmin(dis[i][j],sumv[p]+maxc[p]);
			}
			dis[j][i]=dis[i][j];
		}
	}
	for(scanf("%d",&qury);qury--;){
		scanf("%d%d",&u,&v);
		printf("%d\n",dis[u][v]);
	}
	return 0;
}
