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
const int N=2000010,O=1000000007;
int fac[N],invfac[N];
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
inline int F(int x,int y){
	return (lint)fac[x+y]*invfac[x]%O*invfac[y]%O;
}
int x3,y3,x4,y4;
inline int solve(int sx,int sy,int tx,int ty){
	lint ans=0;
	for(int i=x3;i<=x4;i++){//enter from bottom && out from top
		ans-=(lint)F(i-sx,y3-1-sy)*F(tx-i,ty-y3)%O*(i+y3)%O;
		ans+=(lint)F(i-sx,y4-sy)*F(tx-i,ty-y4-1)%O*(i+y4+1)%O;
	}
	for(int j=y3;j<=y4;j++){//enter from left && out from top
		ans-=(lint)F(x3-1-sx,j-sy)*F(tx-x3,ty-j)%O*(x3+j)%O;
		ans+=(lint)F(x4-sx,j-sy)*F(tx-x4-1,ty-j)%O*(x4+j+1)%O;
	}
	return (ans%O+O)%O;
}
int main(){
	int sx[2],sy[2],tx[2],ty[2];
	sx[0]=ni-1,sx[1]=ni,x3=ni,x4=ni,tx[1]=ni,tx[0]=ni+1;
	sy[0]=ni-1,sy[1]=ni,y3=ni,y4=ni,ty[1]=ni,ty[0]=ni+1;
	gmath(tx[0]+ty[0]);
	lint ans=0;
	for(int a=0;a<2;a++){
		for(int b=0;b<2;b++){
			for(int c=0;c<2;c++){
				for(int d=0;d<2;d++){
					int sig=(a^b^c^d)?-1:1;
					ans+=sig*solve(sx[a],sy[b],tx[c],ty[d]);
				}
			}
		}
	}
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
