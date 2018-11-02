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
namespace G{
	const int N=::N<<1,E=::N*::N;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		mset(head+1,-1,n);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfn[N],low[N],bln[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	void dfs(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				dfs(v);
				apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],dfn[v]);
			}
		}
		if(low[x]==dfn[x]){
			int v;
			do{
				v=stk[--ss],instk[v]=false;
				bln[v]=x;
			}while(x!=v);
		}
	}
	bool twosat(int n){
		mset(dfn+1,0,n);
		tim=0;
		for(int i=1;i<=n;i++){
			if(dfn[i]==0){
				dfs(i);
			}
		}
		for(int i=1;i<=n;i+=2){
			if(bln[i]==bln[i+1])return false;
		}
		return true;
	}
}
struct Edge{
	int u,v,w;
}e[E];
inline bool cmp_w(const Edge &a,const Edge &b){
	return a.w<b.w;
}
int fa[N<<1];
inline int grt(int x){
	return fa[x]!=x?fa[x]=grt(fa[x]):x;
}
int nd(int x,int d){
	return grt((x<<1)-d);
}
inline int Main(int n){
	int es=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			e[++es]=(Edge){i,j,ni};
		}
	}
	sort(e+1,e+es+1,cmp_w);
	int ans=INF;
	for(int i=1;i<=(n<<1);i++){
		fa[i]=i;
	}
	e[0].w=0;
	for(int i=es,l=0,r=es;i>=1;i--){
		apmin(l,i),apmin(r,i);
		for(;l<r;){
			const int m=(l+r)>>1;
			G::init(n<<1);
			for(int j=m+1;j<=i;j++){
				G::ae(nd(e[j].u,0),nd(e[j].v,1));
				G::ae(nd(e[j].v,0),nd(e[j].u,1));
			}
			if(G::twosat(n<<1)){
				r=m;
			}else{
				l=m+1;
			}
		}
		apmin(ans,e[i].w+e[l].w);
		const int u=e[i].u,v=e[i].v;
		if(nd(u,0)!=nd(v,1)){
			fa[nd(u,0)]=nd(v,1);
			fa[nd(u,1)]=nd(v,0);
			if(nd(u,0)==nd(v,0))break;
			l=0,r=es;
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
