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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=100010,MOD=1000000007;
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
int pval[N];
namespace G{
	const int E=400010;
	int to[E],bro[E],head[N],e=0;
	int dfn[N],low[N];
	bool vis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(vis,0,sizeof(vis));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int div[N],cont[N];
	int tim=0;
	int tarjan(int x,int fa){
		int prod=pval[x];
		div[x]=inv(pval[x]),cont[x]=0;
		dfn[x]=low[x]=++tim;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				apmin(low[x],dfn[v]);
			}else{
				int t=tarjan(v,x);
				apmul(prod,t);
				if(low[v]==dfn[x]){
					apadd(cont[x],t);
					apmul(div[x],inv(t));
				}else{
					apmin(low[x],low[v]);
				}
			}
		}
		if(fa==-1){
			div[x]=0;
		}
		return prod;
	}
	int ans[N];
	void dfs2(int x,int prod){
		vis[x]=true;
		ans[x]=sub(::add(mul(prod,div[x]),cont[x]),prod);
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				dfs2(v,prod);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fantasia.in","r",stdin);
	freopen("fantasia.out","w",stdout);
#endif
	G::init();
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	while(tot--){
		G::add(ni,ni);
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(G::dfn[i]==0){
			int prod=G::tarjan(i,-1);
			G::dfs2(i,prod);
			apadd(sum,prod);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		apadd(ans,mul(i,add(sum,G::ans[i])));
	}
	printf("%d\n",ans);
	return 0;
}
