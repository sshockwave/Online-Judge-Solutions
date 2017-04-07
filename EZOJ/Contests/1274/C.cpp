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
int f1[N],f2[N],*fa,size;
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
int que[N],dis[N],s=0,t;
inline bool bfs(){
	int qhead=0,qtail=0;
	memset(dis,-1,size);
	que[qtail++]=s;
	dis[s]=0;
	while(qhead<qtail){
		int x=que[qhead++];
		for(int i=hf[x],v;~i;i=bro[i]){
			if(dis[v=to[i]]==-1&&cap[i]){
				dis[v]=dis[x]+1;
				if(v==t){
					return true;
				}
				que[qtail++]=v;
			}
		}
	}
	return false;
}
int aug(int x,int alloc){
	if(x==t){
		return alloc;
	}
	int rest=alloc,delta;
	for(int i=hf[x],v;rest&&(~i);i=bro[i]){
		v=to[i];
		if(cap[i]&&dis[v]==dis[x]+1){
			assert(cap[i]>0);
			if(delta=aug(v,min(cap[i],rest))){
				rest-=delta;
				cap[i]-=delta,cap[i^1]+=delta;
			}
		}
	}
	if(alloc==rest){
		dis[x]=INF;
	}
	return alloc-rest;
}
int main(){
	for(int tot=ni();tot--;){
		int n=ni(),sum=0,ans=0;
		size=(n+2)<<2;
		for(int i=1;i<=n;i++){
			scanf("%d",pval+i);
			if(pval[i]>0){
				sum+=pval[i];
			}
		}
		etop=0;
		memset(h1,-1,size);
		for(int i=1,u,v;i<n;i++){
			u=ni(),v=ni();
			add_edge(u,v,h1);
			add_edge(v,u,h1);
		}
		memset(h2,-1,size);
		for(int i=1,u,v;i<n;i++){
			u=ni(),v=ni();
			add_edge(u,v,h2);
			add_edge(v,u,h2);
		}
		int last=etop;
		t=n+1;
		for(int i=1;i<=n;i++){
			etop=last;
			memset(hf,-1,size);
			f1[i]=f2[i]=0;
			head=h1,fa=f1,dfs(i);
			head=h2,fa=f2,dfs(i);
			for(int j=1;j<=n;j++){
				if(pval[j]>0){
					add_edge(s,j,pval[j]);
					add_edge(j,s,0);
				}else if(pval[j]<0){
					add_edge(j,t,-pval[j]);
					add_edge(t,j,0);
				}
				if(i!=j){
					add_edge(j,f1[j],INF);
					add_edge(f1[j],j,0);
					add_edge(j,f2[j],INF);
					add_edge(f2[j],j,0);
				}
			}
			int flow=0;
			while(bfs()){
				flow+=aug(s,INF);
			}
			apmax(ans,sum-flow);
		}
		printf("%d\n",ans);
	}
}
