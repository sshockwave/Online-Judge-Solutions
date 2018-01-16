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
const int N=3010,INF=0x7f7f7f7f;
int ans=INF,ansk;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	int size[N];
	int f[N][N],g[N][N],h[N][N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(f,127,sizeof(f));
		memset(g,127,sizeof(g));
		memset(h,127,sizeof(h));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs(int x,int fa){
		size[x]=1;
		int *f=T::f[x],*g=T::g[x],*h=T::h[x];
		f[1]=g[1]=h[1]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				int *nf=T::f[v],*ng=T::g[v],*nh=T::h[v];
				for(int a=size[x];a>=1;a--){
					for(int b=size[v];b>=1;b--){
						apmin(f[a+b],f[a]+nf[b]+(val[i]<<1));
						apmin(g[a+b],f[a]+ng[b]+val[i]);
						apmin(h[a+b],f[a]+nh[b]+(val[i]<<1));
						apmin(g[a+b],g[a]+nf[b]+(val[i]<<1));
						apmin(h[a+b],g[a]+ng[b]+val[i]);
						apmin(h[a+b],h[a]+nf[b]+(val[i]<<1));
					}
				}
				size[x]=min(size[x]+size[v],ansk);
			}
		}
		apmin(ans,h[ansk]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	T::init();
	int n=ni;
	ansk=ni;
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v,ni);
	}
	T::dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
