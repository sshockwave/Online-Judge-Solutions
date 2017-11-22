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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=200010,INF=0x7f7f7f7f;
int ans=0;
namespace T{
	const int E=N<<2;
	int to[E],bro[E],mhead[N],dhead[N],e=0;
	int fa[N],dep[N],dfn[N],dfe[N],tim=0;
	bool col[N];
	inline void init(){
		memset(mhead,-1,sizeof(mhead));
		memset(dhead,-1,sizeof(dhead));
	}
	inline void ae(int u,int v,int *head){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v,int *head){
		ae(u,v,head),ae(v,u,head);
	}
	void dfs1(int x){
		dfn[x]=++tim;
		for(int i=mhead[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs1(v);
			}
		}
		dfe[x]=tim;
	}
	inline bool cont(int u,int v){
		return dfn[u]<=dfn[v]&&dfe[u]>=dfe[v];
	}
	inline bool gcol(int u,int v){
		if(cont(u,v)){
			return dep[v]-dep[u]>2;
		}
		if(cont(v,u)){
			return dep[u]-dep[v]>2;
		}
		return fa[u]!=fa[v];
	}
	void dfs2(int x,int fa,int stp){
		if(dep[x]<=stp){
			return;
		}
		if(col[x]){
			throw -1;
		}
		apmax(ans,dep[x]);
		for(int i=dhead[x];~i;i=bro[i]){
			if(to[i]!=fa){
				dfs2(to[i],x,stp+1);
			}
		}
	}
}
int main(){
	int n=ni,drt=ni,rt=ni;
	T::init();
	for(int i=1;i<n;T::add(ni,ni,T::dhead),i++);
	for(int i=1;i<n;T::add(ni,ni,T::mhead),i++);
	T::dfs1(rt);
	for(int i=0,ti=T::e>>1;i<ti;i+=2){
		int u=T::to[i],v=T::to[i^1];
		if(T::gcol(u,v)){
			T::col[u]=T::col[v]=true;
		}
	}
	try{
		T::dfs2(drt,0,0);
		printf("%d\n",ans<<1);
	}catch(int ans){
		printf("%d\n",ans);
	}
	return 0;
}
