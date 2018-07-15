#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <queue>
using namespace std;
typedef double db;
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=20010,E=20010;
const int INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G1{
	const int E=::E<<1;
	int to[E],bro[E],head[N],e=0;
	bool vis[N],vis_e[E];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(vis+1,0,n);
	}
	inline void ae(int u,int v){
		vis_e[e]=false,to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs(int x){
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			vis_e[i]=true;
			if(!vis[v=to[i]]){
				dfs(v);
			}
		}
	}
}
const lint ratio=1000000000;
namespace G2{
	const int E=(::N+::E)<<1;
	int to[E],bro[E],cap[E],head[N],e=0,n,s,t;
	lint val[E];
	inline void init(int _n){
		mset(head+1,-1,_n+2);
		s=_n+1,t=_n+2,n=t;
	}
	inline void ae(int u,int v,int c,lint w){
		to[e]=v,bro[e]=head[u],cap[e]=c,val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int c,lint w){
		ae(u,v,c,w),ae(v,u,0,-w);
	}
	lint dis[N];
	int pr_e[N];
	struct Node{
		int x;
		lint d;
		inline friend bool operator < (const Node &a,const Node &b){
			return a.d>b.d;
		}
	};
	inline void dij(){
		priority_queue<Node>q;
		mset(dis+1,127,n);
		q.push((Node){s,dis[s]=0}),pr_e[s]=-1;
		for(;!q.empty();){
			const int x=q.top().x;
			const lint d=q.top().d;
			q.pop();
			if(d>dis[x])continue;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					q.push((Node){v,dis[v]=dis[x]+val[i]}),pr_e[v]=i;
				}
			}
		}
	}
	int flow;
	lint cost;
	inline void mcmf(){
		flow=0,cost=0;
		for(;dij(),dis[t]<LINF;){
			int dt=INF;
			for(int i=pr_e[t];~i;i=pr_e[to[i^1]]){
				apmin(dt,cap[i]);
			}
			flow+=dt;
			cost+=dis[t]*dt;
			for(int i=pr_e[t];~i;i=pr_e[to[i^1]]){
				cap[i]-=dt,cap[i^1]+=dt;
			}
		}
	}
}
struct Pt{
#define Pt(x,y) ((Pt){x,y})
	int x,y;
	inline lint d2()const{return sqr<lint>(x)+sqr<lint>(y);}
	inline db len()const{return sqrtl(d2());}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
	inline friend lint dot(const Pt &a,const Pt &b){return (lint)a.x*b.x+(lint)a.y*b.y;}
}pt[N];
int deg[N],ind[N];
inline db trim(db x){
	return min<db>(1,max<db>(-1,x));
}
inline db trimang(db x){
	for(;x<0;x+=M_PI*2);
	for(;x>M_PI;x-=M_PI*2);
	return x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("white.in","r",stdin);
	freopen("white.out","w",stdout);
#endif
	const int n=ni;
	G1::init(n);
	G2::init(n);
	int tot=ni;
	for(int i=1;i<=n;i++){
		pt[i]=Pt(ni,ni);
		ind[i]=0;
	}
	db sum=0;
	mset(ind+1,0,n);
	mset(deg+1,0,n);
	for(;tot--;){
		int u=ni,v=ni;
		++deg[u],++deg[v];
		G1::add(u,v);
		if(crs(pt[u],pt[v])<0){
			swap(u,v);
		}
		//force v->u
		++ind[u],--ind[v];
		const db ang=acos(trim((db)dot(pt[u],pt[v])/(pt[u].len()*pt[v].len())));
		const db ang2=trimang(atan2(pt[v].y,pt[v].x)-atan2(pt[u].y,pt[u].x));
		assert(fabs(ang-ang2)<1e-6);
		sum+=ang;
		G2::add(u,v,1,ang*2*ratio);
	}
	{//check valid
		for(int i=1;i<=n;i++){
			if(deg[i]&1){
				puts("-1");
				return 0;
			}
		}
		G1::dfs(1);
		for(int i=0;i<G1::e;i++){
			if(!G1::vis_e[i]){
				puts("-1");
				return 0;
			}
		}
	}
	lint flowsum=0;
	for(int i=1;i<=n;i++){
		if(ind[i]>0){
			assert((ind[i]&1)==0);
			G2::add(G2::s,i,ind[i]>>1,0);
			flowsum+=ind[i]>>1;
		}else if(ind[i]<0){
			assert(((-ind[i])&1)==0);
			G2::add(i,G2::t,(-ind[i])>>1,0);
		}
	}
	G2::mcmf();
	assert(G2::flow==flowsum);
	sum-=(db)G2::cost/ratio;
	sum/=M_PI*2;
	printf("%d\n",int(round(sum)));
	return 0;
}
