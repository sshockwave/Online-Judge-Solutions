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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=10010;
namespace G{
	const int E=20000*2;
	int to[E],bro[E],head[N],e;
	int vis[N],tim=0;
	inline void init(int n){
		memset(head+1,-1,n*sizeof(head[0]));
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int f[N];
	bool col[N];
	bool instk[N];
	bool dfs(int x,int fa){
		vis[x]=tim;
		instk[x]=true;
		f[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			if(vis[v]<tim){
				col[v]=!col[x];
				if(!dfs(v,x))return false;
				f[x]+=f[v];
			}else{
				if(col[x]==col[v])return false;
				if(instk[v]){
					f[x]++;
				}else{
					f[x]--;
				}
			}
		}
		instk[x]=false;
		return f[x]<=2;
	}
}
inline bool Main(){
	int n=ni,m=ni;
	G::init(n);
	for(int i=1;i<=m;i++){
		G::add(ni,ni);
	}
	++G::tim;
	for(int i=1;i<=n;i++){
		if(G::vis[i]<G::tim&&!G::dfs(i,0))return false;
	}
	return true;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		puts(Main()?"YES":"NO");
	}
	return 0;
}
