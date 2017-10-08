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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=200010;
namespace G{
	const int N=400010,E=400010;
	int to[E],bro[E],head[N],e=0,n=0;
	bool vis[N];
	int dfn[N],low[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		memset(dfn,0,sizeof(dfn));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	inline int nn(){
		return ++n;
	}
	int esize[N];
	void dfs1(int x){//edge size
		esize[x]=0;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			esize[x]++;
			if(!vis[v=to[i]]){
				dfs1(v);
				esize[x]+=esize[v];
			}
		}
	}
	bool ok[E];
	void dfs2(int x,int eall){
		dfn[x]=low[x]=++tim;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				apmin(low[x],low[v]);
			}else{
				dfs2(v,eall);
				apmin(low[x],low[v]);
				ok[i]=ok[i^1]=low[v]==dfn[x]&&(((esize[v]-1)>>1)&1)==0&&(((eall-esize[v]-1)>>1)&1)==0;
			}
		}
	}
}
int nodex[N<<1],nodey[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("point.3.in","r",stdin);
	freopen("point.out","w",stdout);
#endif
	int n=2*ni+1;
	G::init();
	memset(nodex,0,sizeof(nodex));
	memset(nodey,0,sizeof(nodey));
	for(int i=1;i<=n;i++){
		int x=ni,y=ni;
		if(nodex[x]==0){
			nodex[x]=G::nn();
		}
		if(nodey[y]==0){
			nodey[y]=G::nn();
		}
		G::add(nodex[x],nodey[y]);
	}
	int pt=0;
	for(int i=1;i<=G::n;i++){
		if(!G::vis[i]){
			G::dfs1(i);
			if((G::esize[i]>>1)&1){
				pt=pt?-1:i;
			}
		}
	}
	memset(G::ok,0,sizeof(G::ok));
	if(pt==0){
		for(int i=1;i<=G::n;i++){
			if(G::dfn[i]==0){
				G::dfs2(i,G::esize[i]);
			}
		}
	}else if(pt>0){
		G::dfs2(pt,G::esize[pt]);
	}
	for(int i=0;i<G::e;i+=2){
		puts(G::ok[i]?"OK":"NG");
	}
	return 0;
}
