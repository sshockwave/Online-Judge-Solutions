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
const int SH=18,N=1<<SH,O=998244353;
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
#define arr(x) static int* x=new int[N]
namespace poly{
	int sh,n,mxn=0,invnum[N];
	int o[SH][N>>1],io[SH][N>>1];
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)<<2);
	}
	inline void cpy(int a[],const int b[],int n){
		memcpy(a,b,n<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
		if(n<=mxn)return;
		mxn=n;
		invnum[1]=1;
		for(int i=2;i<=n;i++){
			invnum[i]=(lint)(O-O/i)*invnum[O%i]%O;
			assert((lint)invnum[i]*i%O==1);
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			lint wn=fpow(3,(O-1)/full),iwn=inv(wn);
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
			b[i]=(O-(lint)ta[i]*b[i]%O*b[i]%O+(b[i]<<1))%O;
		}
		ntt(b,-1);
		return b;
	}
	inline const int* log(const int a[],int n){
		arr(b);arr(c);
		assert(a[0]==1);
		cpy(c,inv(a,n),n);
		for(int i=1;i<n;i++){
			b[i-1]=(lint)a[i]*i%O;
		}
		init(n<<1);
		clr(b,n-1),ntt(b);
		clr(c,n),ntt(c);
		for(int i=0;i<poly::n;i++){
			b[i]=(lint)b[i]*c[i]%O;
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
		assert(b[0]==1);
		const int* lg=log(b,n);
		init(n<<1);
		clr(b,n),ntt(b);
		for(int i=0;i<n;i++){
			c[i]=(a[i]+O-lg[i])%O;
		}
		assert(c[0]==0);
		c[0]=1;
		clr(c,n),ntt(c);
		for(int i=0;i<poly::n;i++){
			b[i]=(lint)b[i]*c[i]%O;
		}
		ntt(b,-1);
		return b;
	}
	const int* fpow(const int a[],int n,int e){
		assert(a[0]==1);//this task
		arr(b);
		cpy(b,log(a,n),n);
		for(int i=0;i<n;i++){
			b[i]=(lint)b[i]*e%O;
		}
		return exp(b,n);
	}
}
int a[N],f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
#endif
	int n=ni,m=ni;
	int mlen=min(n,m);
	poly::init((mlen<<1)+1);
	int sn=poly::n>>1;
	memset(a,0,sizeof(a));
	a[0]=1,a[1]=6,a[2]=1;
	poly::cpy(a,poly::fpow(a,sn,inv(2)),sn);
	poly::cpy(f,a,sn);
	f[0]=(f[0]+1)%O,f[1]=(f[1]+1)%O;
	for(int i=0;i<sn;i++){
		const static int inv2=inv(2);
		f[i]=(lint)f[i]*inv2%O;
	}
	poly::cpy(f,poly::fpow(f,sn,n+1),sn);
	poly::cpy(a,poly::inv(a,sn),sn);
	poly::init(sn<<1);
	poly::clr(a,sn),poly::ntt(a);
	poly::clr(f,sn),poly::ntt(f);
	for(int i=0;i<poly::n;i++){
		f[i]=(lint)f[i]*a[i]%O;
	}
	poly::ntt(f,-1);
	for(int i=1;i<=mlen;i++){
		printf("%d ",f[i]);
	}
	for(int i=mlen+1;i<=m;i++){
		putchar('0'),putchar(' ');
	}
	putchar('\n');
	return 0;
}
