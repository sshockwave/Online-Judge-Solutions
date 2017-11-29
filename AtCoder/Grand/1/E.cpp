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
const int N=200010,M=4010,O=1000000007;
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
inline int C(int n,int k){
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
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
int x[N],y[N];
int f[M][M];
int main(){
	int n=ni,mx=0,my=0;
	for(int i=1;i<=n;i++){
		apmax(mx,x[i]=ni);
		apmax(my,y[i]=ni);
	}
	//transform:x->mx+x,y->my+y
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		f[mx-x[i]][my-y[i]]++;
	}
	for(int i=0,ti=mx<<1;i<=ti;i++){
		for(int j=0,tj=my<<1;j<=tj;j++){
			if(i)(f[i][j]+=f[i-1][j])%=O;
			if(j)(f[i][j]+=f[i][j-1])%=O;
		}
	}
	gmath((mx+my)<<1);
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=f[x[i]+mx][y[i]+my];
		ans-=C((x[i]+y[i])<<1,x[i]<<1);
	}
	printf("%lld\n",(ans%O+O)%O*inv(2)%O);
	return 0;
}
