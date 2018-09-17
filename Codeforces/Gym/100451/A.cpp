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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=2010;
const lint INF64=0x7f7f7f7f7f7f7f7fll;
int n,c[N];
lint dis[N][N];
lint f[N][N],_f[N][N],f_[N][N];
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(const int n){
		mset(head+1,-1,n);
	}
	inline void ae(const int u,const int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int u,const int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x,int fa,lint dis[]){
		dis[x]=dis[fa]+c[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dfs1(v,x,dis);
		}
	}
	void dfs2(int x,int fa){
		for(int i=1;i<=n;i++){
			f[x][i]=dis[x][i];
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dfs2(v,x);
			for(int j=1;j<=n;j++){
				const lint val=dis[x][j];
				lint ans=INF64;
				apmin(ans,_f[v][upper_bound(dis[v]+1,dis[v]+n+1,val-c[x])-dis[v]-1]);
				apmin(ans,f_[v][lower_bound(dis[v]+1,dis[v]+n+1,val+c[v])-dis[v]]);
				if(ans<INF64&&f[x][j]<INF64){
					f[x][j]+=ans;
				}else{
					f[x][j]=INF64;
				}
			}
		}
		_f[x][0]=f_[x][n+1]=INF64;
		for(int i=1;i<=n;i++){
			_f[x][i]=min(_f[x][i-1],f[x][i]);
		}
		for(int i=n;i>=1;i--){
			f_[x][i]=min(f_[x][i+1],f[x][i]);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("decorate.in","r",stdin);
	freopen("decorate.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		c[i]=ni;
	}
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni+1,ni+1);
	}
	for(int i=1;i<=n;i++){
		T::dfs1(i,0,dis[i]);
		sort(dis[i]+1,dis[i]+n+1);
	}
	T::dfs2(1,0);
	printf("%I64d\n",f_[1][1]);
	return 0;
}
