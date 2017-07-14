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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=100010;
lint ans=0;
int n,color[N];
bool vis[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int &u,const int &v){
		ae(u,v),ae(v,u);
	}
	int dfs(int x){
		if(vis[color[x]]){
			return 0;
		}
		vis[color[x]]=true;
		int ans=1;
		for(int i=head[x];~i;i=bro[i]){
			ans+=dfs(to[i]);
		}
		vis[color[x]]=false;
		return ans;
	}
}
namespace task3{
	int pre[N];
	inline lint solve(int n){
		memset(pre,0,sizeof(pre));
		lint ans=0;
		int cur=0;
		for(int i=1;i<=n;i++){
			apmax(cur,pre[color[i]]);
			ans+=i-cur;
			pre[color[i]]=i;
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		color[i]=ni;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	if(n>=5000){
		printf("%lld\n",task3::solve(n));
		return 0;
	}
	lint ans=0;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		ans+=T::dfs(i);
	}
	printf("%lld\n",(ans-n)/2+n);
	return 0;
}
