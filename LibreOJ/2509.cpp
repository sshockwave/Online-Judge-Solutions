#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int>vi;
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=500010;
lint w[N];
struct Block{
	int sz;
	lint w;
	inline void operator += (const Block &b){
		sz+=b.sz,w+=b.w;
	}
	inline friend bool operator < (const Block &a,const Block &b){
		return a.w*b.sz<b.w*a.sz;
	}
};
lint ans=0;
int tval=0;
inline bool lcmp(int a,int b);
namespace H{
	int lson[N],rson[N],rdis[N];
	inline void init(int n){
		mset(lson+1,0,n),mset(rson+1,0,n);
		rdis[0]=-1;
	}
	int mg(int u,int v){
		if(u==0||v==0)return u|v;
		if(lcmp(v,u)){
			swap(u,v);
		}
		rson[u]=mg(rson[u],v);
		if(rdis[rson[u]]>rdis[lson[u]]){
			swap(lson[u],rson[u]);
		}
		rdis[u]=rdis[rson[u]]+1;
		return u;
	}
	inline int del(int x){
		return mg(lson[x],rson[x]);
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	bool vis[N];
	bool ok[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(vis+1,0,n);
		mset(ok+1,0,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	vi cliq[N];
	Block f[N];
	int dfs(int x){
		vis[x]=ok[x]=true;
		int rt=0;
		for(int i=head[x];~i;i=bro[i]){
			rt=H::mg(rt,dfs(to[i]));
		}
		f[x]=(Block){1,w[x]};
		for(;rt&&!lcmp(x,rt);rt=H::del(rt)){
			ok[rt]=false;
			f[x]+=f[rt];
			cliq[x].push_back(rt);
		}
		return H::mg(rt,x);
	}
	void dfs2(int x){
		ans+=w[x]*++tval;
		for(vi::iterator it=cliq[x].begin(),ti=cliq[x].end();it!=ti;++it){
			dfs2(*it);
		}
	}
}
inline bool lcmp(int a,int b){
	return T::f[a]<T::f[b];
}
int fa[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
#endif
	int n=ni;
	T::init(n),H::init(n);
	for(int i=1;i<=n;i++){
		fa[i]=ni;
		if(fa[i]){
			T::ae(fa[i],i);
		}
	}
	for(int i=1;i<=n;i++){
		w[i]=next_num<lint>();
	}
	int rt=0;
	for(int i=1;i<=n;i++){
		if(fa[i]==0){
			rt=H::mg(rt,T::dfs(i));
		}
	}
	for(int i=1;i<=n;i++){
		if(!T::vis[i]){
			puts("-1");
			return 0;
		}
	}
	for(;rt;rt=H::del(rt)){
		T::dfs2(rt);
	}
	assert(tval==n);
	printf("%lld\n",ans);
	return 0;
}
