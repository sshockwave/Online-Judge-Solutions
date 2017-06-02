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
int MOD;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
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
		if(a&1==0){
			a>>=1;
		}else{
			b>>=1;
		}
		return fpow(2,a%(MOD-1)*b%(MOD-1));
	}
}
namespace task6{
	const int N=1010;
	int f[N];
	inline void init(){
		f[1]=1;
		
	}
	inline int work(int n){
		
	}
}
namespace task7{
	
	inline int work(int n){
		
	}
}
int n;
int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	MOD=ni;
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