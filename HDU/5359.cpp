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
const int N=100010,INF=0x7f7f7f7f;
namespace G{
	const int E=::N<<1;
	int fr[E],to[E],bro[E],head[N],e;
	int bln[N];
	int dfn[N],low[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(instk,0,sizeof(instk));
		e=0;
	}
	inline void ae(int u,int v){
		fr[e]=u,to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
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
namespace G2{
	const int N=::N+G::E,E=G::E*2*2;
	int to[E],bro[E],head[N],e=0,n=0;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		e=0,n=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	bool flag;
	int dfn[N],lst[N],tim;
	bool hasson[N];
	int sdom[N],idom[N],fa[N];
	void dfs(int x){
		lst[dfn[x]=++tim]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if((i&1)==flag&&dfn[v=to[i]]==0){
				fa[v]=x,dfs(v);
			}
		}
	}
	typedef vector<int>vi;
	vi qry[N];
	int edom[N],efa[N];
	int eval(int x){
		if(efa[x]==x)return edom[x];
		eval(efa[x]);
		if(dfn[sdom[edom[efa[x]]]]<dfn[sdom[edom[x]]]){
			edom[x]=edom[efa[x]];
		}
		efa[x]=efa[efa[x]];
		return edom[x];
	}
	void tarjan(){
		memset(dfn+1,0,n*sizeof(dfn[0]));
		tim=0;
		for(int i=1;i<=n;i++){
			qry[i].clear();
			sdom[i]=idom[i]=edom[i]=efa[i]=i;
			hasson[i]=false;
			if(dfn[i]==0){
				fa[i]=0,dfs(i);
			}
		}
		assert(tim==n);
		for(int s=n;s>=1;s--){
			int x=lst[s];
			for(vi::iterator it=qry[x].begin();it!=qry[x].end();it++){
				idom[*it]=sdom[eval(*it)];
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if((i&1)==!flag&&dfn[sdom[eval(v=to[i])]]<dfn[sdom[x]]){
					sdom[x]=sdom[edom[v]];
				}
				if(fa[v=to[i]]==x){
					efa[v]=x;
				}
			}
			qry[sdom[x]].push_back(x);
		}
		for(int s=1;s<=n;s++){
			int x=lst[s];
			if(fa[x]==0){
				idom[x]=x;
			}else{
				idom[x]=idom[x]==sdom[x]?sdom[x]:idom[idom[x]];
				hasson[idom[x]]=true;
			}
		}
	}
}
int nd[G::E];
bool ans[G::E];
inline void Main(){
	int n=ni;
	G::init();
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G::ae(u,v);
	}
	for(int i=1;i<=n;i++){
		if(G::dfn[i]==0){
			G::tarjan(i);
		}
	}
	G2::init();
	G2::n=n;
	memset(nd,0,sizeof(nd));
	for(int i=0;i<G::e;i++){
		int u=G::fr[i],v=G::to[i];
		if(G::bln[u]==G::bln[v]){
			nd[i]=G2::nn();
			G2::add(u,nd[i]);
			G2::add(nd[i],v);
		}
	}
	memset(ans,0,sizeof(ans));
	{
		G2::tarjan();
		for(int i=0;i<G::e;i++){
			ans[i]|=nd[i]&&G2::hasson[nd[i]];
		}
		G2::flag^=1,G2::tarjan();
		for(int i=0;i<G::e;i++){
			ans[i]|=nd[i]&&G2::hasson[nd[i]];
		}
	}
	for(int i=0;i<G::e;i++){
		putchar('0'+(nd[i]&&ans[i]));
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("edge.in","r",stdin);
	freopen("edge.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
