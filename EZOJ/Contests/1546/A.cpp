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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=510;
int O;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
namespace gmath{
	int c[N][N];
	inline void main(int n){
		memset(c,0,sizeof(c));
		for(int i=0;i<=n;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=(c[i-1][j-1]+c[i-1][j])%O;
			}
		}
	}
}
int f[N],g[N][N],h[N];
int tmpc[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
#endif
	const int n=ni;
	O=ni;
	gmath::main(n-1);
	f[0]=f[1]=0;
	for(int i=2;i<=n;i++){
		f[i]=fpow(2,(i-1)*(i-2)/2);
	}
	memset(g,0,sizeof(g));
	g[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j*2<=i;j++){
			int &ans=g[i][j];
			for(int k=1;k<=i;k++){
				apadd(ans,(lint)g[i-k][j-1]*f[k]);
			}
		}
	}
	h[0]=0;
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=1;j<=i;j++){
			for(int k=1;k*2<=j;k++){
				apadd(sum,(lint)g[j][k]*tmpc[i-j+k][k]);
			}
		}
		h[i]=(fpow(2,i*(i+1)/2)+(O-sum))%O;
		for(int j=0;j<=i;j++){
			tmpc[i][j]=(lint)gmath::c[i][j]*h[i]%O;
		}
	}
	printf("%d\n",h[n]);
	return 0;
}
