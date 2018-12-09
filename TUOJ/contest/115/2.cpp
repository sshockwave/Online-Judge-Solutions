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
const int N=200010,A=110,O=998244353;
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
	const int N=::N<<1;
	int fac[N],ifac[N];
	inline void init(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		if(k>n)return 0;
		return (lint)fac[n]*ifac[k]%O*ifac[n-k]%O;
	}
}
namespace poly{
	const int SH=19,N=1<<SH;
	int o[N],*so[SH+1],r[N];
	int sn[N],iv[N+1];
	inline void init(){
		o[0]=1,r[0]=0;
		sn[0]=1;
		for(int i=1,w=fpow(3,(O-1)/N);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
			for(sn[i]=sn[i-1];sn[i]<i;sn[i]<<=1);
		}
		for(int i=0;i<=SH;i++){
			const int n=1<<i,h=n>>1;
			iv[n]=inv_pow(n);
			so[i]=new int[h];
			for(int j=0;j<h;j++){
				so[i][j]=o[j<<(SH-i)];
			}
		}
	}
	inline void ntt(int a[],int n,int d=1){
		assert((n&-n)==n);
		for(int i=0;i<n;i++){
			r[i]=(r[i>>1]>>1)|(i&1?n>>1:0);
			if(i<r[i]){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;(1<<i)<=n;i++){
			int full=1<<i,half=full>>1;
			const int * const w=so[i];
			for(int k=0;k<n;k+=full){
				for(int j=k;j<k+half;j++){
					const int p=a[j];
					lint q=(lint)a[j+half]*w[j-k];
					a[j]=(p+q)%O;
					a[j+half]=(p-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			const lint w=iv[n];
			for(int i=0;i<n;i++){
				a[i]=a[i]*w%O;
			}
		}
	}
	inline void pmul(int a[],const int b[],int n){
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*b[i]%O;
		}
	}
}
int a[N];
using gmath::fac;
using gmath::ifac;
using gmath::C;
inline int sig1(int n){
	return n&1?-1:1;
}
inline void getg(int ansg[],int n){
	const int sn=poly::sn[(n<<1)|1];
	static int f[poly::N],g[poly::N];
	mset(f,0,sn),mset(g,0,sn);
	g[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=C(n+i-1,i*2-1);
		f[i]=(lint)f[i]*fac[i-1]%O;
		g[sn-i]=ifac[i]*sig1(i);
	}
	using poly::ntt;
	ntt(f,sn),ntt(g,sn),poly::pmul(g,f,sn),ntt(g,sn,-1);
	ansg[0]=0;
	for(int i=1;i<=n;i++){
		ansg[i]=(lint)g[i]*ifac[i-1]%O*ifac[i]%O;
	}
}
inline void getg2(int ansg[],int n){
	static int f[poly::N],g[poly::N];
	const int sn=poly::sn[(n<<1)|1];
	mset(f,0,sn),mset(g,0,sn);
	g[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=(C(n+i-1,i*2-1)+2ll*C(n+i-1,i*2))%O;
		f[i]=(lint)f[i]*fac[i]%O;
		g[sn-i]=ifac[i]*sig1(i);
	}
	using poly::ntt;
	ntt(f,sn),ntt(g,sn),poly::pmul(g,f,sn),ntt(g,sn,-1);
	for(int i=1;i<=n;i++){
		ansg[i-1]=(lint)g[i]*ifac[i]%O*ifac[i-1]%O;
	}
}
int solve(const int l,const int r,int pool[]){
	if(l==r){
		const int v=a[l];
		getg2(pool,v);
		getg(pool+v,v);
		return v;
	}
	int *const ans=pool;
	const int m=(l+r)>>1;
	const int lsum=solve(l,m,pool);
	const int *pa=pool,*pb=pool+=lsum;
	const int rsum=solve(m+1,r,pool+=lsum+1);
	const int *pc=pool,*pd=pool+=rsum;
	const int sum=lsum+rsum;
	const int sn=poly::sn[sum+1];
	static int ta[poly::N],tb[poly::N],tc[poly::N],td[poly::N];
	mset(ta,0,sn),mcpy(ta,pa,lsum),poly::ntt(ta,sn);
	mset(tb,0,sn),mcpy(tb,pb,lsum+1),poly::ntt(tb,sn);
	mset(tc,0,sn),mcpy(tc,pc,rsum),poly::ntt(tc,sn);
	mset(td,0,sn),mcpy(td,pd,rsum+1),poly::ntt(td,sn);
	for(int i=0;i<sn;i++){
		ta[i]=((lint)ta[i]*td[i]+(lint)tb[i]*tc[i])%O;
		tb[i]=(lint)tb[i]*td[i]%O;
	}
	poly::ntt(ta,sn,-1),mcpy(ans,ta,sum);
	poly::ntt(tb,sn,-1),mcpy(ans+sum,tb,sum+1);
	return sum;
}
int pool[N*6];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	int n=ni;
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i]=ni;
		if(a[i]==0){
			i--,n--;
		}
	}
	gmath::init(sum*2);
	poly::init();
	solve(1,n,pool);
	int ans=0;
	for(int i=0;i<sum;i++){
		ans=(ans+(lint)pool[i]*fac[i])%O;
	}
	printf("%d\n",ans<0?ans+O:ans);
	return 0;
}
