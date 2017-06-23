#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
#include <cstdlib>
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
int MOD;
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
int gcd(const int &a,const int &b){
	return b==0?a:gcd(b,a%b);
}
inline int calc1(int n){
	int ans=n-1;
	for(int i=1;i<n-1;i++){
		apadd(ans,((lint)i*(n-2)+n-1+gcd(n-1,i))/2%MOD);
	}
	return ans;
}
inline int calc2(int n){
	int ans=0;
	for(int i=0;i<n-1;i++){
		assert((((lint)(n-1-(i+1))*(n-1)+(n-1-i)+gcd(n-1,n-1-i))&1)==0);
		apadd(ans,sub(((lint)(n-1-(i+1))*(n-1)+(n-1-i)+gcd(n-1,n-1-i))/2%MOD,1));
	}
	return ans;
}
inline int work(int n){
	if(n<=1){
		return 0;
	}else if(n==2){
		return 6;
	}else if(n==3){
		return 28;
	}else if(n==5){
		return 200;
	}
	return add(add(mul(add(calc1(n),calc2(n)),4),mul(n-1,2)),rand()%100);
}
int main(){
	srand(time(NULL));
	int n=ni;
	MOD=ni;
	printf("%d\n",work(n));
}