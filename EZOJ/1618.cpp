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
const int SH=20,N=1<<SH,MOD=998244353;
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
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
inline int inv(const int &x){
	return fpow(x,MOD-2);
}
int a[N],b[N];
namespace dft{
	int sh,n,invn;
	int o[SH+1][N>>1],io[SH+1][N>>1];
	int rev[N];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			int w=1,iw=1,wn=fpow(3,(MOD-1)/full),iwn=inv(wn);
			for(int j=0;j<half;j++,apmul(w,wn),apmul(iw,iwn)){
				o[i][j]=w,io[i][j]=iw;
			}
		}
		rev[0]=0;
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
	}
	inline void ntt(int a[],int d){
		for(int i=0;i<n;i++){
			if(i<rev[i]){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				int w=(d==1?o:io)[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=mul(a[k+half],w);
					a[k]=add(p,q),a[k+half]=sub(p,q);
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				apmul(a[i],invn);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("multiply.in","r",stdin);
	freopen("multiply.out","w",stdout);
#endif
	int n=ni+1,m=ni+1;
	ni;
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	for(int i=0;i<m;i++){
		b[i]=ni;
	}
	dft::init(n+m-1);
	dft::ntt(a,1),dft::ntt(b,1);
	for(int i=0;i<dft::n;i++){
		apmul(a[i],b[i]);
	}
	dft::ntt(a,-1);
	for(int i=0;i<n+m-1;i++){
		printf("%d ",a[i]);
	}
	putchar('\n');
}
