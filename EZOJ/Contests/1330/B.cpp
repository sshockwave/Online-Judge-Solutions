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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=50004,M=204,MOD=998244353;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
int m;
int f[N][M],g[N][M];
namespace G{
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
	int tmp1[M],tmp2[M],mx[N];
	void dfs(int x,int fa){
		memset(f[x],0,m<<2);
		memset(g[x],0,m<<2);
		f[x][0]=1,mx[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				memcpy(tmp1,f[x],(mx[x]+1)<<2);
				memcpy(tmp2,g[x],(mx[x]+1)<<2);
				memset(f[x],0,min(m,mx[x]+mx[v]+1)<<2);
				memset(g[x],0,min(m,mx[x]+mx[v]+1)<<2);
				for(int i=0;i<=mx[x];i++){
					for(int j=0;j<=mx[v];j++){
						apadd(f[x][(i+j)%m],mul(tmp1[i],::add(f[v][j],mul(2,g[v][j]))));
						apadd(g[x][(i+j)%m],mul(mul(2,tmp2[i]),::add(f[v][j],g[v][j])));
						apadd(g[x][(i+j+1)%m],mul(tmp1[i],f[v][j]));
					}
				}
				mx[x]=min(m-1,mx[x]+mx[v]+1);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
#endif
	int n=ni;
	m=ni;
	G::init();
	for(int i=1;i<n;i++){
		G::add(ni,ni);
	}
	G::dfs(1,0);
	printf("%d\n",add(f[1][0],g[1][0]));
	return 0;
}
