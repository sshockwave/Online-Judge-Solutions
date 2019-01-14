#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G{
	const int N=::N<<1,E=(N+N+N)<<1;
	int to[E],bro[E],head[N],e=0,n=0,s,t;
	lint cap[E];
	inline int nn(){
		++n;
		head[n]=-1;
		return n;
	}
	inline void init(){
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add_round(int u,int v,int c){
		ae(u,v,c),ae(v,u,c);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		mset(dis+1,0x7f,n);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		for(;qh<qt;){
			const int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	lint aug(int x,lint a){
		if(x==t||a==0)return a;
		lint r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min<lint>(r,cap[i]));
				r-=d,cap[i]-=d,cap[i^1]+=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	lint dinic(){
		lint flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,LINF));
		return flow;
	}
}
int nd[N],pval[N];
int cov[N];
int evis[G::N],tim=0;
inline void adde(int x,int l,int r){
	++tim;
	for(int i=l+1;i<=r;i++){
		if(evis[nd[i]]<tim){
			evis[nd[i]]=tim;
			G::ae(x,nd[i],pval[i]);
			G::ae(nd[i],x,INF);
		}
	}
}
inline void addcov(int x,int l,int r){
	for(int i=l;i<=r;i++){
		if(cov[i]==0){
			cov[i]=x;
		}
	}
}
struct Intv{
	int l,r,w,nd;
}intv[N];
bool cmp_len(const Intv &a,const Intv &b){
	return a.r-a.l<b.r-b.l;
}
int pnd[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("underground.in","r",stdin);
	freopen("underground.out","w",stdout);
#endif
	G::init();
	const int n=ni,m=ni,k=ni;
	for(int i=1;i<=m;i++){
		pnd[i]=G::nn();
		intv[i]=(Intv){ni,ni,ni,pnd[i]};
	}
	sort(intv+1,intv+m+1,cmp_len);
	for(int i=2;i<=n;i++){
		nd[i]=G::t,pval[i]=INF;
	}
	memset(evis,0,sizeof(evis));
	for(int i=1;i<=m;i++){
		int x=intv[i].nd;
		adde(x,intv[i].l,intv[i].r);
		addcov(x,intv[i].l+1,intv[i].r-1);
		for(int j=intv[i].l+1;j<=intv[i].r;j++){
			nd[j]=x,pval[j]=intv[i].w;
		}
	}
	adde(G::s,1,n);
	addcov(G::s,1,n);
	for(int i=1;i<=k;i++){
		G::add_round(cov[ni],cov[ni],INF);
	}
	lint ans=G::dinic();
	if(ans>INF){
		ans=-1;
	}
	printf("%lld\n",ans);
	return 0;
}
