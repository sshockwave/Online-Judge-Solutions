#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
inline int apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=110,E=N*20,INF=0x7f7f7f7f;
int pval[N];
int to[E],bro[E],cap[E],h1[N],h2[N],hf[N],etop=0;
int fa[N];
inline void add_edge(int u,int v,int *head){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
inline void add_edge(int u,int v,int c){
	cap[etop]=c;
	add_edge(u,v,hf);
}
int *head;
void dfs(int x){
	for(int i=head[x],v;~i;i=bro[i]){
		v=to[i];
		if(v!=fa[x]){
			fa[v]=x;
			dfs(v);
		}
	}
}
int que[N],dis[N];
inline void bfs(int t){
	int qhead=0,qtail=0;
	memset(dis,-1,sizeof(dis));
	que[qtail++]=t;
	dis[t]=0;
	while(qhead<qtail){
		int x=que[qhead++];
		for(int i=hf[x],v;~i;i=bro[i]){
			v=to[i];
			if(dis[v]==-1&&cap[i^1]){
				dis[v]=dis[x]+1;
				que[qtail++]=v;
			}
		}
	}
}
int cur[N];
int aug(int x,int alloc){
	int rest=alloc,delta;
	if(cur[x]==INF){
		cur[x]=hf[x];
	}
	for(int i=cur[x],v;~i;i=bro[i]){
		v=to[i];
		if(cap[i]&&dis[v]+1==dis[x]){
			if(delta=aug(v,min(cap[i],rest))){
				rest-=delta;
				cap[i]-=delta,cap[i^1]+=delta;
				if(rest==0){
					break;
				}
			}
		}
	}
	return alloc-rest;
}
int main(){
	for(int tot=ni();tot--;){
		int n=ni(),sum=0,ans=0;
		for(int i=1;i<=n;i++){
			scanf("%d",pval+1);
			if(pval[i]>0){
				sum+=pval[i];
			}
		}
		etop=0;
		memset(h1,0,sizeof(h1));
		for(int i=1,u,v;i<=n;i++){
			u=ni(),v=ni();
			add_edge(u,v,h1);
			add_edge(v,u,h1);
		}
		for(int i=1,u,v;i<=n;i++){
			u=ni(),v=ni();
			add_edge(u,v,h2);
			add_edge(v,u,h2);
		}
		int s=0,t=n+1,last=etop;
		for(int i=1;i<=n;i++){
			etop=last;
			for(int j=1;j<=n;j++){
				if(pval[j]>0){
					add_edge(s,j,pval[j]);
				}else if(pval[j]<0){
					add_edge(j,t,-pval[j]);
				}
			}
			fa[i]=0,head=h1,dfs(i);
			for(int j=1;j<=n;j++){
				if(j!=i){
					add_edge(j,fa[j],INF);
				}
			}
			fa[i]=0,head=h2,dfs(i);
			for(int j=1;j<=n;j++){
				if(j!=i){
					add_edge(j,fa[j],INF);
				}
			}
			int flow=0;
			while(bfs(t),~dis[s]){
				memset(cur,127,sizeof(int)*(n+2));
				flow+=aug(s,INF);
			}
			apmax(ans,sum-flow);
		}
		printf("%d\n",ans);
	}
}
