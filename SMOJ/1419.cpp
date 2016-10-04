#include <iostream>
#include <cstdio>
#include <cstring>
//#include <ctime>
#define N 10010
#define M 50010
using namespace std;
int to[M],bro[M],head[N],que[N],qhead,qtail,etop=0,n;
bool vis[N],valid[N];
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
inline bool judge(){
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			return false;
		}
	}
	return true;
}
int main(){
	freopen("1419.in","r",stdin);
	freopen("1419.out","w",stdout);
	memset(head,-1,sizeof(head));
	memset(valid,0,sizeof(valid));
	int m,u,v,x,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",&u,&v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			vis[j]=false;
		}
		qhead=qtail=0;
		que[qtail++]=i;
		vis[i]=true;
		while(qhead!=qtail){
			x=que[qhead++];
			if(valid[x]){
				valid[i]=true;
				break;
			}
			for(int i=head[x];~i;i=bro[i]){
				if(!vis[to[i]]){
					vis[to[i]]=true;
					que[qtail++]=to[i];
				}
			}
		}
		if(!valid[i]){
			valid[i]=judge();
		}
		if(valid[i]){
			ans++;
		}
	}
	printf("%d",ans);
//	printf("\n%dms",clock());
}
