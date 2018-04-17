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
const int N=1000010,O=998244353;
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
inline int inv(int x){
	return fpow(x,O-2);
}
inline int C(int n,int k){
	assert(n>=k);
	if(k==1)return n;
	else if(k==2){
		return (((lint)n*(n-1))>>1)%O;
	}else assert(false);
}
int f[3][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int n=ni;
	memset(f,0,sizeof(f));
	int r=0,r1=1,r2=2;
	f[r][n]=1;
	if(n>1){
		f[r1][n-1]=1;
		if(n>2){
			f[r2][n-2]=1;
		}
	}
	for(int j=n;j>=1;--j,swap(r,r1),swap(r1,r2)){
		for(int k=j-2;k>=0;k-=2){
			f[r2][k]=0;
		}
		if(j>2){
			f[r2][j-2]=1;
		}
		for(int k=j;k>=0;k-=2){
			const lint F=f[r][k];
			if(F==0)continue;
			f[r][k]=0;
			const int m=j,a=k,b=m-a;
			if(a>=2){
				apadd(f[r][a-2],F*C(a,2));
			}
			if(a>=1&&b>=1){
				apadd(f[r1][a-1],F*a%O*(m-a));
			}
			if(b>=2){
				apadd(f[r2][a],F*C(m-a,2));
			}
		}
	}
	printf("%d\n",f[r][0]);
	return 0;
}
