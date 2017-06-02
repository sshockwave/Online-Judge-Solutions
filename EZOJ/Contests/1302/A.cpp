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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=1010;
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
inline void apsub(int &a,const int &b){
	a=sub(a,b);
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
int c[N][N];
namespace task1{
	inline int work(lint n){
		return n==1?1:fpow(n%MOD,(n-2)%(MOD-1));
	}
}
namespace task2{
	inline int work(lint n){
		return fpow(n%MOD,(n-1)%(MOD-1));
	}
}
namespace task3{
	int f[]={0,1,1,1,2,3};
	inline int work(int n){
		return f[n]%MOD;
	}
}
namespace task4{
	int f[]={0,1,1,2,};
	inline int work(int n){
		
	}
}
namespace task5{
	inline int work(lint n){
		lint a=n-1,b=n-2;
		if((a&1)==0){
			a>>=1;
		}else{
			b>>=1;
		}
		return fpow(2,a%(MOD-1)*b%(MOD-1));
	}
}
namespace task6{
	int f[N];
	inline int work(int n){
		for(int i=1;i<=n;i++){
			f[i]=task5::work(i);
			for(int j=1;j<i;j++){
				apsub(f[i],mul(mul(c[i-1][j-1],f[j]),task5::work(i-j)));
			}
		}
		return f[n];
	}
}
namespace task7{
	
	inline int work(int n){
		
	}
}
int n;
int main(){
	MOD=ni;
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<N;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
	}
	int ans[7]={
		task1::work(nl),
		task2::work(nl),
		task3::work(ni),
		task4::work(ni),
		task5::work(nl),
		task6::work(ni),
		task7::work(ni)
	};
	for(int i=0;i<7;i++){
		printf("%d ",ans[i]);
	}
	putchar('\n');
	return 0;
}