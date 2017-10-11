#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=100010,E=200010,logN=18,INF=0x7f7f7f7f;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
namespace T{
	int to[E],bro[E],val[E],head[N],e=0;
	int fa[N][logN],mx[N][logN],lgdep[N],dep[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(fa,0,sizeof(fa));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs(int x){
		for(int &j=lgdep[x]=0;(fa[x][j+1]=fa[fa[x][j]][j]);j++){
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
	inline int ask(int u,int v){
		int ans=-INF;
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		for(int j=lgdep[u];dep[u]!=dep[v];j--){
			if(dep[fa[u][j]]>=dep[v]){
				apmax(ans,mx[u][j]);
				u=fa[u][j];
			}
		}
		if(u==v){
			return ans;
		}
		for(int j=lgdep[u];j>=0;j--){
			if(fa[u][j]!=fa[v][j]){
				apmax(ans,max(mx[u][j],mx[v][j]));
				u=fa[u][j],v=fa[v][j];
			}
		}
		assert(fa[u][0]==fa[v][0]);
		apmax(ans,max(mx[u][0],mx[v][0]));
		return ans;
	}
}
struct Edge{
	int u,v,w;
}e[E];
bool vis[E];
int lst[E];
inline bool lcmp(int a,int b){
	return e[a].w<e[b].w;
}
int fa[N];
int root(int x){
	return fa[x]?(fa[x]=root(fa[x])):x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("pipe.in","r",stdin);
	freopen("pipe.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=tot;i++){
		e[i]=(Edge){ni,ni,ni};
		lst[i]=i;
	}
	T::init();
	memset(vis,0,sizeof(vis));
	memset(fa,0,sizeof(fa));
	lint sum=0;
	sort(lst+1,lst+tot+1,lcmp);
	for(int i=1;i<=tot;i++){
		int u=e[lst[i]].u,v=e[lst[i]].v;
		if(root(u)!=root(v)){
			vis[lst[i]]=true;
			sum+=e[lst[i]].w;
			fa[root(u)]=root(v);
			T::add(u,v,e[lst[i]].w);
		}
	}
	T::dep[1]=1;
	T::dfs(1);
	for(int i=1;i<=tot;i++){
		if(vis[i]){
			printf("%lld\n",sum);
		}else{
			printf("%lld\n",sum-T::ask(e[i].u,e[i].v)+e[i].w);
		}
	}
	return 0;
}
