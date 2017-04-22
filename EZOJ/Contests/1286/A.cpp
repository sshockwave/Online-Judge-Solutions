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
inline int sub(int &a,int b){
	return b==0?a:add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	assert(a<MOD&&a>=0);
	assert(b<MOD&&b>=0);
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apsub(int &a,const int &b){
	if(b){
		apadd(a,MOD-b);
	}
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
int a[N],b[N],w[N];
const int N2=2010;
int f[N2],g[N2],c[N2][N2],fac[N];
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
			for(;j<=n&&b[j]<=a[i];j++);
			apadd(ans,j-1);
		}
		printf("%d\n",mul(ans,fpow(n,MOD-2)));
	}else if(k==2){
		int sum=0,ans=0;
		fac[0]=1;
		for(int i=1,j=0;i<=n;i++){
			for(;j<=n&&b[j]<=a[i];j++);
			w[i]=j-1;
			fac[i]=mul(fac[i-1],i);
		}
		for(int i=n;i>=1;i--){
			apadd(ans,mul(w[i],sub(sum,n-i)));
			apadd(sum,w[i]);
		}
		apmul(ans,mul(fac[n-2],2));
		apadd(ans,mul(fac[n-1],sum));
		printf("%d\n",mul(ans,fpow(fac[n],MOD-2)));
	}else{
		memset(f,0,sizeof(f));
		memset(c,0,sizeof(c));
		fac[0]=f[0]=c[0][0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=mul(fac[i-1],i);
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=add(c[i-1][j-1],c[i-1][j]);
			}
		}
		for(int i=1,j=1;i<=n;i++){
			for(;j<=n&&b[j]<=a[i];j++);
			for(int k=j-1;k;k--){
				apadd(f[k],mul(f[k-1],j-k));
			}
		}
		int ans=0;
		for(int i=n;i>=1;i--){
			g[i]=mul(f[i],fac[n-i]);
			for(int j=i+1;j<=n;j++){
				apsub(g[i],mul(g[j],c[j][i]));
			}
			apadd(ans,mul(g[i],fpow(i,k)));
		}
		printf("%d\n",mul(ans,fpow(fac[n],MOD-2)));
	}
}
