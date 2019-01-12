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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(b));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=510;
int lst[N],ls;
bool vis[N];
int pval[N];
namespace G{
	const int E=(::N<<1)+1e5;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void dfs_lst(int x){
		vis[x]=true;
		lst[++ls]=pval[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]])continue;
			dfs_lst(v);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("balance.in","r",stdin);
	freopen("balance.out","w",stdout);
#endif
	int n=ni,m1=ni,m2=ni;
	G::init(n);
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	for(int i=1;i<=m1;i++){
		int u=ni,v=ni;
		G::ae(u,v);
		G::ae(v,u);
	}
	for(int i=1;i<=m2;i++){
		int u=ni,v=ni;
		G::ae(v,u);
	}
	mset(vis+1,0,n);
	lint ans=0;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		ls=0;
		G::dfs_lst(i);
		sort(lst+1,lst+ls+1);
		int v=lst[(ls+1)/2];
		for(int j=1;j<=ls;j++){
			ans+=cabs(lst[j]-v);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
