#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=55,N2=1010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int f[N][N][N];
int a[N];
int c[N2][N2];
int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<N2;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=add(c[i-1][j-1],c[i-1][j]);
		}
	}
	for(int tot=ni;tot--;){
		int n=ni;
		for(int i=1;i<=n;i++){
			a[i]=ni;
		}
		memset(f,0,sizeof(f));
		f[0][0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=i;j++){
				for(int k=0;k<=n-2;k++){
					f[i][j][k]=f[i-1][j][k];
					if(j){
						for(int l=max(k-a[i]+1,0);l<=k;l++){
							apadd(f[i][j][k],mul(f[i-1][j-1][l],c[k][l]));
						}
					}
				}
			}
		}
		printf("%d ",n);
		for(int i=2;i<=n;i++){
			printf("%d ",f[n][i][i-2]);
		}
		putchar('\n');
	}
}