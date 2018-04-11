#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
lint pval[N];
namespace unifind{
	int fa[N];
	inline void init(int n){
		for(int i=1;i<=n;i++){
			fa[i]=i;
		}
	}
	int grt(int x){
		return fa[x]!=x?fa[x]=grt(fa[x]):x;
	}
	inline void mg(int u,int v){
		fa[grt(u)]=grt(v);
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	lint len[N];
	bool instk[N];
	bool ontr[E];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(instk,0,sizeof(instk));
		memset(fa,-1,sizeof(fa));
		memset(top,0,sizeof(top));
		memset(ontr,0,sizeof(ontr));
		son[0]=0,size[0]=0,dep[0]=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs1(int x){
		x[dep]=x[fa][dep]+1,x[size]=1;
		x[instk]=true;
		int rt=unifind::grt(x);
		for(int i=x[head],v;~i;i=i[bro]){
			pval[rt]=gcd(pval[rt],(lint)val[i]<<1);
			if((v=i[to])[fa]==-1){
				ontr[i]=true;
				v[fa]=x,v[len]=x[len]+val[i];
				dfs1(v);
				x[size]+=v[size];
				if(v[size]>x[son][size]){
					x[son]=v;
				}
			}else if(v[instk]){
				pval[rt]=gcd(pval[rt],x[len]-v[len]+val[i]);
			}
			assert(unifind::grt(v)==rt);
		}
		x[instk]=false;
	}
	bool vis[N];//cout
	void dfs2(int x){
		assert(!vis[x]),vis[x]=true;
		top[x]=x[fa][son]==x?x[fa][top]:x;
		if(x[son]){
			dfs2(x[son]);
			for(int i=x[head],v;~i;i=i[bro]){
				if(ontr[i]&&(v=to[i])!=x[son]){
					assert(v[fa]==x);
					dfs2(v);
				}
			}
		}
	}
	inline int lca(int u,int v){
		for(;u[top]!=v[top];u[top][dep]>v[top][dep]?(u=u[top][fa]):(v=v[top][fa]));
		return u[dep]<v[dep]?u:v;
	}
	inline lint dis(int u,int v){
		return u[len]+v[len]-(lca(u,v)[len]<<1);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("plan.in","r",stdin);
	freopen("plan.out","w",stdout);
#endif
	int n=ni,m=ni,q=ni;
	memset(pval,0,sizeof(pval));
	unifind::init(n),T::init();
	for(int i=1;i<=m;i++){
		int u=ni,v=ni;
		unifind::mg(u,v);
		T::add(u,v,ni);
	}
	for(int i=1;i<=n;i++){
		if(T::fa[i]==-1){
			T::fa[i]=0;
			T::dfs1(i),T::dfs2(i);
		}
	}
	for(int tot=q;tot--;){
		int u=ni,v=ni;
		lint k=next_num<lint>();
		if(unifind::grt(u)!=unifind::grt(v)){
			puts("NIE");
		}else{
			printf("%lld\n",T::dis(u,v)%gcd(u[unifind::fa][pval],(lint)k));
		}
	}
	return 0;
}
