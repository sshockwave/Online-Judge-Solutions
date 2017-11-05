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
const int N=20,INF=0x7f7f7f7f;
int n;
namespace G{
	const int E=N*N;
	int to[E],bro[E],val[E],head[N],e=0;
	bool mark[E];
	bool vis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(mark,0,sizeof(mark));
		memset(vis,0,sizeof(vis));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int cnt;
	void dfs(int x){
		if(x==n){
			cnt++;
			return;
		}
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!mark[i]&&!vis[v=to[i]]){
				dfs(v);
				if(cnt>1){
					vis[x]=false;
					return;
				}
			}
		}
		vis[x]=false;
	}
}
int ans=INF;
void dfs(int x,int cur){
	if(cur>=ans){
		return;
	}
	if(x>G::e){
		G::cnt=0;
		G::dfs(1);
		if(G::cnt==1){
			ans=cur;
		}
		return;
	}
	G::mark[x]=G::mark[x^1]=false;
	dfs(x+2,cur);
	G::mark[x]=G::mark[x^1]=true;
	dfs(x+2,cur+G::val[x]);
	G::mark[x]=G::mark[x^1]=false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("stable.in","r",stdin);
	freopen("stable.out","w",stdout);
#endif
	n=ni;
	G::init();
	for(int tot=ni,u,v;tot--;u=ni,v=ni,G::add(u,v,ni));
	dfs(0,0);
	printf("%d\n",ans);
	return 0;
}
