#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <vector>
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
const int N=200010;
int pval[N];
namespace G{
	const int E=400010*2;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	lint dis[N];
	bool vis[N];
	struct state{
		int x;
		lint d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d>b.d;
		}
	};
	inline void dij(int s,bool flag){
		memset(dis,127,sizeof(dis));
		memset(vis,0,sizeof(vis));
		dis[s]=0;
		priority_queue<state>q;
		q.push((state){s,0});
		while(!q.empty()){
			int x=q.top().x;
			q.pop();
			if(vis[x]){
				continue;
			}
			vis[x]=true;
			for(int i=head[x],v;~i;i=bro[i]){
				if((i&1)==flag){
					v=to[i];
					lint nd=dis[x]+val[i];
					if(nd<dis[v]){
						assert(!vis[v]);
						dis[v]=nd;
						q.push((state){v,nd});
					}
				}
			}
		}
	}
	void dfs(int x,int t){
		printf("%d ",pval[x]);
		if(x==t){
			return;
		}
		int nxt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((i&1)==0&&dis[v=to[i]]==dis[x]-val[i]&&(nxt==0||pval[v]<pval[nxt])){
				nxt=v;
			}
		}
		dfs(nxt,t);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("journalist.in","r",stdin);
	freopen("journalist.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	G::init();
	for(int u,v;tot--;u=ni,v=ni,G::add(u,v,ni));
	G::dij(n,1);
	printf("%lld\n",G::dis[1]);
	G::dfs(1,n);
	putchar('\n');
	return 0;
}
