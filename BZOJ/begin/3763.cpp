#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 210
#define E (N*4+2*N*N)
#define INF 0x7f7f7f7f
using namespace std;
inline bool is_num(char c){
    return c>='0'&&c<='9';
}
inline int ni(){
    int i=0;char c;
    while(!is_num(c=getchar()));
    while(i=i*10-'0'+c,is_num(c=getchar()));
    return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int to[E],bro[E],cap[E],val[E],head[N],etop=0,ntop=0;
inline int new_node(){
	return ntop++;
}
inline void add_edge(int u,int v,int c,int w,bool d=true){
	to[etop]=v;
	bro[etop]=head[u];
	cap[etop]=c;
	val[etop]=w;
	head[u]=etop++;
	if(d){
		add_edge(v,u,0,-w,false);
	}
}
int que[N],dis[N],pre[N],qhead,qtail;
bool inque[N];
inline void spfa(int s){
	qhead=qtail=0;
	memset(inque,0,sizeof(inque));
	memset(dis,127,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	que[qtail++]=s;
	inque[s]=true;
	dis[s]=0;
	while(qhead!=qtail){
		int x=que[qhead++];
		if(qhead==N){
			qhead=0;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(cap[i]&&dis[v]>dis[x]+val[i]){
				dis[v]=dis[x]+val[i];
				pre[v]=i^1;
				if(!inque[v]){
					inque[v]=true;
					que[qtail++]=v;
					if(qtail==N){
						qtail=0;
					}
				}
			}
		}
		inque[x]=false;
	}
}
int diff[N],add[N],rmov[N],node[N];
int main(){
	int n=ni(),tot=ni(),s=new_node(),t=new_node(),sum=0;
	memset(head,-1,sizeof(head));
	for(int i=0,last=-INF;i<n;i++){//diff[i]=h[i+1]-h[i]
		diff[i]=ni()-last;
		last+=diff[i];
		node[i]=new_node();
		if(diff[i]>0){
			add_edge(node[i],t,diff[i],0);
		}else if(diff[i]<0){
			add_edge(s,node[i],-diff[i],0);
			sum-=diff[i];
		}
	}
	diff[n]=INF;
	node[n]=new_node();
	add_edge(node[n],t,diff[n],0);
	memset(add,127,sizeof(add));
	memset(rmov,127,sizeof(rmov));
	char op;
	for(int i=0,cur;i<tot;i++){
		while(op=getchar(),op!='+'&&op!='-');
		cur=ni();
		if(op=='+'){
			apmin(add[cur],ni());
		}else{
			apmin(rmov[cur],ni());
		}
	}
	for(int i=1;i<=n;i++){
		if(add[i]!=INF){
			for(int j=0;i+j<=n;j++){
				add_edge(node[j],node[i+j],INF,add[i]);
			}
		}
		if(rmov[i]!=INF){
			for(int j=0;i+j<=n;j++){
				add_edge(node[i+j],node[j],INF,rmov[i]);
			}
		}
	}
	int cost=0,totflow=0;
	while(spfa(s),~pre[t]){
		int flow=INF;
		for(int p=t;~pre[p];p=to[pre[p]]){
			apmin(flow,cap[pre[p]^1]);
		}
		totflow+=flow;
		cost+=dis[t]*flow;
		for(int p=t;~pre[p];p=to[pre[p]]){
			cap[pre[p]]+=flow,cap[pre[p]^1]-=flow;
		}
	}
	if(totflow==sum){
		printf("%d",cost);
	}else{
		puts("-1");
	}
}
