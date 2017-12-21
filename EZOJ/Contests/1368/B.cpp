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
const int N=300010;
namespace T{
	int son[N],bro[N];
	inline void init(){
		memset(son,-1,sizeof(son));
	}
	inline void ae(int u,int v){
		bro[v]=son[u],son[u]=v;
	}
	int f[N],g[N];//f:no use g:okay
	void dfs(int x){
		f[x]=0,g[x]=1;
		for(int v=son[x];~v;v=bro[v]){
			dfs(v);
			f[x]+=g[v];
			g[x]+=f[v];
		}
		apmax(g[x],f[x]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
#endif
	int n=ni,tp=ni,ans=0;
	T::init();
	for(int i=1;i<=n;i++){
		int f=ni^(tp*ans);
		if(f==0){
			f=n+1;
		}
		T::ae(f,i);
		T::dfs(n+1);
		printf("%d\n",ans=T::g[n+1]);
	}
	return 0;
}
