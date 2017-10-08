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
	int dfn[N],low[N],tim=0;
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
	inline int nn(){
		return ++n;
	}
	int esize[N],anc[N];
	bool bridge[E];
	void dfs(int x){
		dfn[x]=low[x]=++tim;
		esize[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			esize[x]++;
			if(dfn[v=to[i]]){
				apmin(low[x],low[v]);
			}else{
				anc[v]=anc[x];
				dfs(v);
				esize[x]+=esize[v];
				bridge[i]=bridge[i^1]=low[v]==dfn[x];
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
	int cnt=-1;
	for(int i=1;i<=G::n;i++){
		if(G::dfn[i]==0){
			G::anc[i]=i;
			G::dfs(i);
			if((G::esize[i]>>1)&1){
				cnt++;
			}
		}
	}
	if(cnt){
		for(int i=0;i<G::e;i+=2){
			puts("NG");
		}
	}else{
		for(int i=0;i<G::e;i+=2){
			int all=G::esize[G::anc[G::to[i]]]>>1;
			int part=(min(G::esize[G::to[i]],G::esize[G::to[i|1]])-1)>>1;
			puts(G::bridge[i]&&(all&1)&&(part&1)==0?"OK":"NG");
		}
	}
	return 0;
}
