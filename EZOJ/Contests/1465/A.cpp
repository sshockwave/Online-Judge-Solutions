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
const int N=1000010;
lint ans=0;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	bool vis[N];
	int son[N],dep[N],hei[N];
	int dfn[N],tim=0;
	inline void init(int n){
		mset(head+1,-1,n);
		mset(vis+1,0,n);
		dep[0]=dep[1]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x,int fa){
		hei[x]=dep[x];
		son[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dep[v]=dep[x]+1;
			dfs1(v,x);
			if(hei[v]>hei[x]){
				hei[x]=hei[v],son[x]=v;
			}
		}
	}
	lint f[N];
	void dfs2(int x,int fa,lint g[]){
		dfn[x]=++tim;
		lint *const f=T::f+dfn[x];
		f[0]=1;
		if(son[x]==0)return;
		dfs2(son[x],x,g-1);
		ans+=g[0];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa||v==son[x])continue;
			lint *ng=new lint[(hei[v]-dep[x])<<1];
			mset(ng,0,(hei[v]-dep[x])<<1);
			ng+=hei[v]-dep[x];
			lint *const nf=T::f+tim;
			dfs2(v,x,ng-1);
			ans+=ng[0];
			for(int d=1;d<=hei[v]-dep[x];d++){
				ans+=g[d]*nf[d]+f[d]*ng[d];
				g[d]+=f[d]*nf[d]+ng[d];
				f[d]+=nf[d];
			}
			delete (ng-(hei[v]-dep[x]));
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("zh.in","r",stdin);
	freopen("zh.out","w",stdout);
#endif
	const int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1,0);
	{
		lint *ng=new lint[T::hei[1]<<1];
		mset(ng,0,T::hei[1]<<1);
		ng+=T::hei[1];
		T::dfs2(1,0,ng-1);
		delete (ng-T::hei[1]);
	}
	printf("%lld\n",ans);
	return 0;
}
