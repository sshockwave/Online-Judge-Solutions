#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef long double db;
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=50010,M=15;
int num[M],ns=0;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],hei[N],cnt[N],dfn[N],tim=0;
	inline void init(int n){
		mset(head+1,-1,n);
		mset(cnt+1,0,n);
		hei[0]=-1;
	}
	inline void ae(const int u,const int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int u,const int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		son[x]=0;
		hei[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x])continue;
			fa[v]=x;
			dfs1(v);
			if(hei[v]>hei[son[x]]){
				son[x]=v,hei[x]=hei[v]+1;
			}
		}
	}
	lint dfs2(const int x){
		lint ans=0;
		dfn[x]=++tim;
		++cnt[dfn[x]];
		if(son[x]==0)return ans;
		ans+=dfs2(son[x]);
		int * const F=cnt+dfn[x];
		for(int p=1;p<=ns;p++){
			const int len=num[p];
			if(len<=hei[x]){
				ans+=F[len];
			}
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x]||v==son[x])continue;
			ans+=dfs2(v);
			const int * const G=cnt+dfn[v];
			for(int j=0;j<=hei[v];j++){
				lint cur=0;
				for(int p=1;p<=ns;p++){
					const int len=num[p]-j-1;
					if(len>=0&&len<=hei[x]){
						cur+=F[len];
					}
				}
				ans+=(lint)cur*G[j];
			}
			for(int j=0;j<=hei[v];j++){
				F[j+1]+=G[j];
			}
		}
		return ans;
	}
}
inline db calc(const int n,const int k){
	assert(k<=n);
	if(k<2)return 0;
	return (db)k/n*(k-1)/(n-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	const int n=ni;
	ns=ni;
	for(int i=1;i<=ns;i++){
		num[i]=ni;
	}
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1);
	lint paircnt=T::dfs2(1);
	for(int t=0;t<3;t++){
		const db ans=paircnt*calc(n,(n+2-t)/3);
		printf("%.2lf\n",(double)ans);
	}
	return 0;
}
