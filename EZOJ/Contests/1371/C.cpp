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
const int N=60010,O=998244353;
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
namespace poly{
	const int SH=18,N=1<<SH;
	int n,sh,invn,mxn=0;
	int o[SH][N>>1],io[SH][N>>1];
	int invnum[N];
	inline void mem(int a[],int i){
		assert(i<=n);
		memset(a+i,0,(n-i)<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
		if(n<=mxn)return invn=invnum[n],void();
		mxn=n;
		invnum[1]=1;
		for(int i=2;i<=n;i++){
			invnum[i]=(lint)(O-O/i)*invnum[O%i]%O;
			assert((lint)invnum[i]*i%O==1);
		}
		invn=invnum[n];
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			int wn=fpow(3,(O-1)/full),iwn=inv(wn);
			for(int j=0,w=1,iw=1;j<half;j++,w=(lint)w*wn%O,iw=(lint)iw*iwn%O){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	int rev[N]={0};
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
			if(rev[i]<i){
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
					a[k+half]=(p-q+O)%O;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
	inline int* inv(const int a[],int n){
		static int *b=new int[N];
		assert(n>0);
		if(n==1){
			b[0]=::inv(a[0]);
			return b;
		}
		inv(a,n>>1);
		static int *tmp=new int[N];
		poly::init(n<<1);
		memcpy(tmp,a,n<<2);
		mem(tmp,n);
		mem(b,n>>1);
		ntt(b),ntt(tmp);
		for(int i=0;i<poly::n;i++){
			b[i]=(O-(lint)b[i]*b[i]%O*tmp[i]%O+(b[i]<<1))%O;
		}
		ntt(b,-1);
		return b;
	}
	inline int* log(const int a[],int n){
		static int *tmp=new int[N];
		memcpy(tmp,inv(a,n),n<<2);
		poly::init(n<<1);
		static int *f=new int[N];
		for(int i=0;i<n-1;i++){
			f[i]=(lint)a[i+1]*(i+1)%O;
		}
		mem(f,n-1),mem(tmp,n);
		ntt(f),ntt(tmp);
		for(int i=0;i<poly::n;i++){
			f[i]=(lint)f[i]*tmp[i]%O;
		}
		ntt(f,-1);
		for(int i=n-1;i>0;i--){
			f[i]=(lint)f[i-1]*invnum[i]%O;
		}
		assert(a[0]==1);
		f[0]=0;//tocheck
		return f;
	}
	inline int* exp(const int a[],int n){
		assert(n>0);
		static int *b=new int[N];
		if(n==1){
			assert(a[0]==0);
			b[0]=1;
			return b;
		}
		static int *tmp=new int[N];
		exp(a,n>>1);
		memset(b+(n>>1),0,(n>>1)<<2);
		int *lg=log(b,n);
		poly::init(n<<1);
		for(int i=0;i<n;i++){
			tmp[i]=(a[i]+O-lg[i])%O;
		}
		assert(tmp[0]==0);
		tmp[0]=1;
		mem(tmp,n),ntt(tmp);
		mem(b,n>>1),ntt(b);
		for(int i=0;i<poly::n;i++){
			b[i]=(lint)b[i]*tmp[i]%O;
		}
		ntt(b,-1);
		assert(b[0]==1);
		return b;
	}
	inline int* fpow(const int a[],int n,int e){
		int c=0;
		for(;c<n&&a[c]==0;c++);
		static int* b=new int[N];
		if(c==n){
			memset(b,0,n<<2);
			b[0]=e==0;
			return b;
		}
		int p=a[c],invp=::inv(p);
		for(int i=c;i<n;i++){
			b[i-c]=(lint)a[i]*invp%O;
		}
		memset(b+n-c,0,c<<2);
		p=::fpow(p,e);
		c*=e;
		memcpy(b,log(b,n),n<<2);
		for(int i=0;i<n;i++){
			b[i]=(lint)b[i]*e%O;
		}
		memcpy(b,exp(b,n),n<<2);
		for(int i=n-1;i>=c;i--){
			b[i]=(lint)b[i-c]*p%O;
		}
		memset(b,0,min(c,n)<<2);
		return b;
	}
}
int cnst;
int a[poly::N],f[poly::N];
inline void solve(int n){
	if(n==1){
		f[0]=0;
		return;
	}
	solve(n>>1);
	using namespace poly;
	static int *up=new int[poly::N];
	static int *down=new int[poly::N];
	static int *ep=new int[poly::N];
	memset(f+(n>>1),0,(n>>1)<<2);
	memcpy(ep,exp(f,n),n<<2);
	if(cnst){
		static int* xc=new int[poly::N];
		static int* tmp=new int[poly::N];
		static int* tmpe=new int[poly::N];
		memcpy(xc,fpow(f,n,cnst-1),n<<2);
		poly::init(n<<1);
		memcpy(tmpe,ep,n<<2);
		mem(tmpe,n),ntt(tmpe);
		mem(xc,n),ntt(xc);
		memcpy(tmp,f,n<<2);
		mem(tmp,n),ntt(tmp);
		for(int i=0;i<poly::n;i++){
			tmp[i]=(lint)tmp[i]*xc[i]%O;
		}
		ntt(tmp,-1);
		mem(tmp,n);
		ntt(tmp);
		for(int i=0;i<poly::n;i++){
			down[i]=(lint)xc[i]*tmpe[i]%O;
			up[i]=(lint)tmp[i]*tmpe[i]%O;
		}
		ntt(up,-1),ntt(down,-1);
		for(int i=0;i<n;i++){
			lint u=up[i],d=down[i];
			up[i]=(u+ep[i]+O-a[i])%O;
			down[i]=(u+cnst*d+ep[i])%O;
		}
	}else for(int i=0;i<n;i++){
		down[i]=(ep[i]<<1)%O;
		up[i]=(down[i]+O-a[i])%O;
	}
	memcpy(down,inv(down,n),n<<2);
	poly::init(n<<1);
	mem(up,n),ntt(up);
	mem(down,n),ntt(down);
	for(int i=0;i<poly::n;i++){
		up[i]=(lint)up[i]*down[i]%O;
	}
	ntt(up,-1);
	for(int i=0;i<n;i++){
		f[i]=(f[i]+O-up[i])%O;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("toy.in","r",stdin);
	freopen("toy.out","w",stdout);
#endif
	int n=ni;
	cnst=ni;
	memset(a,0,sizeof(a));
	a[0]=1+(cnst==0);
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	int _n=1;
	for(;_n<=n;_n<<=1);
	poly::init(_n<<1);
	solve(_n);
	for(int i=1;i<=n;i++){
		printf("%d\n",f[i]);
	}
	return 0;
}
