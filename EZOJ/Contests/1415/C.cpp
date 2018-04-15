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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
namespace T{
	const int E=::N<<1;
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
	int vis[N],tim=0;
	int que[N],qh=0,qt=0;
	int dis[N];
	inline int bfs(){
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(vis[v=to[i]]<tim){
					vis[v]=tim;
					dis[v]=dis[x]+1;
					que[qt++]=v;
				}
			}
		}
		return dis[que[qt-1]];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("do.in","r",stdin);
	freopen("do.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	while(tot--){
		T::tim++;
		T::qh=0,T::qt=ni;
		for(int i=0;i<T::qt;i++){
			T::que[i]=ni;
			T::dis[T::que[i]]=0;
			T::vis[T::que[i]]=T::tim;
		}
		printf("%d\n",T::bfs());
	}
	return 0;
}
