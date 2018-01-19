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
enum DataType{
	undirected=1,
	directed=2
}type;
namespace G{
	const int E=200010*2;
	int to[E],bro[E],head[N],e=0;
	bool vis[N],ban[E];
	int nxt[E];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		memset(nxt,-1,sizeof(nxt));
		memset(ban,0,sizeof(ban));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs(int x){
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				dfs(v);
			}
		}
	}
	inline int append_loop(int e){
		int t=to[e];
		do{
			int x=to[e];
			int &i=head[x];
			for(;ban[i];i=bro[i]);
			assert(i!=-1);
			assert(nxt[i]==-1);
			assert(!ban[i]);
			nxt[i]=nxt[e],nxt[e]=i,e=i;
			if(type==undirected){
				ban[i^1]=true;
			}
			i=bro[i];
		}while(to[e]!=t);
		return e;
	}
	inline int euler_tour(){
		for(int &x=to[e]=1;head[x]==-1;x++);
		append_loop(e);
		for(int i=e;~i;){
			int x=to[i];
			for(int &j=head[x];(~j)&&ban[j];j=bro[j]);
			if(head[x]==-1){
				i=nxt[i];
			}else{
				append_loop(i);
			}
		}
		return nxt[e];
	}
}
int deg[N];
inline bool Main(){
	type=(DataType)ni;
	int n=ni,m=ni;
	G::init();
	memset(deg,0,sizeof(deg));
	for(int i=1;i<=m;i++){
		int u=ni,v=ni;
		if(type==undirected){
			G::add(u,v);
			deg[u]++,deg[v]++;
		}else{
			G::ae(u,v);
			deg[u]++,deg[v]--;
		}
	}
	for(int i=1;i<=n;i++){
		if(G::head[i]!=-1){
			G::dfs(i);
			break;
		}
	}
	for(int i=1;i<=n;i++){
		if(type==undirected&&(deg[i]&1))return false;
		if(type==directed&&deg[i])return false;
	}
	for(int i=0;i<G::e;i++){
		if(!G::vis[G::to[i]])return false;
	}
	puts("YES");
	if(m){
		for(int i=G::euler_tour();~i;i=G::nxt[i]){
			if(type==undirected){
				if(i&1){
					putchar('-');
				}
				printf("%d ",(i>>1)+1);
			}else{
				printf("%d ",i+1);
			}
		}
	}
	putchar('\n');
	return true;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);
#endif
	if(!Main()){
		puts("NO");
	}
	return 0;
}
