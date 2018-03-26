#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=2010,M=2010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G{
	const int E=::M<<1;
	int to[E],bro[E],head[N],e,n,s,t;
	lint cap[E];
	inline void init(int _n){
		e=0,n=_n,s=1,t=n;
		memset(head+1,-1,n*sizeof(head[0]));
	}
	inline void ae(int u,int v,lint c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,lint c){
		ae(u,v,c),ae(v,u,LINF);
	}
	int que[N];
	int rch[N];
	inline void bfsrch(int s,int eq,int flag){
		int qh=0,qt=0;
		rch[s]|=flag,que[qt++]=s;
		while(qh<qt){
			for(int i=head[que[qh++]],v;~i;i=bro[i]){
				if((i&1)==eq&&(rch[v=to[i]]&flag)==0){
					rch[v]|=flag,que[qt++]=v;
				}
			}
		}
	}
	inline void work(){
		memset(rch+1,0,n*sizeof(rch[0]));
		bfsrch(s,0,1),bfsrch(t,1,2);
		for(int i=0;i<e;i+=2){
			if(rch[to[i]]!=3||rch[to[i^1]]!=3){
				cap[i]=cap[i^1]=0;
			}
		}
	}
	int dis[N],cur[N];
	inline void bfs(){
		memset(dis+1,127,n*sizeof(dis[0]));
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	lint aug(int x,lint a){
		if(x==t||a==0)return a;
		lint r=a,d=0;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	inline lint dinic(){
		lint flow=0;
		for(;bfs(),dis[t]<INF;){
			lint d=aug(s,LINF);
			if(d==LINF)return -1;
			flow+=d;
		}
		return flow;
	}
}
inline lint Main(){
	int n=ni;
	G::init(n);
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G::add(u,v,ni);
	}
	G::work();
	return G::dinic();
}
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flow.in","r",stdin);
	freopen("flow.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
