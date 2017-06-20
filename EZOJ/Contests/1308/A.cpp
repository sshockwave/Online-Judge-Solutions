#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010,E=N*2;
namespace G{
	int to[E],bro[E],head[N],e;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	inline void build(int n){
		memset(head+1,-1,n<<2);
		e=0;
		for(int i=1;i<n;i++){
			add(ni,ni);
		}
	}
}
bool vis[N];
namespace task0{
	int f[N][3][2],g[N][3];
	void dfs(int x){
		int deg=0;
		vis[x]=true;
		for(int i=G::head[x];~i;i=G::bro[i]){
			if(!vis[G::to[i]]){
				deg++;
			}
		}
		for(int i=G::head[x],v;~i;i=G::bro[i]){
			v=G::to[i];
			if(!vis[v]){
				dfs(v);
				//dp
				//todo
			}
		}
	}
	inline int work(){
		int n=ni;
		G::build(n);
		memset(vis+1,0,n);
		dfs(1);
		int ans=0;
		apmax(ans,f[1][1][0]);
		apmax(ans,f[1][1][1]);
		apmax(ans,f[1][2][0]);
		apmax(ans,f[1][2][1]);
		apmax(ans,g[1][0]);
		apmax(ans,g[1][1]);
		apmax(ans,g[1][2]);
		return ans;
	}
}
namespace task2{
	int fa[N],dep[N];
	inline void mark(int u,int v){
		while(u!=v){
			if(dep[u]<dep[v]){
				swap(u,v);
			}
			vis[u]=true;
			u=fa[u];
		}
		vis[u]=true;
	}
	void dfs(int x){
		for(int i=G::head[x],v;~i;i=G::bro[i]){
			v=G::to[i];
			if(v!=fa[x]){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs(v);
			}
		}
	}
	void mark(int x){
		vis[x]=true;
		for(int i=G::head[x],v;~i;i=G::bro[i]){
			v=G::to[i];
			if(!vis[v]){
				mark(v);
			}
		}
	}
	inline int work(){
		int n=ni,ps=ni,pt=ni,hs=ni,ht=ni;
		G::build(n);
		fa[1]=dep[1]=0;
		dfs(1);
		memset(vis+1,0,n);
		mark(ps,pt),mark(hs,ht);
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				cnt++;
				mark(i);
			}
		}
		return cnt;
	}
}
namespace task1{
	int f[N],g[N],h[N];
	void dfs(int x){
		vis[x]=true;
		int deg=0;
		for(int i=G::head[x],v;~i;i=G::bro[i]){
			v=G::to[i];
			if(!vis[v]){
				deg++;
			}
		}
		h[x]=1;
		f[x]=0;
		g[x]=deg;
		for(int i=G::head[x],v;~i;i=G::bro[i]){
			v=G::to[i];
			if(!vis[v]){
				dfs(v);
				apmax(h[x],max(f[v],g[v])+1);
				apmax(h[x],h[v]);
				apmax(g[x],f[x]-1+f[v]);
				apmax(f[x],f[v]+deg-1);
			}
		}
		apmax(f[x],deg);
	}
	inline int work(){
		int n=ni,ps=ni,pt=ni;
		G::build(n);
		task2::fa[1]=task2::dep[1]=0;
		task2::dfs(1);
		memset(vis+1,0,n);
		task2::mark(ps,pt);
		int ans=0;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				dfs(i);
				ans+=max(f[i],max(g[i],h[i]));
			}
		}
		return ans;
	}
}
int main(){
	for(int tot=ni,x=ni;tot--;){
		printf("%d\n",x==0?task0::work():(x==1?task1::work():task2::work()));
	}
}