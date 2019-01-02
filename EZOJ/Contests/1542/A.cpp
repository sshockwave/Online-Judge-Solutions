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
const int N=2010,INF=0x7f7f7f7f;
int gval[N][N];
int dis[N];
bool vis[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	int mnval=INF;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			gval[i][j]=gval[j][i]=ni;
			apmin(mnval,gval[i][j]);
		}
	}
	mset(dis+1,0x7f,n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j){
				apmin(dis[i],gval[i][j]-=mnval);
			}
		}
		dis[i]<<=1;
	}
	mset(vis+1,0,n);
	for(int tot=n;tot--;){
		int x=0;
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			if(x==0||dis[i]<dis[x]){
				x=i;
			}
		}
		vis[x]=true;
		for(int i=1;i<=n;i++){
			apmin(dis[i],dis[x]+gval[x][i]);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld\n",dis[i]+(lint)mnval*(n-1));
	}
	return 0;
}
