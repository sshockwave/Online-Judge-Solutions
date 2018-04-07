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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int O=998244353;
inline int fpow(int x,lint n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int minv(int x){
	assert(x);
	return fpow(x,O-2);
}
namespace poly{
	const int SH=19,N=1<<SH;
	namespace gmath{
		int invnum[N];
		inline void main(int n){
			invnum[1]=1;
			for(int i=2;i<=n;i++){
				invnum[i]=O-(lint)O/i*invnum[O%i]%O;
			}
		}
	}
	int r[N],o[N];
	inline void init(){
		gmath::main(N-1);
		o[0]=1;
		for(int i=1,w=fpow(3,(O-1)>>SH);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline void clr(int a[],const int n,const int x=0){
		memset(a+x,0,(n-x)<<2);
	}
	inline void cpy(int a[],const int b[],int n){
		memcpy(a,b,n<<2);
	}
	inline int lb(int n){
		int sh=0;
		for(;(1<<sh)<n;sh++);
		return sh;
	}
	int polyn;
	inline void ntt(int a[],const int n,const int d=1){
		assert(n==(n&-n));
		const int sh=lb(polyn=n);
		for(int i=1;i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			int wn=o[1<<(SH-i)];
			for(int k=0;k<n;k+=full){
				lint w=1;
				for(int j=k,tj=k+half;j<tj;j++,w=w*wn%O){
					int p=a[j],q=a[j+half]*w%O;
					a[j]=(p+q)%O;
					a[j+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			const int invn=minv(n);
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
	const int* inv(const int a[],const int n){
		static int b[N],c[N];
		assert(n==(n&-n));
		if(n==1)return b[0]=minv(a[0]),b;
		inv(a,n>>1);
		clr(b,n<<1,n>>1),ntt(b,n<<1);
		cpy(c,a,n),clr(c,n<<1,n),ntt(c,n<<1);
		for(int i=0;i<polyn;i++){
			b[i]=(O-(lint)c[i]*b[i]%O*b[i]%O+(b[i]<<1))%O;
		}
		ntt(b,n<<1,-1);
		return b;
	}
	const int* log(const int a[],const int n){
		assert(a[0]==1);
		assert(n==(n&-n));
		static int b[N],c[N];
		for(int i=1;i<n;i++){
			b[i-1]=(lint)a[i]*i%O;
		}
		clr(b,n<<1,n-1),ntt(b,n<<1);
		cpy(c,inv(a,n),n),clr(c,n<<1,n),ntt(c,n<<1);
		for(int i=0;i<polyn;i++){
			b[i]=(lint)b[i]*c[i]%O;
		}
		ntt(b,n<<1,-1);
		for(int i=n-1;i>=1;i--){
			b[i]=(lint)b[i-1]*gmath::invnum[i]%O;
		}
		b[0]=0;
		return b;
	}
	const int* exp(const int a[],const int n){
		static int b[N],c[N];
		assert(n==(n&-n));
		if(n==1){
			assert(a[0]==0);
			b[0]=1;
			return b;
		}
		exp(a,n>>1);
		clr(b,n<<1,n>>1);
		const int* ln=log(b,n);
		ntt(b,n<<1);
		for(int i=0;i<n;i++){
			c[i]=(a[i]+O-ln[i])%O;;
		}
		assert(c[0]==0);
		c[0]=1,clr(c,n<<1,n),ntt(c,n<<1);
		for(int i=0;i<polyn;i++){
			b[i]=(lint)b[i]*c[i]%O;
		}
		ntt(b,n<<1,-1);
		return b;
	}
	const int* gpw(const int a[],const int n,const int e){
		assert(a[0]==1);
		assert(n==(n&-n));
		static int b[N];
		cpy(b,log(a,n),n);
		for(int i=0;i<n;i++){
			b[i]=(lint)b[i]*e%O;
		}
		return exp(b,n);
	}
}
namespace getg{
	using poly::N;
	int g[N],a[N],b[N];
	namespace gmath{
		int fac[N],invfac[N];
		inline void main(int n){
			fac[0]=1;
			for(int i=1;i<=n;i++){
				fac[i]=(lint)fac[i-1]*i%O;
			}
			invfac[n]=minv(fac[n]);
			for(int i=n;i>=1;i--){
				invfac[i-1]=(lint)invfac[i]*i%O;
			}
		}
	}
	inline void main(int n){
		assert(sizeof(g)==poly::N*4);
		n=1<<poly::lb(n+1);
		a[0]=0,b[0]=1;
		gmath::main(n);
		for(int i=1;i<n;i++){
			lint tmp=fpow(2,(lint)i*(i-1)/2);
			a[i]=tmp*gmath::invfac[i-1]%O;
			b[i]=tmp*gmath::invfac[i]%O;
		}
		using namespace poly;
		clr(a,n<<1,n),ntt(a,n<<1);
		cpy(b,inv(b,n),n),clr(b,n<<1,n),ntt(b,n<<1);
		for(int i=0;i<polyn;i++){
			g[i]=(lint)a[i]*b[i]%O;
		}
		ntt(g,n<<1,-1);
	}
}
namespace getb{
	using poly::N;
	const int *g=getg::g;
	int a[N],d[N];
	inline void init(int n){
		n=1<<poly::lb(n);
		for(int i=0;i<=n;i++){
			a[i]=g[i+1];
		}
		const int *ln=poly::log(a,n<<1);
		for(int i=1;i<=n;i++){
			d[i-1]=(lint)ln[i]*i%O;
		}
	}
	int tmpa[N],tmpb[N];
	inline int main(int _n){
		using namespace poly;
		int n=1<<lb(_n);
		cpy(tmpa,poly::gpw(a,n,O-_n),n),clr(tmpa,n<<1,n),ntt(tmpa,n<<1);
		cpy(tmpb,d,n),clr(tmpb,n<<1,n),ntt(tmpb,n<<1);
		for(int i=0;i<polyn;i++){
			tmpa[i]=(lint)tmpa[i]*tmpb[i]%O;
		}
		ntt(tmpa,n<<1,-1);
		return (lint)tmpa[_n-1]*poly::gmath::invnum[_n]%O;
	}
}
int b[poly::N];
inline int Main(){
	int n=ni;
	poly::init(),getg::main(n+1),getb::init(n);
	for(int tot=ni;tot--;){
		int x=ni-1;
		if(x==0)continue;
		b[x]=(lint)getb::main(x)*n%O;
	}
	lint ans=(lint)poly::exp(b,1<<poly::lb(n))[n-1]*poly::gmath::invnum[n]%O;//inversion
	ans=ans*getg::gmath::fac[n]%O;//EGF
	ans=ans*poly::gmath::invnum[n]%O;//no root
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
