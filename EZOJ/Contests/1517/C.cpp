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
const int N=260,E=N*N/2,INF=0x7f7f7f7f;
int curmx;
bool vis[N];
namespace G{
	const int E=::E<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
		e=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs(int x){
		if(vis[x])return;
		vis[x]=true;
		for(int i=head[x];~i;i=bro[i]){
			apmax(curmx,val[i]);
			dfs(to[i]);
		}
	}
}
struct Edge{
	int u,v,w;
}edg[E];
inline bool ecmp(const Edge &a,const Edge &b){
	return a.w<b.w;
}
int fa[N],oppo[N];
int grt(int x){
	return fa[x]!=x?fa[x]=grt(fa[x]):x;
}
inline void mg(int u,int v){
	if(u==0||v==0)return;
	fa[grt(u)]=grt(v);
}
inline void t_mg(int u,int v){
	u=grt(u),v=grt(v);
	int u1=oppo[u],v1=oppo[v];
	mg(u,v1),mg(v,u1);
	u=grt(u),v=grt(v);
	oppo[u]=v,oppo[v]=u;
}
namespace brute{
	const int N=20,INF=0x7f7f7f7f;
	int f[1<<N];
	int mat[N+2][N+2];
	inline int Main(const int n){
		const int sn=1<<n;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				mat[i][j]=mat[j][i]=ni;
			}
		}
		f[0]=0;
		for(int s=1;s<sn;s++){
			int x=1;
			for(;((s>>(x-1))&1)==0;x++);
			assert((1<<(x-1))==(s&-s));
			f[s]=f[s^(1<<(x-1))];
			for(int i=x+1;x<=n;x++){
				if((s>>(x-1))&1){
					apmax(f[s],mat[x][i]);
				}
			}
		}
		int ans=INF;
		for(int s=0;s<sn;s++){
			apmin(ans,f[s]+f[s^(sn-1)]);
		}
		return ans;
	}
}
inline int Main(const int n){
	if(n<=20)return brute::Main(n);
	int es=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			edg[++es]=(Edge){i,j,ni};
		}
	}
	sort(edg+1,edg+es+1,ecmp);
	int ans=INF;
	edg[0].w=edg[es+1].w=0;
	curmx=0;
	mset(vis+1,0,n);
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	mset(oppo+1,0,n);
	G::init(n);
	for(int i=es;i>=1;i--){
		apmin(ans,edg[i].w+edg[max(curmx,i)].w);
		const int u=edg[i].u,v=edg[i].v;
		t_mg(u,v);
		G::add(u,v,i);
		if(oppo[grt(u)]==grt(u)){
			apmax(curmx,i);
			G::dfs(u);
			G::dfs(v);
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
#endif
	for(int n;scanf("%d",&n)!=EOF;printf("%d\n",Main(n)));
	return 0;
}
