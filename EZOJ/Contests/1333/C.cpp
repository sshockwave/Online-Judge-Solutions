#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
template<class T>inline T cabs(T x){
	return x>0?x:-x;
}
const int N=500010,INF=0x7f7f7f7f;
int pval[N];
namespace H{
	int lson[N],rson[N],dis[N];
	inline void init(){
		memset(lson,0,sizeof(lson));
		memset(rson,0,sizeof(rson));
		memset(dis,0,sizeof(dis));
	}
	inline int merge(int u,int v){
		if(u==0||v==0){
			return u|v;
		}
		if(pval[u]<pval[v]){
			swap(u,v);
		}
		rson[u]=merge(rson[u],v);
		if(dis[lson[u]]<dis[rson[u]]){
			swap(lson[u],rson[u]);
		}
		dis[u]=dis[rson[u]]+1;
		return u;
	}
	inline int del(int x){
		return merge(lson[x],rson[x]);
	}
}
int rt[N];
namespace H2{
	int lson[N],rson[N],dis[N];
	inline void init(){
		memset(lson,0,sizeof(lson));
		memset(rson,0,sizeof(rson));
		memset(dis,0,sizeof(dis));
	}
	inline int merge(int u,int v){
		if(u==0||v==0){
			return u|v;
		}
		if(pval[rt[u]]<pval[rt[v]]){
			swap(u,v);
		}
		rson[u]=merge(rson[u],v);
		if(dis[lson[u]]<dis[rson[u]]){
			swap(lson[u],rson[u]);
		}
		dis[u]=dis[rson[u]]+1;
		return u;
	}
	inline int del(int x){
		return merge(lson[x],rson[x]);
	}
}
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int size[N],con[N];
	struct xcmp{
		inline bool operator () (int a,int b){
			return pval[rt[a]]<pval[rt[b]];
		}
	};
	bool vis[N];
	int q[N];
	void dfs(int x,int d){
		pval[x]+=d;
		size[x]=1;
		rt[x]=x;
		q[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i],d+1);
			size[x]+=size[v];
			q[x]=H2::merge(q[x],v);
		}
		con[x]=1;
		while(q[x]&&pval[rt[q[x]]]>pval[rt[x]]){
			int y=q[x];
			q[x]=H2::del(q[x]);
			rt[x]=H::merge(rt[x],rt[y]);
			if((con[x]&1)&&(con[y]&1)){
				rt[x]=H::del(rt[x]);
			}
			con[x]+=con[y];
			vis[y]=false;
			q[x]=H2::merge(q[x],q[y]);
		}
		vis[x]=true;
	}
	lint dfs2(int x,int w){
		if(vis[x]){
			w=pval[rt[x]];
		}
		lint ans=cabs(pval[x]-w);
		for(int i=head[x];~i;i=bro[i]){
			ans+=dfs2(to[i],w);
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("asc.in","r",stdin);
	freopen("asc.out","w",stdout);
#endif
	int n=ni;
	pval[1]=ni;
	T::init();
	for(int i=2;i<=n;i++){
		T::ae(ni,i),pval[i]=ni;
	}
	memset(T::vis,0,sizeof(T::vis));
	T::dfs(1,0);
	printf("%lld\n",T::dfs2(1,0));
	return 0;
}
