#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=510,E=1e5+(500<<1)+10,INF=0x7f7f7f7f;
namespace G{
	const int E=(::N<<1)+(::E<<1);
	int to[E],bro[E],cap[E],head[N],e,n,s,t;
	inline int nn(){
		++n;
		head[n]=-1;
		return n;
	}
	inline void init(){
		n=0,e=0;
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		mset(dis+1,0x7f,n);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		for(;qh<qt;){
			const int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+1){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t||a==0)return a;
		int r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(r,cap[i]));
				r-=d,cap[i]-=d,cap[i^1]+=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,INF));
		return flow;
	}
}
struct Edge{
	int u,v;
};
int pval[N],tval[N];
void solve(int l,int r,const vector<int>&lst,const vector<Edge>&edg){
	if(lst.empty())return;
	if(l==r){
		for(vector<int>::const_iterator it=lst.begin(),ti=lst.end();it!=ti;++it){
			tval[*it]=l;
		}
		return;
	}
	G::init();
	static int nd[N];
	const int m=(l+r)>>1;
	for(vector<int>::const_iterator it=lst.begin(),ti=lst.end();it!=ti;++it){
		nd[*it]=G::nn();
		if(pval[*it]<=m){
			G::add(G::s,nd[*it],1);
		}else{
			G::add(nd[*it],G::t,1);
		}
	}
	for(vector<Edge>::const_iterator it=edg.begin(),ti=edg.end();it!=ti;++it){
		G::add(nd[it->u],nd[it->v],INF);
	}
	G::dinic();
	vector<int>lst1,lst2;
	for(vector<int>::const_iterator it=lst.begin(),ti=lst.end();it!=ti;++it){
		(G::dis[nd[*it]]<INF?lst1:lst2).push_back(*it);
	}
	vector<Edge>edg1,edg2;
	for(vector<Edge>::const_iterator it=edg.begin(),ti=edg.end();it!=ti;++it){
		bool mu=G::dis[nd[it->u]]<INF,mv=G::dis[nd[it->v]]<INF;
		if(mu&&mv){
			edg1.push_back(*it);
		}else if(!mu&&!mv){
			edg2.push_back(*it);
		}
	}
	solve(l,m,lst1,edg1);
	solve(m+1,r,lst2,edg2);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("balance.in","r",stdin);
	freopen("balance.out","w",stdout);
#endif
	const int n=ni,m1=ni,m2=ni;
	int mx=-INF,mn=INF;
	vector<int>lst;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
		lst.push_back(i);
		apmax(mx,pval[i]);
		apmin(mn,pval[i]);
	}
	vector<Edge>edg;
	for(int i=1;i<=m1;i++){
		const int u=ni,v=ni;
		edg.push_back((Edge){u,v});
		edg.push_back((Edge){v,u});
	}
	for(int i=1;i<=m2;i++){
		const int u=ni,v=ni;
		edg.push_back((Edge){v,u});
	}
	solve(mn,mx,lst,edg);
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=cabs(pval[i]-tval[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
