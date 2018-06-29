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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G{
	const int E=200010;
	int to[E],bro[E],fir[E],gap[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v,int f,int g){
		to[e]=v,bro[e]=head[u],fir[e]=f,gap[e]=g,head[u]=e++;
	}
	struct State{
		int x;
		lint d;
		inline friend bool operator < (const State &a,const State &b){
			return a.d>b.d;
		}
	};
	lint dis[N];
	void dij(const int n){
		mset(dis+1,127,n);
		priority_queue<State>q;
		q.push((State){1,dis[1]=0});
		for(;!q.empty();){
			const int x=q.top().x;
			const lint d=q.top().d;
			q.pop();
			if(d>dis[x])continue;
			for(int i=head[x],v;~i;i=bro[i]){
				const lint td=d+(fir[i]+gap[i]-d%gap[i])%gap[i]+1;
				if(td<dis[v=to[i]]){
					q.push((State){v,dis[v]=td});
				}
			}
		}
	}
}
int pos[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("bus.in","r",stdin);
	freopen("bus.out","w",stdout);
#endif
	const int n=ni;
	G::init(n);
	for(int tot=ni;tot--;){
		const int cnt=ni;
		for(int i=0;i<cnt;i++){
			pos[i]=ni;
		}
		for(int i=0;i<cnt;i++){
			G::ae(pos[i],pos[i+1<cnt?i+1:0],i,cnt);
		}
	}
	G::dij(n);
	for(int i=2;i<=n;i++){
		printf("%lld ",G::dis[i]<LINF?G::dis[i]:-1ll);
	}
	putchar('\n');
	return 0;
}
