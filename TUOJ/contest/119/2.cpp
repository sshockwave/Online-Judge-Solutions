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
const int O=998244353;
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
	const int SH=19,N=1<<SH;
	int o[SH][N>>1],w[N],r[N],invnum[N+1];
	inline void init(){
		w[0]=1,r[0]=0;
		for(int i=1,g=fpow(3,(O-1)>>SH);i<N;i++){
			w[i]=(lint)w[i-1]*g%O;
		}
		for(int i=0;i<SH;i++){
			int half=1<<i;
			for(int j=0;j<half;j++){
				o[i][j]=w[j<<(SH-i-1)];
			}
		}
		invnum[1]=1;
		for(int i=2;i<=N;i++){
			invnum[i]=(lint)(O-invnum[O%i])*(O/i)%O;
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
		for(int i=0;(1<<i)<n;i++){
			const int *const w=o[i];
			const int half=1<<i,full=half<<1;
			for(int k=0;k<n;k+=full){
				for(int j=k;j<k+half;j++){
					int p=a[j],q=(lint)a[j+half]*w[j-k]%O;
					a[j]=(p+q)%O;
					a[j+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			const int invn=invnum[n];
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
			reverse(a+1,a+n);
		}
	}
	inline void inv(const int a[],int b[],int _n){
		static int ta[N];
		assert(_n==(_n&-_n));
		assert(a!=b);
		mset(b,0,_n<<1);
		b[0]=a[0]!=1?inv_pow(a[0]):1;
		for(int n=2;n<=_n;n<<=1){
			const int n2=n<<1;
			mcpy(ta,a,n),mset(ta+n,0,n),ntt(ta,n2);
			ntt(b,n2);
			for(int i=0;i<n2;i++){
				b[i]=((lint)(O-ta[i])*b[i]%O+2)*b[i]%O;
			}
			ntt(b,n2,-1),mset(b+n,0,n);
		}
	}
	inline void derv(const int a[],int b[],int n){
		for(int i=1;i<n;i++){
			b[i-1]=(lint)a[i]*i%O;
		}
		b[n-1]=0;
	}
	inline void intg(const int a[],int b[],int n){
		for(int i=n-1;i>=1;i--){
			b[i]=(lint)a[i-1]*invnum[i]%O;
		}
		b[0]=0;
	}
	inline void pmul(int a[],int b[],const int n){
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*b[i]%O;
		}
	}
	inline void log(const int a[],int b[],const int n){
		static int ta[N];
		const int n2=n<<1;
		assert(n==(n&-n));
		assert(a[0]==1);
		derv(a,ta,n),mset(ta+n,0,n),ntt(ta,n2);
		inv(a,b,n),ntt(b,n2),pmul(b,ta,n2),ntt(b,n2,-1),intg(b,b,n),mset(b+n,0,n);
	}
	inline void exp(const int a[],int b[],const int _n){
		static int ta[N];
		assert(_n==(_n&-_n));
		assert(a!=b);
		assert(a[0]==0);
		mset(b,0,_n<<1),b[0]=1;
		for(int n=2;n<=_n;n<<=1){
			const int n2=n<<1;
			log(b,ta,n);
			for(int i=0;i<n;i++){
				ta[i]=(a[i]+O-ta[i])%O;
			}
			ta[0]=(ta[0]+1)%O,ntt(ta,n2);
			ntt(b,n2),pmul(b,ta,n2),ntt(b,n2,-1),mset(b+n,0,n);
		}
	}
}
using poly::N;
int a[N],b[N],f[N];
void solve(const int n){
	if(n==1){
		f[0]=0;
		return;
	}
	const int n2=n<<1;
	solve(n>>1);
	static int ta[N],h[N],c[N];
	using namespace poly;
	//h=exp(f0)*a
	exp(f,h,n),ntt(h,n2);
	mcpy(ta,a,n),mset(ta+n,0,n),ntt(ta,n2);
	pmul(h,ta,n2),ntt(h,n2,-1),mset(h+n,0,n);
	//c=b-(f0-1)*h
	mcpy(ta,f,n2),ta[0]=(ta[0]+O-1)%O,ntt(ta,n2);
	mcpy(c,h,n2),ntt(c,n2),pmul(c,ta,n2),ntt(c,n2,-1),mset(c+n,0,n);
	for(int i=0;i<n;i++){
		c[i]=(b[i]+O-c[i])%O;
	}
	//f=exp(intg(h)),h=inv(f)
	intg(h,h,n),exp(h,f,n),inv(f,h,n);
	//c*=h
	ntt(c,n2),ntt(h,n2),pmul(c,h,n2),ntt(c,n2,-1),mset(c+n,0,n);
	//f=f*intg(c)
	intg(c,c,n),ntt(c,n2),ntt(f,n2),pmul(f,c,n2),ntt(f,n2,-1),mset(f+n,0,n);
}
namespace gmath{
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
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	poly::init();
	const int n=ni;
	int tot1=ni,tot2=ni;
	for(;tot1--;a[ni]=1);
	for(;tot2--;b[ni]=1);
	gmath::main(n);
	b[0]=0;
	for(int i=0;i<n;i++){
		b[i]=(lint)(b[i]+O-a[i])*gmath::ifac[i]%O;
		a[i]=(lint)a[i]*gmath::ifac[i]%O;
	}
	int sn=1;
	for(;sn<=n;sn<<=1);
	solve(sn);
	assert(f[1]==0);
	f[1]=1;
	printf("%lld\n",(lint)f[n]*gmath::fac[n]%O);
	return 0;
}
