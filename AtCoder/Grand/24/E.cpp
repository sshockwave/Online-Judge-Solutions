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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=310;
int O;
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
using gmath::c;
int n;
int f[N],g[N];
inline void dp_exp(){//g=exp(f)
	g[0]=1;
	assert(f[0]==0);
	for(int i=1;i<=n;i++){
		int &ans=g[i]=0;
		for(int j=1;j<=i;j++){
			ans=(ans+(lint)f[j]*g[i-j]%O*c[i-1][j-1])%O;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("grow.in","r",stdin);
	freopen("grow.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	O=ni;
	gmath::main(n);
	mset(f,0,n+1);
	for(;tot--;){
		dp_exp();
		for(int i=1;i<=n;i++){
			f[i]=(f[i]+g[i-1])%O;
		}
	}
	dp_exp();
	printf("%d\n",g[n]);
	return 0;
}
