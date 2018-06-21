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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=1000010;
int ans[N];
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
	int g;
	int size[N];
	void gcen(int x,int fa,int n){
		size[x]=1;
		int bal=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				gcen(v,x,n);
				size[x]+=size[v];
				apmax(bal,size[v]);
			}
		}
		apmax(bal,n-size[x]);
		if((bal<<1)<=n){
			g=x;
		}
	}
	void dfs(int x,int fa,int n,int cnt,int sz){
		ans[x]=cnt+(((sz-size[x])<<1)>n);
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x,n,cnt,sz);
			}
		}
	}
}
int lst[N];
inline bool lcmp(int a,int b){
	return T::size[a]>T::size[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flea.in","r",stdin);
	freopen("flea.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	int g=(T::gcen(1,0,n),T::g);
	ans[g]=0;
	T::gcen(g,0,n);
	int ls=0;
	for(int i=T::head[g];~i;i=T::bro[i]){
		lst[++ls]=T::to[i];
	}
	sort(lst+1,lst+ls+1,lcmp);
	int rst=n,cnt=0;
	for(int i=1;i<=ls;i++){
		rst-=T::size[lst[i]],cnt++;
		if((rst<<1)<=n)break;
	}
	for(int i=1;i<=ls;i++){
		T::dfs(lst[i],g,n,cnt-1,rst+max(T::size[lst[i]],T::size[lst[cnt]]));
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
