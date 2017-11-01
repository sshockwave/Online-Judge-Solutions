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
const int N=100010;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int f[N],g[N];
	void dfs(int x,int fa){
		f[x]=0;
		bool flag=false;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				f[x]+=g[v];
				flag|=f[v]==g[v];
			}
		}
		g[x]=f[x]+flag;
	}
}
inline int Main(){
	int n=ni,k=ni;
	T::init(n);
	for(int i=1;i<n;T::add(ni,++i));
	T::dfs(1,0);
	if(k<=(T::g[1]<<1)){
		return (k+1)>>1;
	}
	return k-T::g[1];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
