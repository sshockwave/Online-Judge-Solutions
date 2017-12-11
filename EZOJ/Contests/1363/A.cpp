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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=510,O=998244353;
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
int fac[N],invfac[N];
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
int pw1[N],pw2[N];
int a[N][N],f[N][2],g[N];
inline int Main(){
	int n=ni,m=ni;
	gmath(n);
	for(int i=1;i<=n;i++){
		a[i][0]=ni;
		for(int j=1;j<=n-2;j++){
			a[i][j]=(lint)a[i][j-1]*a[i][0]%O;
		}
	}
	for(int j=0;j<=n-2;j++){
		pw1[j]=fpow(j+1,m);
		pw2[j]=(lint)pw1[j]*pw1[j]%O;
	}
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=n-2;j>=0;j--){
			lint F0=f[j][0],F1=f[j][1];
			f[j][0]=f[j][1]=0;
			for(int k=n-2-j;k>=0;k--){
				int tmp=(lint)a[i][k]*pw1[k]%O*invfac[k]%O;
				(f[j+k][0]+=F0*tmp%O)%=O;
				(f[j+k][1]+=F0*a[i][k]%O*pw2[k]%O*invfac[k]%O)%=O;
				(f[j+k][1]+=F1*tmp%O)%=O;
			}
		}
	}
	return (lint)f[n-2][1]*fac[n-2]%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
