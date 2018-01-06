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
const int L=110,N=510,INF=0x7f7f7f7f;
namespace G{
	const int N=L*L,E=(N*8+::N*2)*2;
	int to[E],bro[E],val[E],cap[E],head[N],e=0,n=0,s,t;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		s=nn(),t=nn();
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w,int c){
		to[e]=v,bro[e]=head[u],val[e]=w,cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int w,int c){
		ae(u,v,w,c),ae(v,u,-w,0);
	}
	int dis[N],pre[N],que[N];
	bool inque[N];
	inline void spfa(){
		memset(dis+1,127,n<<2);
		memset(inque+1,0,n);
		int qh=0,qt=0;
		dis[s]=0,pre[s]=-1,inque[s]=true,que[qt++]=s;
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			inque[x]=false;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i],pre[v]=i;
					if(!inque[v]){
						inque[v]=true,que[qt++]=v;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
		}
	}
	inline int aug(){
		int dt=INF;
		for(int p=t;p!=s;p=to[pre[p]^1]){
			apmin(dt,cap[pre[p]]);
		}
		for(int p=t;p!=s;p=to[pre[p]^1]){
			cap[pre[p]]-=dt,cap[pre[p]^1]+=dt;
		}
		return dt;
	}
}
int node[L][L];
int r,c;
inline bool valid(int x,int y){
	return x>=1&&x<=r&&y>=1&&y<=c;
}
char s[L];
int main(){
#ifndef ONLINE_JUDGE
	freopen("willow.in","r",stdin);
	freopen("willow.out","w",stdout);
#endif
	r=ni,c=ni;
	int n=ni,a=ni,b=ni;
	G::init();
	for(int i=1;i<=r;i++){
		scanf("%s",s+1);
		for(int j=1;j<=c;j++){
			node[i][j]=s[j]=='.'?G::nn():0;
		}
	}
	const int dx[]={a,a,-a,-a,b,b,-b,-b},dy[]={b,-b,b,-b,a,-a,a,-a};
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(node[i][j]==0)continue;
			for(int d=0;d<8;d++){
				int x=i+dx[d],y=j+dy[d];
				if(valid(x,y)&&node[x][y]){
					G::add(node[i][j],node[x][y],1,INF);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		int x=ni,y=ni;
		G::add(G::s,node[x][y],0,1);
	}
	for(int i=1;i<=n;i++){
		int x=ni,y=ni;
		G::add(node[x][y],G::t,0,1);
	}
	int flow=0,cost=0;
	for(int dt;G::spfa(),G::dis[G::t]<INF;dt=G::aug(),flow+=dt,cost+=dt*G::dis[G::t]);
	printf("%d\n",flow==n?cost:-1);
	return 0;
}
