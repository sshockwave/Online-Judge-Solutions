#include <iostream>
#include <cstdio>
#include <cstring>
//#define NDEBUG
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
const int N=1000010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
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
int fac[N],invfac[N];
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
inline int c(int n,int k){
	if(n<0||k<0||n<k){
		return 0;
	}
	return mul(fac[n],mul(invfac[k],invfac[n-k]));
}
inline int Main(){
	int n=ni,A,B,C;
	{
		int a=ni,b=ni,c=ni;
		assert(a+b+c==n*2);
		A=(b+c-a)>>1;
		B=(a+c-b)>>1;
		C=(a+b-c)>>1;
		assert(A+B+C==n);
		if(A>B){swap(A,B);}
		if(B>C){swap(B,C);}
		if(A>B){swap(A,B);}
		assert(A<=B&&B<=C);
		if(A<0||C>n/2){
			return 0;
		}
		if(A==0&&B==0&&c==0){
			return 1;
		}
	}
	gmath(n+9);
	lint ans=0;
	for(int i=0;i<=A;i++){
		lint cur=0;
		int tmp=B+C-1-i;
		if(tmp>=0&&((tmp&1)==0)){
			int j=tmp>>1;
			cur+=mul(c(C-1,j),c(B-1,j-1));
		}
		tmp=B+C-2-i;
		if(tmp>=0&&((tmp&1)==0)){
			int j=tmp>>1;
			cur+=mul(mul(c(C-1,j),2),c(B-1,j));
		}
		tmp=B+C-3-i;
		if(tmp>=0&&((tmp&1)==0)){
			int j=tmp>>1;
			cur+=mul(c(C-1,j),c(B-1,j+1));
		}
		ans+=mul(cur%MOD,c(B+C+1-i,A-i));
	}
	return ans*2%MOD;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("board.in","r",stdin);
	freopen("board.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
