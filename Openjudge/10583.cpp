#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <bitset>
#include <map> 
#define N 110
#define INF 2147483647
using namespace std;
int culture[N],to[N*N*2],bro[N*N*2],val[N*N*2],head[N],etop=0,k,hate[N][N];
struct node{
	bitset<N>b;
	int pos;
	node(int p,bitset<N>bi){
		pos=p,b=bi;
	}
};
queue<node>q;
template<>inline bool bitset<N>::operator <(const bitset<N>&a,const bitset<N>&b){
	for(int i=1;i<=k;i++){
		if(a.test(i)!=b.test(i)){
			return a.test(i)<b.test(i);
		}
	}
	return false;
}
map<bitset<N>,bool>inque[N];
map<bitset<N>,int>dis[N];
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
inline bool judge(bitset<N>b,int cul){
	for(int i=1;i<=k;i++){
		if(b.test(i)&&hate[cul][i]){
			return false;
		}
	}
	return true;
}
int main(){
	int n,m,s,t,u,v,w,x,d,ans=INF;
	scanf("%d%d%d%d%d",&n,&k,&m,&s,&t);
	for(int i=1;i<=n;i++){
		scanf("%d",culture+i);
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			scanf("%d",&hate[i][j]);
			if(i==j){
				hate[i][j]=true;
			}
		}
	}
	memset(head,-1,sizeof(head));
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	bitset<N>bi(0);
	bi.set(culture[s]);
	q.push(node(s,bi));
	while(!q.empty()){
		x=q.front().pos;
		bi=q.front().b;
		d=dis[x][bi];
		q.pop();
		inque[x][bi]=false;
		if(x==t){
			apmin(ans,d);
			continue;
		}
		for(int i=head[x];~i;i=bro[i]){
			v=to[i];
			if(judge(bi,culture[v])){
				bi.set(culture[v]);
				if(dis[v].find(bi)==dis[v].end()||dis[v][bi]>d+val[i]){
					dis[v][bi]=dis[x][bi]+val[i];
					if(inque[v].find(bi)==inque[v].end()||!inque[v][bi]){
						inque[v][bi]=true;
						q.push(node(v,bi));
					}
				}
				bi.reset(culture[v]);
			}
		}
	}
	if(ans==INF){
		printf("-1");
	}else{
		printf("%d",ans);
	}
}
