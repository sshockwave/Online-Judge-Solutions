#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef long double db;
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=510;
namespace gmath{
	const int N=1010;
	db c[N][N];
	inline void main(int n){
		memset(c,0,sizeof(c));
		for(int i=0;i<=n;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=c[i-1][j-1]+c[i-1][j];
			}
		}
	}
}
db f[N][N];
inline void calcf(int n,int d,int r){
	using gmath::c;
	if(n<=r){
		f[n][d]=c[n+d-1][n-1]*(n+d);
		return;
	}
	db &ans=f[n][d]=r*c[n+d-1][n-1];
	for(int i=max(n-d,0);i<=n;i++){
		ans+=c[n][i]*f[n-i][d+i-n];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gem.in","r",stdin);
	freopen("gem.out","w",stdout);
#endif
	int n=ni,d=ni,r=ni;
	gmath::main(n+d);
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		for(int j=0;j<=d;j++){
			calcf(i,j,r);
		}
	}
	double ans=f[n][d]/gmath::c[n+d-1][n-1];
	printf("%.10lf\n",ans);
	return 0;
}
