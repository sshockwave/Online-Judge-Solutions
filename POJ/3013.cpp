#include <iostream> 
#include <cstdio>
#include <cstring>
#include <cassert>
#define V 50010
#define E 50010
#define INF 0x7f7f7f7f
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
int weight[V],to[E*2],val[E*2],bro[E*2],head[V],etop=0,que[V],qhead,qtail,dis[V];
bool inque[V];
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
int main(){
	for(int tot=nextInt();tot--;){
		memset(head,-1,sizeof(head));
		etop=0;
		int v=nextInt(),e=nextInt(),a,b,c;
		long long ans=0;
		for(int i=1;i<=v;i++){
			weight[i]=nextInt();
		}
		while(e--){
			a=nextInt(),b=nextInt(),c=nextInt();
			add_edge(a,b,c);
			add_edge(b,a,c);
		}
		qhead=qtail=0;
		memset(inque,0,sizeof(inque));
		memset(dis,127,sizeof(dis));
		assert(dis[0]==INF);
		que[qtail++]=1;
		dis[1]=0;
		inque[1]=true;
		while(qhead!=qtail){
			int x=que[qhead++];
			if(qhead==V){
				qhead=0;
			}
			for(int i=head[x];~i;i=bro[i]){
				if(dis[to[i]]>dis[x]+val[i]){
					dis[to[i]]=dis[x]+val[i];
					if(!inque[to[i]]){
						inque[to[i]]=true;
						que[qtail++]=to[i];
						if(qtail==V){
							qtail=0;
						}
					}
				}
			}
			inque[x]=false;
		}
		bool fail=false;
		for(int i=1;i<=v;i++){
			if(dis[i]==INF){
				fail=true;
				break;
			}
			ans+=1ll*weight[i]*dis[i];
		}
		if(fail){
			puts("-1");
		}else{
			printf("%lld\n",ans);
		}
	}
}
