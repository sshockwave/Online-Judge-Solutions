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
const int N=1000000010,SH=18,K=1<<SH,MOD=998244353;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
namespace poly{
	const int SH=18,N=1<<SH;
	int n,sh,invn;
	int o[SH+1][N>>1],io[SH+1][N>>1],rev[N];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n),rev[0]=0;
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			int w=1,wn=fpow(3,(MOD-1)/full),iw=1,iwn=inv(wn);
			for(int j=0;j<half;j++,apmul(w,wn),apmul(iw,iwn)){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	inline void ntt(int a[],int d){
		for(int i=0;i<n;i++){
			if(rev[i]<i){
				swap(a[rev[i]],a[i]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				int w=(~d)?o[i][j]:io[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=mul(a[k+half],w);
					a[k]=add(p,q);
					a[k+half]=sub(p,q);
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				apmul(a[i],invn);
			}
		}
	}
	inline void mul(int a[],int b[]){
		ntt(a,1),ntt(b,1);
		for(int i=0;i<n;i++){
			apmul(a[i],b[i]);
		}
		ntt(a,-1);
	}
}
int fac[K],invfac[K];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=mul(fac[i-1],i);
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=mul(invfac[i],i);
	}
}
int a[K],b[K];
int main(){
#ifndef ONLINE_JUDGE
	freopen("value.in","r",stdin);
	freopen("value.out","w",stdout);
#endif
	int n=ni-1,k=ni;
	gmath(k);
	poly::init(k*2+1);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	for(int i=0;i<=k;i++){
		a[i]=mul(fpow(MOD-1,i),invfac[i]);
		b[i]=mul(fpow(i,k),invfac[i]);
	}
	poly::mul(a,b);
	lint ans=0;
	for(int i=0,c=1,ti=min(n,k);i<=ti;apmul(c,n-i),i++){
		ans+=mul(a[i],mul(c,fpow(2,n-i)));
	}
	n++;
	printf("%d\n",mul(ans%MOD,mul(n,fpow(2,(lint)(n-1)*(n-2)/2%(MOD-1)))));
	return 0;
}
