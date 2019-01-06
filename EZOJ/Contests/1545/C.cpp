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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1010,INF=0x7f7f7f7f;
int dis[N][N];
namespace T{
	const int E=::N<<1;
	int to[E],val[E],bro[E],head[N],e;
	int dfn[N],tim;
	int len[N];
	inline void init(int n){
		mset(head+1,-1,n),e=0;
		tim=0;
		len[1]=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int idx[N];
	void dfs(int x,int fa){
		dfn[x]=++tim;
		idx[dfn[x]]=x;
		int lasttim=dfn[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			len[v]=len[x]+val[i];
			dfs(v,x);
			for(int a=dfn[x];a<=lasttim;a++){
				for(int b=dfn[v];b<=tim;b++){
					int u=idx[a],v=idx[b];
					apmin(dis[u][v],len[u]+len[v]-(len[x]<<1));
					apmin(dis[v][u],len[u]+len[v]-(len[x]<<1));
				}
			}
			lasttim=tim;
		}
	}
}
inline lint Main(){
	const int n=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=INF;
		}
	}
	T::init(n);
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v,ni);
	}
	T::dfs(1,0);
	T::init(n);
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v,ni);
	}
	T::dfs(1,0);
	lint ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ans+=dis[i][j];
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%lld\n",Main());
	}
	return 0;
}
