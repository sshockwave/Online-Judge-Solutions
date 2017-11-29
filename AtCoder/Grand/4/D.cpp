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
int mxdep,ans=0;
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e=0;
	int fa[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfs(int x){
		int dep=0;
		for(int i=head[x];~i;i=bro[i]){
			apmax(dep,dfs(to[i])+1);
		}
		if(x!=1&&dep==mxdep-1&&fa[x]!=1){
			return ans++,-1;
		}
		return dep;
	}
}
int main(){
	int n=ni;
	mxdep=ni;
	ans+=ni!=1;
	T::init();
	for(int i=2;i<=n;T::ae(T::fa[i]=ni,i),i++);
	T::dfs(1);
	printf("%d\n",ans);
	return 0;
}
