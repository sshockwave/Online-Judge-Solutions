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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=130010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)x*a%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace poly{
	const int SH=18,N=1<<SH;
	int n,sh;
	int o[SH][N>>1],io[SH][N>>1];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			int w=1,iw=1,wn=fpow(3,(O-1)/full),iwn=inv(wn);
			for(int j=0;j<half;j++,w=(lint)w*wn%O,iw=(lint)iw*iwn%O){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	int rev[N];
	inline void ntt(int a[],int s=sh,int d=1){
		int n=1<<s;
		for(int i=0;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(s-1));
			if(rev[i]<i){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=0;i<s;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				int w=(d==1?o:io)[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=(lint)a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p-q+O)%O;
				}
			}
		}
		if(d==-1){
			int invn=inv(n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
	int tmp[N],b[N];
	inline void inv(int a[],int s=sh-1){
		if(s==0){
			memcpy(tmp,a,n<<2);
			memset(a,0,n<<2);
			memset(b,0,n<<2);
			a[0]=::inv(tmp[0]);
			return;
		}
		int n=1<<s;
		inv(a,s-1);
		memcpy(b,tmp,n<<2);
		ntt(a,s+1),ntt(b,s+1);
		for(int i=0;i<(n<<1);i++){
			a[i]=(((lint)a[i]<<1)%O+O-(lint)b[i]*a[i]%O*a[i]%O)%O;
		}
		ntt(a,s+1,-1);
		memset(a+n,0,n<<2);
	}
}
int fac[N],invfac[N];
inline int C(int n,int k){
	assert(n>=k);
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
		assert((lint)invfac[i]*fac[i]%O==1);
	}
}
int a[poly::N],b[poly::N];
inline void getfrac(int a[],int n){
	memset(a,0,poly::n<<2);
	for(int i=0;i<=n-i;i++){
		a[i]=C(n-i,i);
		if(i&1){
			a[i]=(O-a[i])%O;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("comb.in","r",stdin);
	freopen("comb.out","w",stdout);
#endif
	int ldep=ni-2,n=ni;
	if(ldep<0){
		for(int i=1;i<=n;i++){
			puts("0");
		}
		return 0;
	}
	gmath(max(ldep,n));
	poly::init((n<<1)-1);
	memset(a,0,sizeof(a));
	getfrac(a,ldep);
	getfrac(b,ldep+1);
	poly::inv(b);
	poly::ntt(a),poly::ntt(b);
	for(int i=0;i<poly::n;i++){
		a[i]=(lint)a[i]*b[i]%O;
	}
	poly::ntt(a,poly::sh,-1);
	for(int i=0;i<n;i++){
		printf("%d\n",a[i]);
	}
	return 0;
}
