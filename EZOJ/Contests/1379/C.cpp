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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=50010;
int a[N],b[N];
int ans=0;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	bool vis[N];
	inline void init(int n){
		e=0;
		memset(head+1,-1,n<<2);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs(int x,int fa,bool f){
		int t=a[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x,!f||b[v]==0);
				t-=a[v]*b[v];
			}
		}
		if(f){
			ans^=t;
		}
	}
}
inline bool Main(){
	int n=ni;
	T::init(n);
	ans=0;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b[i]=ni;
	}
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(1,0,1);
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("meal.in","r",stdin);
	freopen("meal.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		puts(Main()?"YES":"NO");
	}
	return 0;
}
