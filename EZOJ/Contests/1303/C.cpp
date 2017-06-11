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
	if(a>b){a=b;}
}
const int SHIFT=20,N=1<<SHIFT,MOD=998244353;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x))
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
namespace NTT{
	int n,shift;
	inline void work(int a[]){
		for(int i=1;i<=shift;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				for(int k=j;k<n;k+=full){
					int p=a[k],q=mul(a[k+half],1);//debug
					a[k]=add(p,q);
					a[k+half]=sub(p,q);
				}
			}
		}
	}
}
int main(){
	
}