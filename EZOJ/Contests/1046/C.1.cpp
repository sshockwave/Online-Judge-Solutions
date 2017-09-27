#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <queue>
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
const int N=50,E=100;
bool vis[N];
int n,k;
namespace G{
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
	struct state{
		int x,d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d<b.d;
		}
	};
	priority_queue<state>q;
	int dis[N];
	inline void spfa(){
		memset(dis,127,sizeof(dis));
		for(int i=1;i<=n;i++){
			if(vis[i]){
				dis[i]=0;
				q.push((state){i,0});
			}
		}
		while(!q.empty()){
			int x=q.top().x;
			int d=q.top().d;
			q.pop();
			if(d>dis[x]){
				continue;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>dis[x]+val[i]){
					dis[v]=dis[x]+val[i];
					q.push((state){v,dis[v]});
				}
			}
		}
	}
}
int lst[N];
bool best[N];
inline int gen(){
	random_shuffle(lst+1,lst+n+1);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=k;i++){
		vis[lst[i]]=true;
	}
	G::spfa();
	int val=0;
	for(int i=1;i<=n;i++){
		if(G::dis[i]>val){
			val=G::dis[i];
		}
	}
	return val;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("defense1.in","r",stdin);
#endif
	srand(time(0));
	n=ni;
	int tot=ni;
	k=min(ni,n);
	G::init();
	while(tot--){
		int u=ni,v=ni;
		G::add(u,v,ni);
	}
	for(int i=1;i<=n;i++){
		lst[i]=i;
	}
	int ans=0x7f7f7f7f;
	while(true){
		int t=gen();
		if(t<ans){
			ans=t;
			cout<<"new best ans:"<<ans<<endl;
			memcpy(best,vis,sizeof(vis));
			FILE *file=fopen("defense1.out","w");
			fprintf(file,"%d\n",k);
			for(int i=1;i<=n;i++){
				if(vis[i]){
					fprintf(file,"%d\n",i);
				}
			}
			fclose(file);
		}
	}
	return 0;
}
