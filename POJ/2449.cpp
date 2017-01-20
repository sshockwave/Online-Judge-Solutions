#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
#define V 1010
#define E 100010
using namespace std;
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int dis[V],to[E],val[E],bro[E],head[V],etop=0;
namespace rev{
	int to[E],val[E],bro[E],head[V],etop=0,que[V],qhead=0,qtail=0;
	bool inque[V];
	inline void add_edge(int u,int v,int w){
		to[etop]=v;
		val[etop]=w;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	inline void push(int x){
		que[qtail++]=x;
		if(qtail==V){
			qtail=0;
		}
	}
	inline int pop(){
		int x=que[qhead++];
		if(qhead==V){
			qhead=0;
		}
		return x;
	}
	inline void spfa(int x){
		memset(inque,0,sizeof(inque));
		memset(dis,127,sizeof(dis));
		dis[x]=0;
		push(x);
		inque[x]=true;
		while(qhead!=qtail){
			x=pop();
			for(int i=head[x];~i;i=bro[i]){
				if(dis[to[i]]>dis[x]+val[i]){
					dis[to[i]]=dis[x]+val[i];
					if(!inque[to[i]]){
						push(to[i]);
						inque[to[i]]=true;
					}
				}
			}
			inque[x]=false;
		}
	}
}
inline void add_edge(int w,int v,int u){//should be reversed
	rev::add_edge(v,u,w);
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
struct state{
	int x,f;
	state(int node,int d){
		x=node;
		f=d+dis[x];
	}
};
bool operator < (state a,state b){
	return a.f>b.f;
}
priority_queue<state>q;
int main(){
	memset(head,-1,sizeof(head));
	memset(rev::head,-1,sizeof(rev::head));
	int v=nextInt(),e=nextInt(),x,t,k,d;
	while(e--){
		add_edge(nextInt(),nextInt(),nextInt());
	}
	q.push(state(nextInt(),0)),rev::spfa(t=nextInt()),k=nextInt();
	while(!q.empty()){
		x=q.top().x,d=q.top().f-dis[x];
		q.pop();
		if(x==t){
			k--;
			if(k==0){
				printf("%d",d);
				return 0;
			}
		}
		for(int i=head[x];~i;i=bro[i]){
			q.push(state(to[i],d+val[i]));
		}
	}
	puts("-1");
}
