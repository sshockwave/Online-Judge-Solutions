#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1010,INF=0x7f7f7f7f;
namespace G{
	const int E=5010<<1;
	int to[E],bro[E],cap[E],val[E],head[N],e,s,t,n;
	int dis[N],dt[N],pre[N];
	inline void init(int _n){
		n=_n;
		mset(head+1,-1,n);
		mset(dis+1,0,n);
		e=0;
		s=1,t=n;
	}
	inline void ae(int u,int v,int c,int w){
		to[e]=v,bro[e]=head[u],cap[e]=c,val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int c,int w){
		ae(u,v,c,w),ae(v,u,0,-w);
	}
	struct state{
		int x,d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d>b.d;
		}
	};
	void dij(){
		mset(dt+1,127,n);
		priority_queue<state>q;
		q.push((state){s,dt[s]=0});
		pre[s]=-1;
		for(;!q.empty();){
			const int x=q.top().x,d=dis[x]+q.top().d;
			q.pop();
			if(dt[x]<dis[x]-d)continue;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]==0)continue;
				v=to[i];
				if(dt[v]<=d+val[i]-dis[v])continue;
				q.push((state){v,dt[v]=d+val[i]-dis[v]});
				pre[v]=i;
			}
		}
	}
	int aug(){
		int c=INF;
		for(int x=t;x!=s;x=to[pre[x]^1]){
			apmin(c,cap[pre[x]]);
		}
		for(int x=t;x!=s;x=to[pre[x]^1]){
			cap[pre[x]]-=c;
			cap[pre[x]^1]+=c;
		}
		for(int i=1;i<=n;i++){
			dis[i]=dt[i]<INF?dis[i]+dt[i]:INF;
		}
		return c;
	}
}
int n,m,k;
inline void Main(){
	G::init(n);
	for(int i=1;i<=m;i++){
		const int u=ni+1,v=ni+1,c=ni;
		G::add(u,v,c,1);
	}
	if(k==0){
		puts("0");
		return;
	}
	int ans=INF;
	lint flow=0,sum=0;
	for(;G::dij(),G::dt[G::t]<INF;){
		int d=G::dis[G::t]+G::dt[G::t],dt=G::aug();
		flow+=dt,sum+=(lint)d*dt;
		lint cur=(k+sum-1)/flow;
		if(cur<d){
			apmin(ans,d);
			break;
		}else{
			apmin(ans,cur);
		}
	}
	if(ans==INF){
		puts("No solution");
	}else{
		printf("%d\n",ans);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
#endif
	for(;scanf("%d%d%d",&n,&m,&k)!=EOF;Main());
	return 0;
}
