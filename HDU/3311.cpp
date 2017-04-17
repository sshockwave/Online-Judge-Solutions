#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=1010,P=5,E=10010,INF=0x7f7f7f7f;
int n,p,dis[N][N];
struct Graph{
	int to[E],bro[E],val[E],head[N],etop;
	inline void reset(){
		etop=qhead=qtail=0;
		memset(head,-1,sizeof(head));
		memset(inque,0,sizeof(inque));
	}
	inline void add_edge(int u,int v,int w){
		to[etop]=v;
		bro[etop]=head[u];
		val[etop]=w;
		head[u]=etop++;
	}
	int que[N],qhead,qtail;
	bool inque[N];
	inline void push(int x){
		if(!inque[x]){
			inque[x]=true;
			que[qtail++]=x;
			if(qtail==N){
				qtail=0;
			}
		}
	}
	inline void spfa(int *dis){
		while(qhead!=qtail){
			int x=que[qhead++];
			if(qhead==N){
				qhead=0;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(dis[v]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i];
					push(v);
				}
			}
			inque[x]=false;
		}
	}
}G;
int f[1<<P][N];
int main(){
	int e;
	while(scanf("%d%d%d",&p,&n,&e)>0){
		n+=p;
		G.reset();
		for(int i=1,w;i<=n;i++){
			w=ni();
			G.add_edge(0,i,w);
			G.add_edge(i,0,w);
		}
		while(e--){
			int u=ni(),v=ni(),w=ni();
			G.add_edge(u,v,w);
			G.add_edge(v,u,w);
		}
		memset(dis,127,sizeof(dis));
		for(int i=0;i<=n;i++){
			G.push(i);
			dis[i][i]=0;
			G.spfa(dis[i]);
		}
		memset(f,127,sizeof(f));
		for(int i=0;i<=p;i++){
			f[1<<i][i]=0;
		}
		for(int i=0,_=1<<(p+1);i<_;i++){
			for(int j=0;j<=n;j++){
				for(int k=i;k=(k-1)&i;){
					if(f[k][j]<INF&&f[k^i][j]<INF){
						apmin(f[i][j],f[k][j]+f[k^i][j]);
					}
				}
			}
			for(int j=0;j<=n;j++){
				if(f[i][j]<INF){
					for(int k=0;k<=n;k++){
						if(dis[j][k]<INF){
							apmin(f[i][k],f[i][j]+dis[j][k]);
						}
					}
				}
			}
		}
		printf("%d\n",f[(1<<(p+1))-1][0]);
	}
}
