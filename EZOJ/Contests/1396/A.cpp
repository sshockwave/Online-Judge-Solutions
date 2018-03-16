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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=260,Q=50010;
namespace G2{
	const int N=::N*::N*3,E=N+Q*20;
	int to[E],bro[E],head[N],e=0,n;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	int deg[N];
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++,deg[v]++;
	}
	int que[N],qh=0,qt=0;
	void topsort(){
		for(int i=2;i<=n;i++){
			if(deg[i]==0){
				que[qt++]=i;
			}
		}
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				deg[v=to[i]]--;
				if(deg[v]==0){
					que[qt++]=v;
				}
			}
		}
	}
}
namespace G{
	const int N=::N*::N*3,E=N+Q*20;
	int to[E],bro[E],head[N],e=0,n=1;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline int nn(){
		return ++n;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfn[N],low[N],tim=0;
	int stk[N],ss=0;
	int bln[N];
	bool instk[N];
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		instk[x]=true,stk[ss++]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				tarjan(v);
				apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],dfn[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--ss];
				bln[v]=x;
				instk[v]=false;
			}while(v!=x);
		}
	}
	bool ban[N];
	void work(){
		for(int i=2;i<=n;i++){
			if(dfn[i]==0){
				tarjan(i);
			}
		}
		G2::init();
		G2::n=n;
		memset(dfn,0,sizeof(dfn));
		for(int x=2;x<=n;x++){
			assert(bln[x]!=bln[x^1]);
			for(int i=head[x],v;~i;i=bro[i]){
				if(bln[v=to[i]]!=bln[x]){
					G2::ae(bln[v],bln[x]);
				}
			}
		}
		G2::topsort();
		for(int i=0;i<G2::qt;i++){
			using G2::que;
			int x=que[i];
			if(bln[x]!=x)continue;
			if(ban[x])continue;
			ban[bln[x^1]]=true;
		}
	}
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int cnt[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
}
struct Query{
	int a,b,c;
}qry[Q];
int gnd[N][T::E];
int go(int p){
	int x=1;
	while(true){
		bool flag=true;
		using namespace T;
		for(int i=head[x];~i;i=bro[i]){
			if(!G::ban[G::bln[gnd[p][i]]]){
				flag=false;
				x=to[i];
			}
		}
		if(flag)break;
	}
	return x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("myth.in","r",stdin);
	freopen("myth.out","w",stdout);
#endif
	int n=ni,m=ni,q=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	for(int i=1;i<=q;i++){
		qry[i]=(Query){ni,ni,ni};
		T::cnt[qry[i].c]++;
	}
	if(q==0){
		for(int i=1;i<=n;i++){
			putchar('1'),putchar(' ');
		}
		putchar('\n');
		return 0;
	}
	G::init();
	for(int x=1;x<=m;x++){
		using namespace T;
		for(int i=0;i<e;i++){
			gnd[x][i]=G::nn();
		}
		for(int t=1;t<=n;t++){
			for(int i=head[t];~i;i=bro[i]){
				for(int j=head[t];~j;j=bro[j]){
					if(i==j)continue;
					G::ae(gnd[x][i],gnd[x][j^1]);
				}
			}
		}
	}
	for(int t=1;t<=q;t++){
		using namespace T;
		int a=qry[t].a,b=qry[t].b;
		for(int i=head[qry[t].c];~i;i=bro[i]){
			G::ae(gnd[a][i],gnd[b][i^1]);
			G::ae(gnd[b][i],gnd[a][i^1]);
		}
	}
	G::work();
	for(int i=1;i<=m;i++){
		printf("%d ",go(i));
	}
	putchar('\n');
	return 0;
}
