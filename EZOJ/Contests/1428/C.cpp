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
int dfs(int x,int op,int beta){//op1:max op2:min
	if(x>n)return calc();
	int ans=op==1?-INF:INF;
	for(int i=1;i<=n;i++){
		if(col[i]==0){
			col[i]=op;
			int t=dfs(x+1,3-op,ans);
			col[i]=0;
			if(op==1){
				apmax(ans,t);
				if(ans>=beta)return ans;
			}else{
				apmin(ans,t);
				if(ans<=beta)return ans;
			}
		}
	}
	return ans;
}
int deg[N];
inline bool ischain(){
	mset(deg+1,0,n);
	for(int i=0;i<T::e;i++){
		using namespace T;
		int u=to[i];
		if(++deg[u]>2)return false;
	}
	return true;
}
namespace solve2{
	using namespace T;
	int que[N];
	inline int main(){
		int qh=0,qt=0;
		mset(deg+1,0,n);
		for(int i=0;i<T::e;i++){
			++deg[T::to[i]];
		}
		for(int i=1;i<=n;i++){
			if(deg[i]==1){
				que[qt++]=i;
			}
		}
		int op=1;
		while(qh<qt){
			int x=que[qh++];
			col[x]=op;
			for(int i=head[x],v;~i;i=bro[i]){
				if(--deg[v=to[i]]==1){
					que[qt++]=v;
				}
			}
		}
		return calc();
	}
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
	if(n==1){
		puts("1");
	}else if(n<=15){
		printf("%d\n",dfs(1,1,INF));
	}else if(ischain()){
		puts("0");
	}else{
		printf("%d\n",solve2::main());
	}
	return 0;
}
