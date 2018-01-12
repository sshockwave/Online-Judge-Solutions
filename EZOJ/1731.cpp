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
const int N=100010,O=950009857;
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
#define arr(x) static int* x=new int[poly::N]
template<class T>inline void cpy(T a[],const T b[],int n){
	memcpy(a,b,n*sizeof(b[0]));
}
namespace poly{
	const int SH=18,N=1<<SH;
	int sh,n,mxn=0,invnum[N]={0,1};
	int o[SH][N>>1],io[SH][N>>1];
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
		if(n<=mxn)return;
		mxn=n;
		for(int i=2;i<=n;i++){
			invnum[i]=(lint)(O-O/i)*invnum[O%i]%O;
			assert((lint)invnum[i]*i%O==1);
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			lint wn=fpow(5,(O-1)/full),iwn=inv(wn);
			for(int j=0,w=1,iw=1;j<half;j++,w=w*wn%O,iw=iw*iwn%O){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	int rev[N]={0};
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
			if(i<rev[i]){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				lint w=(d==1?o:io)[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=w*a[k+half]%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invnum[n]%O;
			}
		}
	}
	const int* inv(const int a[],int n){
		arr(b);arr(ta);
		if(n==1){
			assert(a[0]);
			b[0]=::inv(a[0]);
			return b;
		}
		assert(n>1);
		inv(a,n>>1);
		init(n<<1);
		clr(b,n>>1),ntt(b);
		cpy(ta,a,n),clr(ta,n),ntt(ta);
		for(int i=0;i<poly::n;i++){
			b[i]=(O-(lint)b[i]*b[i]%O*ta[i]%O+(b[i]<<1))%O;
		}
		ntt(b,-1);
		return b;
	}
	inline const int* log(const int a[],int n){
		arr(b);arr(ta);
		assert(a[0]==1);
		cpy(b,inv(a,n),n);
		init(n<<1);
		for(int i=1;i<n;i++){
			ta[i-1]=(lint)i*a[i]%O;
		}
		clr(b,n),ntt(b);
		clr(ta,n-1),ntt(ta);
		for(int i=0;i<poly::n;i++){
			b[i]=(lint)b[i]*ta[i]%O;
		}
		ntt(b,-1);
		for(int i=n-1;i>=1;i--){
			b[i]=(lint)b[i-1]*invnum[i]%O;
		}
		b[0]=0;
		return b;
	}
	const int* exp(const int a[],int n){
		arr(b);arr(c);
		if(n==1){
			assert(a[0]==0);
			b[0]=1;
			return b;
		}
		assert(n>1);
		exp(a,n>>1);
		memset(b+(n>>1),0,(n>>1)<<2);
		const int* lg=log(b,n);
		for(int i=0;i<n;i++){
			c[i]=(a[i]+O-lg[i])%O;
		}
		assert(c[0]==0);
		c[0]=1;
		init(n<<1);
		clr(b,n>>1),ntt(b);
		clr(c,n),ntt(c);
		for(int i=0;i<poly::n;i++){
			b[i]=(lint)b[i]*c[i]%O;
		}
		ntt(b,-1);
		return b;
	}
}
int f[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("big.in","r",stdin);
	freopen("big.out","w",stdout);
#endif
	int n=ni;
	memset(f,0,sizeof(f));
	f[0]=1;
	for(int tot=ni;tot--;){
		f[ni-1]=O-1;
	}
	poly::init((n+1)<<1);
	int sn=poly::n>>1;
	const int* lg=poly::log(f,sn);
	for(int i=0;i<sn;i++){
		f[i]=(lint)lg[i]*(O-n)%O;
	}
	printf("%lld\n",(lint)poly::exp(f,sn)[n-1]*poly::invnum[n]%O);
	return 0;
}
