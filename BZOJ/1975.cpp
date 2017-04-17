#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=5010,E=200010*2;
int to[E],bro[E],val[E],head[N],rhead[N];
inline void add_edge(int u,int v,int w,int *head){
	static int etop=0;
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	head[u]=etop++;
}
int dis[N];
inline void spfa(int s,int *head){
	memset(dis,127,sizeof(dis));
	bool *inque=new bool[N];
	memset(inque,0,N<<2);
	queue<int>q;
	q.push(s);
	dis[s]=0;
	inque[s]=true;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(dis[v]>dis[x]+val[i]){
				dis[v]=dis[x]+val[i];
				if(!inque[v]){
					inque[v]=true;
					q.push(v);
				}
			}
		}
		inque[x]=false;
	}
}
struct state{
	int x,dis;
};
inline bool operator < (const state &a,const state &b){
	return a.dis+dis[a.x]>b.dis+dis[b.x];
}
inline int astar(int t,int sum){
	priority_queue<state>q;
	q.push(1);
	int cnt=0;
	while(!q.empty()){
		state s=q.top();
		q.pop();
		if(s.x==t){
			if(s.dis>sum){
				return cnt;
			}
			cnt++;
			sum-=s.dis;
			if(sum==0){
				return cnt;
			}
		}
		for(int i=head[s.x];~i;i=bro[i]){
			q.push((state){to[i],s.dis+val[i]});
		}
	}
	return cnt;
}
int main(){
	int n=ni(),m=ni(),e=ni();
	for(int i=1,u,v,w;i<=m;i++){
		u=ni(),v=ni(),w=ni();
		add_edge(u,v,w,head);
		add_edge(v,u,w,rhead);
	}
	spfa(n,rhead);
	printf("%d\n",astar(n,e));
}
