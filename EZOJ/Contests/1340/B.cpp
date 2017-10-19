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
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=2010,O=1000000007;
inline int fpow(lint x,int n){
	int a=1;
	for(;n;n>>=1,x=x*x%O){
		if(n&1){
			a=a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int fac[N*N],invfac[N*N];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
inline int C(int n,int m){
	if(n<m){
		return 0;
	}
	return (lint)fac[n]*invfac[m]%O*invfac[n-m]%O;
}
lint f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
#endif
	int n=ni,k=ni;
	if(k<=1){
		puts("1");
		return 0;
	}
	gmath(n*k);
	memset(f,0,sizeof(f));
	f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i;j>=0;j--){
			f[j]=f[j+1];
			if(j){
				(f[j]+=(lint)f[j-1]*C((i-1)*(k-1)+(i-j)+(k-2),k-2)%O*(n-i+1))%=O;
			}
		}
	}
	printf("%lld\n",f[0]);
	return 0;
}
