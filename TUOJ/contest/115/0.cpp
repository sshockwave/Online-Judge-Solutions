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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=6,M=110,SN=1<<N,NM=N*M*2,O=998244353;
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
inline int inv_pow(int x){
	return fpow(x,O-2);
}
int f[2][SN][NM];
char mat[N][M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni,m=ni;
	int tsum=n*(m-1)+m*(n-1);
	for(int i=0;i<n;i++){
		scanf("%s",mat[i]);
	}
	bool r=0;
	const int sn=1<<n;
	f[r][0][0]=1;
	for(int p=0;p<m;p++){
		for(int i=0;i<n;i++,r^=1){
			memset(f[!r],0,sizeof(f[!r]));
			for(int s=0;s<sn;s++){
				for(int j=0;j<=tsum;j++){
					const int F=f[r][s][j];
					if(F==0)continue;
					apadd(f[!r][s^(s&(1<<i))][j+(i&&((s>>(i-1))&1))+((s>>i)&1)],F);
					if(mat[i][p]=='*'){
						apadd(f[!r][s|(1<<i)][j+(i>0)+(p>0)],O-F);
					}
				}
			}
		}
	}
	int ans=0;
	for(int s=0;s<sn;s++){
		for(int j=1;j<=tsum;j++){
			ans=(ans+(lint)f[r][s][j]*inv_pow(j))%O;
		}
	}
	ans=(lint)ans*tsum%O;
	ans=(O-ans)%O;
	printf("%d\n",ans);
	return 0;
}
