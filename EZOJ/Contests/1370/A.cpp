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
const int N=1010;
namespace G{
	const int E=10010*2;
	int to[E],bro[E],head[N],e=0;
	bool vis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	inline void dfs(int x,bool d){//d:x is vis
		if(d){
			printf("%d ",x);
		}
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			assert(bro[i]!=i);
			if(!vis[v=to[i]]){
				dfs(v,!d);
			}
		}
		if(!d){
			printf("%d ",x);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("npc.in","r",stdin);
	freopen("npc.out","w",stdout);
#endif
	int n=ni,m=ni,p=ni;
	assert(p>=3);
	G::init();
	for(int i=1;i<=m;i++){
		G::add(ni,ni);
	}
	G::dfs(1,1);
	putchar('\n');
	return 0;
}
