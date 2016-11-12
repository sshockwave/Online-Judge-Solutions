#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#define N 100010
#define M 500010
using namespace std;
queue<pair<int,bool> >q;
int price[N],to[M<<1],bro[M<<1],head[N],etop=0,dis[N][2];
bool inq[N][2];
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
int main(){
	int n,m,u,v,w;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",price+i);
	}
	memset(head,-1,sizeof(head));
	while(m--){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v);
		if(w==2){
			add_edge(v,u);
		}
	}
	memset(dis,-1,sizeof(dis));
	memset(inq,0,sizeof(inq));
	q.push(make_pair(1,false));
	inq[1][0]=true;
	dis[1][0]=0;
	while(!q.empty()){
		int x=q.front().first,bene;
		bool traded=q.front().second;
		q.pop();
		for(int i=head[x];~i;i=bro[i]){
			if(price[to[i]]>price[x]&&!traded){
				bene=price[to[i]]-price[x];
				if(bene>dis[to[i]][true]){
					dis[to[i]][true]=bene;
					if(!inq[to[i]][true]){
						inq[to[i]][true]=true;
						q.push(make_pair(to[i],true));
					}
				}
			}
			if(dis[x][traded]>dis[to[i]][traded]){
				dis[to[i]][traded]=dis[x][traded];
				if(!inq[to[i]][traded]){
					inq[to[i]][traded]=true;
					q.push(make_pair(to[i],traded));
				}
			}
		}
		inq[x][traded]=false;
	}
	printf("%d",max(dis[n][0],dis[n][1]));
}
