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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
int pval[N];
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	lint f[N][2],g[N];
	void dfs(int x){
		lint gsum=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			gsum+=g[v];
		}
		f[x][0]=gsum-pval[x];
		f[x][1]=gsum+pval[x];
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			apmax(f[x][0],f[v][0]+(gsum-g[v]));
			apmax(f[x][1],f[v][1]+(gsum-g[v]));
		}
		g[x]=max(f[x][0]+pval[x],f[x][1]-pval[x]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("experience.in","r",stdin);
	freopen("experience.out","w",stdout);
#endif
	const int n=ni;
	T::init(n);
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	for(int i=1;i<n;i++){
		const int u=ni,v=ni;
		T::ae(u,v);
	}
	T::dfs(1);
	printf("%lld\n",T::g[1]);
	return 0;
}
