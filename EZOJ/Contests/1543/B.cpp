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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
struct Edge{
	int x1,x2;
	int y1,y2;
	int w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}edg[N*3];
int n,e;
namespace solve1{
	const int N=1010,E=N*N/2;
	struct Edge2{
		int u,v;
		lint w;
		inline friend bool operator < (const Edge2 &a,const Edge2 &b){
			return a.w<b.w;
		}
	}edg2[E];
	namespace dj{
		int fa[N];
		inline void init(int n){
			mset(fa+1,0,n);
		}
		inline int rt(int x){
			return fa[x]?fa[x]=rt(fa[x]):x;
		}
	}
	lint val[N][N];
	inline lint main(){
		dj::init(n);
		for(int i=1;i<=e;i++){
			val[edg[i].x1][edg[i].y1]+=edg[i].w;
			val[edg[i].x1][edg[i].y2+1]-=edg[i].w;
			val[edg[i].x2+1][edg[i].y1]-=edg[i].w;
			val[edg[i].x2+1][edg[i].y2+1]+=edg[i].w;
		}
		for(int i=1;i<=n;i++){
			for(int j=2;j<=n;j++){
				val[i][j]+=val[i][j-1];
			}
		}
		for(int i=2;i<=n;i++){
			for(int j=1;j<=n;j++){
				val[i][j]+=val[i-1][j];
			}
		}
		int es=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				edg2[++es]=(Edge2){i,j,val[i][j]};
			}
		}
		sort(edg2+1,edg2+es+1);
		lint ans=0;
		for(int i=1;i<=es;i++){
			int u=dj::rt(edg2[i].u),v=dj::rt(edg2[i].v);
			if(u!=v){
				dj::fa[u]=v;
				ans+=edg2[i].w;
			}
		}
		return ans;
	}
}
namespace solve3{
	namespace dj{
		int fa[N];
		inline void init(int n){
			mset(fa+1,0,n);
		}
		inline int rt(int x){
			return fa[x]?fa[x]=rt(fa[x]):x;
		}
	}
	lint ans=0;
	int nxt[N];
	inline int getnxt(int x){
		if(nxt[x]==x&&x<n&&dj::rt(x)==dj::rt(x+1)){
			nxt[x]=x+1;
		}
		return nxt[x]!=x?nxt[x]=getnxt(nxt[x]):x;
	}
	int curw;
	inline void mg(int u,int v){
		u=dj::rt(u),v=dj::rt(v);
		if(u!=v){
			ans+=curw;
			dj::fa[u]=v;
		}
	}
	inline void mg_intv(int l,int r){
		for(;getnxt(l)!=getnxt(r);mg(l,getnxt(l)+1));
	}
	int int_l[N],int_r[N];
	inline lint main(){
		for(int i=1;i<=n;i++){
			nxt[i]=i;
			int_l[i]=int_r[i]=-1;
		}
		dj::init(n);
		for(int i=1;i<=e;i++){
			int_l[edg[i].x1]=edg[i].y1;
			int_r[edg[i].x2]=edg[i].y2;
		}
		for(int i=1;i<=n;i++){
			if(int_l[i]==-1){
				if(i+1<=n){
					edg[++e]=(Edge){i,i,i+1,n,0};
				}
			}else{
				if(i+1<=int_l[i]-1){
					edg[++e]=(Edge){i,i,i+1,int_l[i]-1,0};
				}
				if(int_r[i]+1<=n){
					edg[++e]=(Edge){i,i,int_r[i]+1,n,0};
				}
			}
		}
		sort(edg+1,edg+e+1);
		for(int i=1;i<=e;i++){
			curw=edg[i].w;
			mg_intv(edg[i].x1,edg[i].x2);
			mg_intv(edg[i].y1,edg[i].y2);
			mg(edg[i].x1,edg[i].y1);
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
#endif
	n=ni,e=ni;
	for(int i=1;i<=e;i++){
		edg[i]=(Edge){ni,ni,ni,ni,ni};
	}
	lint ans=0;
	if(n<=1000&&e<=1000){
		ans=solve1::main();
	}else{
		ans=solve3::main();
	}
	printf("%lld\n",ans);
	return 0;
}
