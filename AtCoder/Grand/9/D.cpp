#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
const int N=100010;
inline uint lowbit(uint x){
	return x&-x;
}
inline uint highbit(uint x){
	for(;x!=(x&-x);x^=x&-x);
	return x;
}
namespace T{
	const int E=N<<1;
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
	uint dfs(int x,int fa){
		uint ans=0,hb=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				uint cur=dfs(v,x);
				apmax(hb,highbit(cur&ans)<<1);
				ans|=cur;
			}
		}
		for(;hb&ans;hb<<=1);
		return hb|(ans&~(hb-1));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("uninity.in","r",stdin);
	freopen("uninity.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	uint tmp=T::dfs(1,0);
	int ans=0;
	for(;tmp>1;tmp>>=1,ans++);
	printf("%d\n",ans);
	return 0;
}
