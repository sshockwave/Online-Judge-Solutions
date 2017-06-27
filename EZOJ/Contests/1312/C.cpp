#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=1000010,MOD=998244353;
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
int fac[N],invfac[N];
inline int c(int n,int k){
	if(k>n){
		return 0;
	}
	return mul(fac[n],mul(invfac[k],invfac[n-k]));
}
inline int intcnt(int l1,int r1,int l2,int r2){
	return max(0,min(r1,r2)-max(l1,l2)+1);
}
inline int work(int n,int k){
	int ans=0,m=(n+1)>>1;
	apadd(ans,sub(c(n-1,k-1),c(n-3,k-1)));//000 & 100 & 001
	for(int t=n-3;t>=2;t-=2){//00 00
		apadd(ans,mul(intcnt(2,m-1,m+1-t,n-1-t),c(n-t-3,k-t/2-3)));
	}
	{//00 11
		int cur=0;
		for(int t=n-4;t>=3;t-=2){
			apadd(ans,mul(intcnt(3,m-1,(n-t)/2+1,n-1-t),c(n-t-3,k-(t+1)/2-1)));
		}
		apadd(ans,mul(cur,2));
	}
	{//00 
		int cur=0;
		for(int i=2;i<m;i++){
			apadd(cur,c(i-2,k-(n-i)/2-2));
		}
		apadd(ans,mul(cur,2));
	}
	if(k==n-k+1){//101
		apadd(ans,1);
	}
	apmul(ans,mul(fac[k],fac[n-k]));
	return ans;
}
int main(){
	int n=ni,k=ni;
	{//get fac
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=mul(fac[i-1],i);
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=mul(invfac[i],i);
		}
	}
	if(n==1){
		puts("1");
	}else if(k==1||k==n){
		puts("0");
	}else{
		printf("%d\n",sub(work(n,k),work(n,k-1)));
	}
}
