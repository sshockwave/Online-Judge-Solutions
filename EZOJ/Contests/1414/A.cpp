#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=100010;
namespace G{
	const int E=300010;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	struct State{
		int x;
		lint d;
		inline friend bool operator < (const State &a,const State &b){
			return a.d>b.d;
		}
	};
	lint dis[N];
	void dij(int s){
		priority_queue<State>q;
		memset(dis,127,sizeof(dis));
		q.push((State){s,dis[s]=0});
		while(!q.empty()){
			int x=q.top().x;
			lint d=q.top().d;
			q.pop();
			if(d>dis[x])continue;
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>d+val[i]){
					q.push((State){v,dis[v]=d+val[i]});
				}
			}
		}
	}
}
lint inval[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("create.in","r",stdin);
	freopen("create.out","w",stdout);
#endif
	int n=ni;
	G::init();
	for(int i=1;i<=n;i++){
		for(int tot=ni;tot--;){
			int w=ni;
			G::ae(i,ni,w);
		}
	}
	int st=ni;
	G::dij(st);
	memset(inval,127,sizeof(inval));
	inval[st]=0;
	for(int x=1;x<=n;x++){
		using namespace G;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dis[v=to[i]]==dis[x]+val[i]){
				apmin(inval[v],val[i]);
			}
		}
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=inval[i];
	}
	printf("%lld\n",ans);
	return 0;
}
