#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=200010;
int fa[N];
bool vis[N];
int nodes[N],ns=0;
int mex1[N],mex2[N];
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void dfs(int x){
		set<int>s;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			s.insert(mex1[v]);
		}
		for(int &i=mex1[x]=0;s.find(i)!=s.end();i++);
		for(int &i=mex2[x]=mex1[x]+1;s.find(i)!=s.end();i++);
	}
}
inline int gval(int sg){
	for(int i=1;i<=ns;i++){
		sg=(sg!=mex1[nodes[i]]?mex1:mex2)[nodes[i]];
	}
	return sg;
}
inline bool Main(){
	int n=ni;
	T::init();
	for(int i=1;i<=n;i++){
		fa[i]=ni;
	}
	memset(vis,0,sizeof(vis));
	int x=1;
	for(;!vis[x];vis[x]=true,x=fa[x]);
	memset(vis,0,sizeof(vis));
	for(int p=x;nodes[++ns]=p,vis[p]=true,p=fa[p],p!=x;);
	T::init();
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			T::ae(fa[i],i);
		}
	}
	for(int i=1;i<=ns;i++){
		T::dfs(nodes[i]);
	}
	int val1=mex1[nodes[ns]],val2=mex2[nodes[ns]];
	return gval(val1)==val1||gval(val2)==val2;
}
int main(){
	puts(Main()?"POSSIBLE":"IMPOSSIBLE");
	return 0;
}
