#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg&&(c=getchar());
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=500010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_num(int x){
	return fpow(x,O-2);
}
namespace poly{
	const int SH=20,N=1<<SH;
	int n,sh,o[N],r[N];
	inline void clr(int a[],int x){
		mset(a+x,0,n-x);
	}
	inline void cpy(int a[],const int b[],int n){
		memcpy(a,b,n*sizeof(a[0]));
	}
	inline void calc_o(){
		o[0]=1;
		for(int i=1,w=fpow(3,(O-1)>>SH);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	int __initer__=(calc_o(),r[0]=0,0);
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
	}
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int k=0;k<n;k+=full){
				for(int j=k;j<k+half;j++){
					int p=a[j],q=(lint)a[j+half]*o[(j-k)<<(SH-i)]%O;
					a[j]=(p+q)%O;
					a[j+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			lint invn=inv_num(n);
			for(int i=0;i<n;i++){
				a[i]=a[i]*invn%O;
			}
		}
	}
	inline const int* inv(const int a[],int _n){
		init(_n),_n=n;
		static int *b=new int[N],*ta=new int[N];
		mset(b,0,_n<<1);
		mset(ta,0,_n<<1);
		b[0]=inv_num(a[0]);
		for(int i=1,ti=sh;i<=ti;i++){
			int n=1<<i;
			init(n<<1);
			cpy(ta,a,n),ntt(ta);
			ntt(b);
			for(int j=0;j<poly::n;j++){
				b[j]=(O-(lint)ta[j]*b[j]%O*b[j]%O+(b[j]<<1))%O;
			}
			ntt(b,-1);
			mset(b+n,0,n);
		}
		return b;
	}
}
using poly::cpy;
namespace gmath{
	int fac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
	}
}
int t2[poly::N];
int g[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	gmath::main(n);
	for(int i=0;i<=n;i++){
		t2[i]=gmath::fac[i];
	}
	poly::init(n*2+1);
	poly::clr(t2,n+1),poly::ntt(t2);
	for(int i=0;i<poly::n;i++){
		t2[i]=(lint)t2[i]*t2[i]%O;
	}
	poly::ntt(t2,-1);
	memset(g,0,sizeof(g));
	for(int i=0;i<=n;i++){
		g[i]=(t2[i]+O-(lint)i*gmath::fac[i]%O)%O;
	}
	const int *f=poly::inv(g,n+1);
	int ans=0;
	for(int i=0;i<=n;i++){
		ans=(ans+(lint)f[i]*t2[n-i])%O;
	}
	printf("%d\n",ans);
	return 0;
}
