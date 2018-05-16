#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=100010,INF=0x7f7f7f7f;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
}
int n;
int col[N];
inline int calc(){
	int ans=n&1;
	for(int i=0;i<T::e;i+=2){
		using namespace T;
		assert(col[to[i]]!=0);
		assert(col[to[i^1]]!=0);
		if(col[to[i]]==col[to[i^1]]){
			if(col[to[i]]==1){
				ans--;
			}else{
				ans++;
			}
		}
	}
	return ans;
}
int deg[N];
int lst[N];
inline bool lcmp(int a,int b){
	return deg[a]<deg[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	mset(deg+1,0,n);
	for(int i=0;i<T::e;i++){
		deg[T::to[i]]++;
	}
	for(int i=1;i<=n;i++){
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,lcmp);
	for(int i=1;i<=n;i++){
		col[lst[i]]=(i&1)?1:2;
	}
	printf("%d\n",calc());
	return 0;
}
