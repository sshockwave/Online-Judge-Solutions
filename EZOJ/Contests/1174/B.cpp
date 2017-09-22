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
const int N=40010;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dfn[N],dfe[N],tim=0;
	void dfs(int x,int fa){
		dfn[x]=++tim;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
			}
		}
		dfe[x]=tim;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("query.in","r",stdin);
	freopen("query.out","w",stdout);
#endif
	int n=ni,rt;
	T::init();
	for(int i=1;i<=n;i++){
		int u=ni,v=ni;
		if(v==-1){
			rt=u;
		}else{
			T::add(u,v);
		}
	}
	T::dfs(rt,-1);
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		if(T::dfn[u]<=T::dfn[v]&&T::dfe[v]<=T::dfe[u]){
			puts("1");
		}else if(T::dfn[v]<=T::dfn[u]&&T::dfe[u]<=T::dfe[v]){
			puts("2");
		}else{
			puts("0");
		}
	}
	return 0;
}
