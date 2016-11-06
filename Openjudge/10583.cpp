#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <bitset>
#define N 110
#define INF 2147483647
using namespace std;
int culture[N],to[N*N*2],bro[N*N*2],val[N*N*2],head[N],etop=0,k;
bool hate[N][N],reachable[N];
struct state{
	int pos,dis;
	bitset<N>b;
	state(int p,int d,bitset<N>bi){
		pos=p,dis=d,b=bi;
	}
};
queue<state>q;
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
	int n,m,s,t,u,v,w,tmp,ans=INF;
	scanf("%d%d%d%d%d",&n,&k,&m,&s,&t);
	for(int i=1;i<=n;i++){
		scanf("%d",culture+i);
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			scanf("%d",&tmp);
			hate[i][j]=tmp;
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
	for(int i=1;i<=n;i++){
		reachable[i]=culture[i]!=culture[t];
	}
	reachable[t]=true;
	bitset<N>bi(0);
	bi.set(culture[s]);
	q.push(state(s,0,bi));
	while(!q.empty()){
		state cur=q.front();
		q.pop();
		if(cur.pos==t){
			apmin(ans,cur.dis);
			continue;
		}
		for(int i=head[cur.pos];~i;i=bro[i]){
			if(reachable[to[i]]&&judge(cur.b,culture[to[i]])&&cur.dis+val[i]<ans){
				cur.b.set(culture[to[i]]);
				cur.dis+=val[i];
				cur.pos=to[i];
				q.push(cur);
				cur.dis-=val[i];
				cur.b.reset(culture[to[i]]);
			}
		}
	}
	if(ans==INF){
		printf("-1");
	}else{
		printf("%d",ans);
	}
}
