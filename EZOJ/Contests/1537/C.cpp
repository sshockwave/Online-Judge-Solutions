#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
//const int N=50010,K=16,O=998244353;
const int K=16,O=998244353;
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
namespace poly{
	const int SH=18,N=1<<SH;
	int o[N],r[N];
	inline void init(){
		o[0]=1,r[0]=0;
		for(int i=1,w=fpow(3,(O-1)>>SH);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline void ntt(int a[],int n,int d=1){
		assert(n==(n&-n));
		for(int i=1;i<n;i++){
			r[i]=(r[i>>1]>>1)|(i&1?n>>1:0);
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;(1<<i)<=n;i++){
			int full=1<<i,half=full>>1;
			for(int k=0;k<n;k+=full){
				for(int j=k;j<k+half;j++){
					int p=a[j];
					lint q=(lint)a[j+half]*o[(j-k)<<(SH-i)];
					a[j]=(p+q)%O;
					a[j+half]=(p-q)%O;
				}
			}
		}
		if(d==-1){
			int ivn=inv_pow(n);
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)(a[i]+O)*ivn%O;
			}
		}
	}
	inline void pmul(int a[],const int b[],int n){
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*b[i]%O;
		}
	}
	inline void inv(int b[],const int a[],int n){
		mset(b,0,n<<1);
		b[0]=inv_pow(a[0]);
		for(int tn=2;tn<=n;tn<<=1){
			static int ta[N];
			mcpy(ta,a,tn),mset(ta+tn,0,tn),ntt(ta,tn<<1);
			ntt(b,tn<<1);
			for(int i=0;i<(tn<<1);i++){
				b[i]=(2-(lint)ta[i]*b[i])%O*b[i]%O;
			}
			ntt(b,tn<<1,-1);
			mset(b+tn,0,tn);
		}
	}
}
using poly::ntt;
namespace gmath{
	const int N=poly::N;
	int fac[N],ifac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
		}
	}
}
int g[K][poly::N];
inline void getg(int n,int k){
	const int iv2=inv_pow(2);
	for(int i=0;i<=n;i++){
		const int n2=(lint)i*(i-1)/2%O;
		int j=0;
		int c=fpow(2,(lint)i*(i-1)/2%(O-1));
		for(;j<=n2&&j<=k;j++){
			g[j][i]=c;
			c=(lint)c*(n2-j)%O*inv_pow(j+1)%O*iv2%O;
		}
		for(;j<=k;j++){
			g[j][i]=0;
		}
	}
}
int h[poly::N];
inline void geth(int n){
	static int ta[poly::N];
	for(int i=0;i<n;i++){
		ta[i]=(lint)g[0][i]*gmath::ifac[i]%O;
	}
	poly::inv(h,ta,n);
	ntt(h,n<<1);
}
int stir[K];
inline void getstir(int n){
	stir[0]=1,mset(stir+1,0,n);
	for(int i=1;i<=n;i++){
		for(int j=i;j>=1;j--){
			stir[j]=(stir[j-1]+(lint)stir[j]*j)%O;
		}
		stir[0]=0;
	}
}
int f[K][poly::N],tg[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	poly::init();
	const int n=ni,k=ni;
	int sn=1;
	for(;sn<=n;sn<<=1);
	gmath::main(max(sn,k));
	getg(sn,k);
	geth(sn);
	getstir(k);
	int ans=0;
	for(int p=0;p<=k;p++){
		for(int i=0;i<sn;i++){
			if(i){
				tg[i]=(lint)g[p][i]*gmath::ifac[i-1]%O;
			}else{
				tg[i]=0;
			}
			g[p][i]=(lint)g[p][i]*gmath::ifac[i]%O;
		}
		mset(g[p]+sn,0,sn),ntt(g[p],sn<<1);
		for(int i=0;i<(sn<<1);i++){
			int &ans=f[p][i]=0;
			for(int a=0;a<p;a++){
				ans=(ans+(lint)f[a][i]*g[p-a][i])%O;
			}
		}
		ntt(f[p],sn<<1,-1);
		for(int i=0;i<sn;i++){
			f[p][i]=(tg[i]-f[p][i])%O;
		}
		mset(f[p]+sn,0,sn),ntt(f[p],sn<<1);
		poly::pmul(f[p],h,sn<<1);
		ntt(f[p],sn<<1,-1);
		ans=(ans+(lint)stir[p]*((lint)f[p][n]*gmath::fac[n-1]%O)%O*gmath::fac[p])%O;
		mset(f[p]+sn,0,sn);
		ntt(f[p],sn<<1);
	}
	printf("%d\n",ans);
	return 0;
}
