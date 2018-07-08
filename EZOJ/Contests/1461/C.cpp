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
const int N=55,C=110,NC=N*C,O=1000000007;
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
namespace gmath{
	const int N=::NC;
	int fac[N],ifac[N],inv[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
			inv[i]=(lint)ifac[i]*fac[i-1]%O;
		}
	}
	inline int C(int n,int k){
		assert(n>=k&&k>=0);
		return (lint)fac[n]*ifac[k]%O*ifac[n-k]%O;
	}
}
int ball[N];
int f[C][C],g[NC],h[C];
inline void dp_f(const int n){
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			int &ans=f[i][j];
			for(int k=1;i-k>=j-1;k++){
				ans=(ans+(lint)f[i-k][j-1]*k)%O;
			}
		}
	}
}
inline void dp_h(const int n){
	assert(n);
	h[0]=0;
	for(int b=1;b<=n;b++){
		int &ans=h[b]=0;
		for(int a=b;a<=n;a++){
			int cur=gmath::C(a-1,b-1);
			if((a-b)&1){
				cur=O-cur;
			}
			ans=(ans+(lint)f[n][a]*cur)%O;
		}
		ans=(lint)ans*gmath::ifac[b]%O;
	}
}
inline void dp_h1(const int n){
	assert(n);
	for(int b=2;b<=n+1;b++){
		int &ans=h[b-2]=0;
		for(int a=b-1;a<=n;a++){
			//virtual a+1 balls
			int cur=gmath::C(a,b-1);
			if((a+1-b)&1){
				cur=O-cur;
			}
			ans=(ans+(lint)f[n][a]*cur%O*gmath::inv[a]%O)%O;
		}
		ans=(lint)ans*gmath::ifac[b-2]%O;
	}
	h[n]=0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
#endif
	const int n=ni;
	int sumc=0,mxc=0;
	for(int i=1;i<=n;i++){
		ball[i]=ni;
		apmax(mxc,ball[i]);
		sumc+=ball[i];
	}
	gmath::main(sumc);
	dp_f(mxc);
	mset(g,0,sumc+1);
	sumc=0;
	g[0]=1;
	for(int i=1;i<=n;i++){
		const int c=ball[i];
		(i==1?dp_h1:dp_h)(c);
		for(int j=sumc;j>=0;j--){//conv
			const lint F=g[j];
			g[j]=0;
			if(F==0)continue;
			for(int k=0;k<=c;k++){
				g[j+k]=(g[j+k]+F*h[k])%O;
			}
		}
		sumc+=c;
	}
	int ans=0;
	for(int j=0;j<=sumc;j++){
		ans=(ans+(lint)gmath::fac[j]*g[j])%O;
	}
	ans=(lint)ans*sumc%O;
	printf("%d\n",ans);
	return 0;
}
