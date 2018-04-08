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
const int N=100010;
namespace G{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	bool ban[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int bln[N];
	int dfn[N],low[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	inline void reset(int n){
		tim=0,ss=0;
		for(int i=1;i<=n;i++){
			dfn[i]=0,instk[i]=false;
		}
	}
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(ban[i])continue;
			if(dfn[v=to[i]]==0){
				tarjan(v),apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],dfn[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--ss];
				instk[v]=false;
				bln[v]=x;
			}while(v!=x);
		}
	}
}
inline int work(int n){
	G::reset(n);
	for(int i=1;i<=n;i++){
		if(G::dfn[i]==0){
			G::tarjan(i);
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=G::bln[i]==i;
	}
	return cnt;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("edge.in","r",stdin);
	freopen("edge.out","w",stdout);
#endif
	int n=ni;
	G::init();
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G::ae(u,v);
	}
	int cnt=work(n);
	for(int i=0;i<G::e;i++){
		G::ban[i]=true;
		putchar('0'+(work(n)!=cnt));
		G::ban[i]=false;
	}
	putchar('\n');
	return 0;
}
