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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
namespace G{
	const int E=200010*2;
	int to[E],bro[E],head[N],e=0;
	int dfn[N],low[N],bln[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int stk[N],ss=0;
	void tarjan(int x,int e){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if(i^e^1){
				if(!dfn[v=to[i]]){
					tarjan(v,i);
				}
				apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do bln[v=stk[--ss]]=x;
			while(v!=x);
		}
	}
}
int deg[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
#endif
	int n=ni;
	G::init();
	for(int tot=ni;tot--;G::add(ni,ni));
	G::tarjan(1,-1);
	memset(deg,0,sizeof(deg));
	for(int i=0;i<G::e;i+=2){
		using namespace G;
		if(bln[to[i]]!=bln[to[i^1]]){
			deg[bln[to[i]]]++,deg[bln[to[i^1]]]++;
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=G::bln[i]==i&&deg[i]==1;
	}
	printf("%d\n",(cnt+1)>>1);
	return 0;
}
