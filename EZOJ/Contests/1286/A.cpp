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
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=1000010,MOD=1000000007;
inline int add(const int &a,const int &b){
	assert(a<MOD&&a>=0);
	assert(b<MOD&&b>=0);
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	assert(a<MOD&&a>=0);
	assert(b<MOD&&b>=0);
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
int a[N],b[N];
const int lessN=110;
int f[lessN][lessN][lessN];
int main(){
	int n=ni,k=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b[i]=ni;
	}
	if(k==1){
		int ans=0;
		for(int i=1,j=1;i<=n;i++){
			for(;b[j]<=a[i];j++);
			apadd(ans,j-1);
		}
		printf("%d\n",mul(ans,fpow(n,MOD-2)));
	}else{
		memset(f,0,sizeof(f));
		for(int i=0;i<=n;i++){
			f[i][0][0]=1;
			f[0][i][0]=1;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=i&&k<=j;k++){
					f[i][j][k]=f[i-1][j][k];
					for(int l=1;l<=j;l++){
						if(a[i]>=b[l]){
							apadd(f[i][j][k],f[i-1][l-1][k-1]);
						}
					}
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			apadd(ans,mul(f[n][n][i],fpow(i,k)));
		}
		printf("%d\n",mul(ans,fpow(n,MOD-2)));
	}
}
