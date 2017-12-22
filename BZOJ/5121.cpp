#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=50010,B=20;
inline int grt(lint x){
	int ans=sqrt(x);
	for(;(lint)ans*ans<x;ans++);
	for(;(lint)ans*ans>x;ans--);
	return ans;
}
lint a[N];
int rt;
struct BIT{
	lint *c;
	int n;
	inline void init(int _n){
		n=_n;
		c=new lint[n+1];
		memset(c,0,(n+1)<<3);
	}
	inline void add(int x,lint v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline lint sum(int x){
		assert(x<=n);
		lint ans=0;
		for(;x;ans+=c[x],x^=x&-x);
		return ans;
	}
	inline lint ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}bt[B][B];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],idx[N],tim=0;
	int ufa[N][B];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(fa,0,sizeof(fa));
		memset(son,0,sizeof(son));
		memset(ufa,0,sizeof(ufa));
		fa[1]=son[0]=size[0]=dep[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	inline void act(int x){//x:original
		if(a[x]==1)return;
		lint dt=grt(a[x])-a[x];
		a[x]+=dt;
		for(int i=1;i<=rt;i++){
			bt[i][dfn[x]%i].add(dfn[x]/i+1,dt);
		}
	}
	int stk[N],ss=0;
	void dfs1(int x){
		for(int i=1,ti=min(rt,ss);i<=ti;i++){
			ufa[x][i]=stk[ss-i];
		}
		stk[ss++]=x;
		fa[x]=ufa[x][1];
		dep[x]=ss;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
		ss--;
	}
	void dfs2(int x){
		idx[dfn[x]=tim++]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]){
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					dfs2(v);
				}
			}
		}
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline int fly(int x,int n){
		assert(n<dep[x]);
		for(int d;d=dep[x]-dep[fa[top[x]]],d<=n;n-=d,x=fa[top[x]]);
		return idx[dfn[x]-n];
	}
	inline int uroot(int x,int k){
		return a[x]==1?ufa[x][k]=uroot(ufa[x][k],k):x;
	}
	int op,k;
	lint ans;
	inline void workp(int x){
		if(op){
			ans+=a[x];
		}else{
			act(x);
		}
	}
	inline void workup(int x,int w,int d){//dep[x]%k==d && don't go above w
		assert(w);
		if(dep[x]%k!=d){
			workp(x);
			if(dep[x]<d||(dep[x]<k&&d==0))return;
			x=fly(x,(dep[x]%k+k-d)%k);
		}
		if(k>rt){
			for(;dep[x]>=dep[w];x=fly(x,k)){
				workp(x);
				if(dep[x]<=k)break;
			}
		}else if(op){
			for(;dep[x]>=dep[w];x=fa[top[x]]){
				if(dep[x]<d||(dep[x]<k&&d==0))break;
				x=fly(x,(dep[x]%k+k-d)%k);
				if(dep[x]<dep[w])break;
				int y=idx[max(dfn[w],dfn[top[x]])];
				y=idx[dfn[y]+((d-dep[y])%k+k)%k];
				assert(dep[y]%k==d);
				assert(dfn[y]<=dfn[x]&&(dfn[x]-dfn[y])%k==0);
				ans+=bt[k][dfn[x]%k].ask(dfn[y]/k+1,dfn[x]/k+1);
			}
		}else for(;x=uroot(x,k),dep[x]>=dep[w];x=ufa[x][k]){
			act(x);
		}
	}
	inline void work(){
		op=ni;
		int u=ni,v=ni,w=lca(u,v);
		k=ni;
		ans=0;
		if(u!=w){
			workup(u,fly(u,dep[u]-dep[w]-1),dep[u]%k);
		}
		workup(v,w,(((dep[w]<<1)-dep[u])%k+k)%k);
		if(op){
			printf("%lld\n",ans);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("down.in","r",stdin);
	freopen("down.out","w",stdout);
#endif
	int n=ni;
	rt=min(n,B-3);
	for(int i=1;i<=n;i++){
		a[i]=next_num<lint>();
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	assert(T::tim==n);
	for(int i=1;i<=rt;i++){
		for(int j=0;j<i;j++){
			assert(j<n);
			bt[i][j].init((n-1-j)/i+1);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=rt;j++){
			bt[j][T::dfn[i]%j].add(T::dfn[i]/j+1,a[i]);
		}
	}
	for(int tot=ni;tot--;){
		T::work();
	}
	return 0;
}
