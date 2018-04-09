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
const int N=100010,O=998244353;
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
namespace gmath{
	int fac[N],invfac[N];
	inline void Main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
}
namespace poly{
	const int SH=18,N=1<<18;
	int sh,n,invn,pw[N],rev[N];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		pw[0]=1,rev[0]=0;
		lint wn=fpow(3,(O-1)/n);
		for(int i=1;i<n;i++){
			pw[i]=pw[i-1]*wn%O;
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
	}
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			if(i<rev[i]){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				lint w=pw[j<<(sh-i)];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=w*a[k+half]%O;
					a[k]=(p+q)%O;
					a[k+half]=(lint)(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
int f[poly::N],g[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
#endif
	int n=ni,m=ni;
	gmath::Main(m+1);
	for(int i=0;i<=m;i++){
		using gmath::invfac;
		f[i]=(lint)fpow(i,m)*invfac[i]%O;
		g[i]=i&1?O-invfac[i]:invfac[i];
	}
	using poly::ntt;
	poly::init(m*2+1),ntt(f),ntt(g);
	for(int i=0;i<poly::n;i++){
		f[i]=(lint)f[i]*g[i]%O;
	}
	ntt(f,-1);
	lint ans=0,c=1;
	for(int i=n+1;i>n-m;i--){
		c=c*i%O;
	}
	c=c*gmath::invfac[m+1]%O;
	for(int j=0;j<=m;j++){
		ans+=c*gmath::fac[j]%O*f[j]%O;
		c=c*inv(m+j+2)%O*(n-m-j)%O;
		if(c==0)break;
	}
	printf("%lld\n",ans%O);
	return 0;
}
