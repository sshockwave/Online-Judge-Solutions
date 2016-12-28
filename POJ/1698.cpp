#include <iostream>
#include <cstdio>
#include <cstring>
#define W 55
#define N 22
#define E N+N*W*7+W*7
#define INF 2147483647
using namespace std;
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int n=0;
	char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);c=getchar()){
		n=n*10-'0'+c;
	}
	return n;
}
int to[E*2],bro[E*2],val[E*2],head[W*7+N],dis[W*7+N],que[W*7+N],qhead,qtail,day[W][7],erset,nrset,etop=0,ntop=0;
bool film[7];
inline int new_node(){
	head[ntop]=-1;
	return ntop++;
}
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	head[u]=etop++;
}
inline void bfs(int s){
	qhead=qtail=0;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
#define push(x) que[qtail++]=(x);
#define pop() que[qhead++]
	push(s);
	while(qhead<qtail){
		int x=pop();
		for(int i=head[x];~i;i=bro[i]){
			if(val[i]&&dis[to[i]]==-1){
				dis[to[i]]=dis[x]+1;
				push(to[i]);
			}
		}
	}
}
int dfs(int x,int alloc){
	int sum=0,flow;
	for(int i=head[x];~i&&sum<=alloc;i=bro[i]){
		if(val[i]&&dis[to[i]]==dis[x]-1){
			flow=dfs(to[i],min(val[i],alloc-sum));
			sum+=flow;
			val[i]-=flow;
			val[i^1]+=flow;
		}
	}
	return sum;
}
int main(){
	int s=new_node(),t=new_node(),flow,sum;
	for(int i=0;i<W;i++){
		for(int j=0;j<7;j++){
			day[i][j]=new_node();
			add_edge(day[i][j],t,1);
			add_edge(t,day[i][j],0);
		}
	}
	erset=etop,nrset=ntop;
	for(int tot=nextInt();tot--;){
		etop=erset,ntop=nrset;
		sum=0;
		for(int cnt=nextInt(),cur,d,w;cnt--;){
			for(int i=0;i<7;i++){
				film[i]=nextInt();
			}
			cur=new_node();
			add_edge(s,cur,d=nextInt());
			add_edge(cur,s,0);
			sum+=d;
			w=nextInt();
			for(int i=0;i<7;i++){
				if(film[i]){
					for(int j=0;j<w;j++){
						add_edge(cur,day[j][i],1);
						add_edge(day[j][i],cur,0);
					}
				}
			}
		}
		while(bfs(t),sum-=(flow=dfs(s,INF)),flow);
		if(sum==0){
			puts("Yes\n");
		}else{
			puts("No\n");
		}
	}
}
