#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef double db;
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
const int N=3010,M=310;
int p[N][M];
db f[N],g[N];
int n,m;
inline void dp(int t){
	g[0]=1;
	for(int i=1;i<=n;i++){
		g[i]=0;
		db perc=(db)p[i][t]/1000;
		for(int j=i;j>=0;j--){
			g[j]*=1-perc;
			if(j){
				g[j]+=g[j-1]*perc;
			}
		}
	}
	db presum=0,preexp=0;
	for(int i=0;i<=n;i++){
		presum+=g[i],preexp+=g[i]*i;
		g[i]=preexp+(1-presum)*i;
	}
	for(int i=n;i>=0;i--){
		db ans=0;
		for(int j=0;j<=i;j++){
			apmax(ans,g[j]+f[i-j]);
		}
		f[i]=ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
#endif
	n=ni,m=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			p[i][j]=ni;
		}
	}
	for(int i=0;i<=n;i++){
		f[i]=0;
	}
	for(int i=1;i<=m;i++){
		dp(i);
	}
	printf("%.10lf\n",f[n]);
	return 0;
}
