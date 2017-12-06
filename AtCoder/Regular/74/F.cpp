#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=110,INF=0x7f7f7f7f;
namespace G{
	const int N=110*2,E=110*110*2*2;
	int to[E],bro[E],cap[E],head[N],e=0,s,t;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N];
	inline void bfs(){
		memset(dis,-1,t<<2);
		int qh=0,qt=0;
		dis[que[qt++]=t]=0;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i^1]&&dis[v=to[i]]==-1){
					dis[que[qt++]=v]=dis[x]+1;
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t)return a;
		int r=a,d;
		for(int i=head[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]-1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		return r?dis[x]=-1,a-r:a;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),~dis[s];flow+=aug(s,INF));
		return flow;
	}
}
char s[N];
inline int Main(){
	int n=ni,m=ni;
	int sx,sy,tx,ty;
	G::init();
	G::s=n+m+1,G::t=n+m+2;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='S'){
				sx=i,sy=j;
				G::add(G::s,i,INF);
				G::add(G::s,j+n,INF);
			}else if(s[j]=='T'){
				tx=i,ty=j;
				G::add(i,G::t,INF);
				G::add(j+n,G::t,INF);
			}else if(s[j]=='o'){
				G::add(i,j+n,1);
				G::add(j+n,i,1);
			}
		}
	}
	return sx==tx||sy==ty?-1:G::dinic();
}
int main(){
	printf("%d\n",Main());
	return 0;
}
