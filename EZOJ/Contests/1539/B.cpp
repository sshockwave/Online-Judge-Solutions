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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
int O;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
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
namespace getprim{
	const int N=100;
	int pri[N];
	inline int main(){
		int t=O-1;
		int ps=0;
		for(int i=2;i*i<=t;i++){
			if(t%i==0){
				pri[ps++]=i;
				for(;t%i==0;t/=i);
			}
		}
		if(t!=1){
			pri[ps++]=t;
		}
		for(int g=2;;g++){
			bool flag=true;
			for(int i=0;i<ps;i++){
				if(fpow(g,(O-1)/pri[i])==1){
					flag=false;
					break;
				}
			}
			if(flag)return g;
		}
		assert(false);
		return -1;
	}
}
namespace poly{
	const int SH=18,N=1<<SH;
	int o[N],r[N];
	inline void init(){
		o[0]=1,r[0]=0;
		for(int i=1,w=fpow(getprim::main(),(O-1)>>SH);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline void ntt(int a[],int n,int d=1){
		for(int i=1;i<n;i++){
			r[i]=(r[i>>1]>>1)|(i&1?n>>1:0);
			if(r[i]<i){
				swap(a[r[i]],a[i]);
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
			reverse(a+1,a+n);
			int ivn=inv_pow(n);
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
		static int ta[N];
		mset(b,0,n<<1);
		b[0]=inv_pow(a[0]);
		for(int tn=2;tn<=n;tn<<=1){
			mcpy(ta,a,tn),mset(ta+tn,0,tn),ntt(ta,tn<<1);
			ntt(b,tn<<1);
			for(int i=0;i<(tn<<1);i++){
				b[i]=(2-(lint)ta[i]*b[i])%O*b[i]%O;
			}
			ntt(b,tn<<1,-1),mset(b+tn,0,tn);
		}
	}
}
int f[poly::N];
void solve(int n){
	if(n==1){
		f[0]=f[1]=0;
		return;
	}
	solve(n>>1);
	using poly::N;
	using poly::ntt;
	mset(f+n,0,n),ntt(f,n<<1);
	static int pw[5][N];
	{
		static int tf[N];
		for(int j=1;j<=4;j++){
			for(int i=0;i<(n<<1);i++){
				tf[i]=j>1?(lint)tf[i]*f[i]%O:f[i];
			}
			ntt(tf,n<<1,-1);
			mset(tf+n,0,n);
			mcpy(pw[j],tf,n<<1);
			if(j<4){
				ntt(tf,n<<1);
			}
		}
	}
	static int hf[N],h1f[N];
	for(int i=0;i<n;i++){
		hf[i]=(pw[4][i]+2ll*pw[2][i]-pw[1][i])%O;
		if(i>0){
			apadd(hf[i],-pw[1][i-1]);
		}
		if(i==1){
			apadd(hf[i],1);
		}
		h1f[i]=4ll*(pw[3][i]+pw[1][i])%O;
		if(i==0||i==1){
			apadd(h1f[i],-1);
		}
	}
	mset(hf+n,0,n),ntt(hf,n<<1);
	static int ivh[N];
	poly::inv(ivh,h1f,n),ntt(ivh,n<<1);
	for(int i=0;i<(n<<1);i++){
		f[i]=(f[i]-(lint)hf[i]*ivh[i])%O;
	}
	ntt(f,n<<1,-1),mset(f+n,0,n);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int n=ni;
	O=ni;
	poly::init();
	int sn=1;
	for(;sn<=n;sn<<=1);
	solve(sn);
	for(int i=1;i<=n;i++){
		printf("%d\n",f[i]);
	}
	return 0;
}
