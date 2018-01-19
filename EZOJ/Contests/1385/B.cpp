#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <algorithm>
#include <map>
#include <queue>
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
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G{
	const int N=100010*2*2,E=100010*2+N*2;//TODO
	int to[E],bro[E],val[E],head[N],e=0;
	int n=0;
	int tag[N],tim=0;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(tag,0,sizeof(tag));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	lint dis[N];
	struct state{
		int x;
		lint d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d>b.d;
		}
	};
	inline lint dij(int s,int t){
		priority_queue<state>q;
		tim++;
		tag[s]=tim,q.push((state){s,dis[s]=0});
		while(!q.empty()){
			int x=q.top().x;
			lint d=q.top().d;
			if(x==t)return d;
			q.pop();
			if(d>dis[x])continue;
			for(int i=head[x],v;~i;i=bro[i]){
				if(tag[v=to[i]]<tim){
					tag[v]=tim,dis[v]=LINF;
				}
				if(dis[v]>dis[x]+val[i]){
					q.push((state){v,dis[v]=dis[x]+val[i]});
				}
			}
		}
		return -1;
	}
}
namespace T{
	const int N=300010,E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N],dfn[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		fa[1]=0;
		son[0]=0;
		size[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		dep[x]=dep[fa[x]]+1;
		son[x]=0;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	void dfs2(int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dfn[x]=++tim;
		if(son[x]){
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					dfs2(v);
				}
			}
		}
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline bool dfncmp(int a,int b){
		return dfn[a]<dfn[b];
	}
	int gid[N];
	int stk[N],ss;
	inline void pushstk(int x){
		for(;;){
			if(ss==0){
				stk[ss++]=x;
				break;
			}
			int v=stk[ss-1];
			if(v==x)return;
			if(dep[v]>=dep[x]){
				ss--;
				if(ss==0||dep[stk[ss-1]]<dep[x]){
					stk[ss++]=x;
				}
				int u=stk[ss-1];
				assert(dep[u]<dep[v]);
				G::add(gid[u],gid[v],dep[v]-dep[u]);
			}else{
				stk[ss++]=x;
				break;
			}
		}
	}
	inline void finalize(){
		for(;ss>1;ss--){
			int u=stk[ss-2],v=stk[ss-1];
			assert(dep[u]<dep[v]);
			G::add(gid[u],gid[v],dep[v]-dep[u]);
		}
	}
}
typedef map<int,int>mp;
const int N=100010,L=200010,Q=13;
mp nodes[L];
int mxlev=0;
inline int gid(int lev,int x){
	apmax(mxlev,lev);
	mp::iterator it=nodes[lev].find(x);
	if(it==nodes[lev].end())return nodes[lev][x]=G::nn();
	else return it->second;
}
struct Query{
	int x1,lev1,x2,lev2;
}q[Q];
int lst[N],lst2[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("m.in","r",stdin);
	freopen("m.out","w",stdout);
#endif
	int n=ni,tot1=ni,tot2=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	G::init();
	while(tot1--){
		int x1=ni,lev1=ni,x2=ni,lev2=ni;
		G::add(gid(lev1,x1),gid(lev2,x2),1);
	}
	for(int i=1;i<=tot2;i++){
		q[i]=(Query){ni,ni,ni,ni};
		gid(q[i].lev1,q[i].x1);
		gid(q[i].lev2,q[i].x2);
	}
	for(int i=1;i<=mxlev;i++){
		mp &m=nodes[i];
		if(m.empty())continue;
		int ls=0;
		for(mp::iterator it=m.begin(),ti=m.end();it!=ti;it++){
			lst[++ls]=it->first;
			T::gid[it->first]=it->second;
		}
		sort(lst+1,lst+ls+1,T::dfncmp);
		T::ss=0;
		for(int j=1;j<ls;j++){
			T::pushstk(lst[j]);
			int w=T::lca(lst[j],lst[j+1]);
			T::gid[w]=gid(i,w),T::pushstk(w);
		}
		T::pushstk(lst[ls]);
		T::finalize();
	}
	for(int i=1;i<=tot2;i++){
		lint ans=G::dij(gid(q[i].lev1,q[i].x1),gid(q[i].lev2,q[i].x2));
		if(ans==-1){
			puts("impossible");
		}else{
			printf("%lld\n",ans);
		}
	}
	return 0;
}
