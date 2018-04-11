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
const int N=200010;
int fa[N];
int grt(int x){
	return fa[x]!=x?fa[x]=grt(fa[x]):x;
}
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
	int f[N],size[N];
	bool alt[N];
	void dfs(int x,int fa){
		size[x]=1;
		alt[x]=false;
		f[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				size[x]+=size[v];
				f[x]+=f[v];
				alt[x]|=!alt[v];
			}
		}
		f[x]+=alt[x];
	}
}
int ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1;i<=n;i++){
		fa[i]=i,ans[i]=0;
	}
	for(int tot=ni;tot--;){
		if(ni){
			int u=ni,v=ni;
			T::add(u,v);
			u=grt(u),v=grt(v);
			fa[u]=v,ans[v]=(T::dfs(v,0),T::size[v]-T::f[v]);
		}else{
			printf("%d\n",ans[grt(ni)]);
		}
	}
	return 0;
}
