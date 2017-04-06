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
const int N=110,E=N*2,INF=0x7f7f7f7f;
int pval[N];
struct Graph{
	int to[E],bro[E],head[N],etop;
	inline void reset(){
		memset(head,-1,sizeof(head));
		etop=0;
	}
};
struct MaxFlow:Graph{
	int cap[E],dis[N],que[N],cur[N],last,s,t;
	inline void add_edge(int u,int v,int c,bool d){
		to[etop]=v;
		bro[etop]=head[u];
		cap[etop]=c;
		head[u]=etop++;
		if(d){
			add_edge(v,u,0,0);
		}
	}
	inline void build(int n){
		memset(head,-1,sizeof(head));
		etop=0;
		for(int i=1;i<=n;i++){
			if(pval[i]>0){
				add_edge(s,i,pval[i],true);
			}else if(pval[i]<0){
				add_edge(i,t,-pval[i],true);
			}
		}
	}
	inline void bfs(){
		int qhead=0,qtail=0;
		memset(dis,-1,sizeof(dis));
		dis[t]=0;
		que[qtail++]=t;
		while(qhead<qtail){
			int x=que[qhead++];
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(cap[i^1]&&dis[v]==-1){
					dis[v]=dis[x]+1;
					que[qtail++]=v;
				}
			}
		}
	}
	int dfs(int x,int alloc){
		if(x==t){
			return alloc;
		}
		int flow=0,delta;
		if(cur[x]==INF){
			cur[x]=head[x];
		}
		for(int &i=cur[x],v;~i;i=bro[i]){
			v=to[i];
			if(cap[i]&&dis[v]+1==dis[x]){
				if(delta=dfs(v,min(alloc,cap[i]))){
					cap[i]-=delta,cap[i^1]+=delta;
					alloc-=delta,flow+=delta;
				}
			}
		}
		return flow;
	}
	inline int dinic(){
		int flow=0;
		while(bfs(),memset(cur,127,sizeof(cur)),~dis[s]){
			flow+=dfs(s,INF);
		}
		return flow;
	}
}mf;
struct Tree:Graph{
	int fa[N];
	inline void add_edge(int u,int v,bool d){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
		if(d){
			add_edge(v,u,0);
		}
	}
	void dfs(int x){
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=fa[x]){
				fa[v]=x;
				dfs(v);
				mf.add_edge(v,x,INF,true);
			}
		}
	}
}t1,t2;
int main(){
	for(int tot=ni();tot--;){
		t1.reset(),t2.reset(),mf.reset();
		int n=ni(),mx=0,ans=0;
		mf.s=0,mf.t=n+1;
		for(int i=1;i<=n;i++){
			scanf("%d",pval+i);
			if(pval[i]>0){
				mx+=pval[i];
			}
		}
		for(int i=1;i<n;i++){
			t1.add_edge(ni(),ni(),true);
		}
		for(int i=1;i<n;i++){
			t2.add_edge(ni(),ni(),true);
		}
		for(int i=1;i<=n;i++){
			mf.build(n);
			t1.fa[i]=t2.fa[i]=0;
			t1.dfs(i),t2.dfs(i);
			apmax(ans,mx-mf.dinic());
		}
		printf("%d\n",ans);
	}
}
