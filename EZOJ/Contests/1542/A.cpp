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
const int N=2010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
lint dis[N][N];
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}edg[N*N/2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	if(n==1){
		puts("0");
		return 0;
	}
	memset(dis,0x7f,sizeof(dis));
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
	}
	int es=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			edg[++es]=(Edge){i,j,ni};
		}
	}
	sort(edg+1,edg+es+1);
	const lint ansdt=(lint)(n-1)*edg[1].w;
	for(int p=es;p>=1;p--){
		edg[p].w-=edg[1].w;
		const int u=edg[p].u,v=edg[p].v,w=edg[p].w;
		for(int i=1;i<=n;i++){
			if(dis[i][u]<LINF){
				for(int j=1;j<=n;j++){
					apmin(dis[i][j],dis[i][u]+w+(j!=v?w:0));
				}
			}
			if(dis[i][v]<LINF){
				for(int j=1;j<=n;j++){
					apmin(dis[i][j],dis[i][v]+w+(j!=u?w:0));
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		lint curans=ansdt+dis[i][edg[1].u];
		printf("%lld\n",curans);
	}
	return 0;
}
