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
const int N=4010,M=200010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G{
	const int N=::N+::M,E=(N+::M*2)*2;
	int to[E],bro[E],head[N],e=0,s,t;
	lint cap[E];
	inline void init(int n){
		memset(head+1,-1,(n+1)<<2);
		s=n+1,t=n+2;
	}
	inline void ae(int u,int v,lint c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,lint c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N];
	inline void bfs(){
		memset(dis+1,127,t<<2);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	lint aug(int x,lint a){
		if(x==t)return a;
		lint r=a,d;
		for(int i=head[x],v;r&&~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(cap[i],r));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		if(r){
			dis[x]=INF;
		}
		return a-r;
	}
	inline lint dinic(){
		lint flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,LINF));
		return flow;
	}
}
int n,m;
int a[N],b[M];
struct Edge{
	int u,v;
}e[M];
inline lint check(int x){
	G::init(n+m);
	for(int i=1;i<=n;i++){
		G::add(i,G::t,(lint)a[i]*x);
	}
	lint sum=0;
	for(int i=1;i<=m;i++){
		sum+=b[i];
		G::add(G::s,i+n,b[i]);
		G::add(i+n,e[i].u,LINF);
		G::add(i+n,e[i].v,LINF);
	}
	sum-=G::dinic();
	return sum;
}
inline int Main(){
	n=ni,m=ni;
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=m;i++){
		e[i]=(Edge){ni,ni};
		r+=b[i]=ni;
	}
	while(l<r){
		int m=((l+r)>>1)+1;
		if(check(m)>0){//TODO
			l=m;
		}else{
			r=m-1;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gift.in","r",stdin);
	freopen("gift.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
