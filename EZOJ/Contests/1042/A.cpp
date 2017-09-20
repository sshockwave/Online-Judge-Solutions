#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=100010,E=200010,logN=20;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	lint val[E];
	int fa[N][logN],dep[N],ldep[N];
	lint mx[N][logN];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,lint w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,lint w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs(int x){
		for(int &j=ldep[x]=0;(fa[x][j+1]=fa[fa[x][j]][j]);j++){
			mx[x][j+1]=max(mx[x][j],mx[fa[x][j]][j]);
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x][0]){
				fa[v][0]=x;
				mx[v][0]=val[i];
				dep[v]=dep[x]+1;
				dfs(v);
			}
		}
	}
	lint ask(int u,int v){
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		int ans=0;
		for(int j=ldep[u];j>=0&&dep[u]>dep[v];j--){
			if(dep[fa[u][j]]>=dep[v]){
				apmax(ans,mx[u][j]);
				u=fa[u][j];
			}
		}
		assert(dep[u]==dep[v]);
		if(u==v){
			return ans;
		}
		for(int j=max(ldep[u],ldep[v]);j>=0;j--){
			if(fa[u][j]!=fa[v][j]){
				apmax(ans,max(mx[u][j],mx[v][j]));
				u=fa[u][j];
				v=fa[v][j];
			}
		}
		apmax(ans,max(mx[u][0],mx[v][0]));
		assert(fa[u][0]==fa[v][0]);
		return ans;
	}
}
bool good[N];
namespace G{
	const int E=200010*2;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	struct state{
		int x;
		lint d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d>b.d;
		}
	};
	priority_queue<state>q;
	lint dis[N];
	int fr[N];
	inline void dij(int n){
		memset(dis,127,sizeof(dis));
		for(int i=1;i<=n;i++){
			if(good[i]){
				dis[i]=0,fr[i]=i,q.push((state){i,0});
			}
		}
		while(!q.empty()){
			int x=q.top().x;
			lint d=q.top().d;
			q.pop();
			if(d>dis[x]){
				continue;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>d+val[i]){
					dis[v]=d+val[i];
					fr[v]=fr[x];
					q.push((state){v,dis[v]});
				}
			}
		}
	}
	inline lint eval(int e){
		return dis[to[e]]+dis[to[e^1]]+val[e];
	}
	int lst[E>>1],ls=0;
	inline bool lscmp(int a,int b){
		return eval(a)<eval(b);
	}
	int fa[N];
	int root(int x){
		if(fa[x]==0){
			return x;
		}
		return fa[x]=root(fa[x]);
	}
	inline void kruskal(){
		for(int i=0;i<e;i+=2){
			if(fr[to[i]]!=fr[to[i^1]]){
				lst[ls++]=i;
			}
		}
		sort(lst,lst+ls,lscmp);
		memset(fa,0,sizeof(fa));
		for(int i=0;i<ls;i++){
			int e=lst[i],u=fr[to[e]],v=fr[to[e^1]];
			if(root(u)!=root(v)){
				T::add(u,v,eval(e));
				fa[root(u)]=root(v);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
#endif
	int n=ni,tot=ni,rt;
	{
		static char s[N];
		scanf("%s",s+1);
		for(int i=1;i<=n;i++){
			good[i]=s[i]=='1';
			if(good[i]){
				rt=i;
			}
		}
	}
	T::init(),G::init();
	while(tot--){
		int u=ni,v=ni;
		G::add(u,v,ni);
	}
	T::fa[rt][0]=0,T::dep[rt]=1;
	G::dij(n),G::kruskal(),T::dfs(rt);
	for(tot=ni;tot--;){
		printf("%lld\n",T::ask(ni,ni));
	}
	return 0;
}
