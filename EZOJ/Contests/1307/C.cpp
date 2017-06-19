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
const int K=55;
int k,MOD;
inline bool valid(const int &x){
	return x>=0&&x<MOD;
}
inline int add(const int &a,const int &b){
	assert(valid((a+b)%MOD));
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	assert(valid((lint)a*b%MOD));
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
void fpow(int a[],int tmp[],lint n){//store into a
	if(n==0){
		a[0]=1;
		return;
	}
	fpow(tmp,a,n>>1);
	memset(a,0,k<<2);
	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++){
			apadd(a[(i+j)%k],mul(tmp[i],tmp[j]));
		}
	}
	if(n&1){
		memcpy(tmp,a,k<<2);
		for(int i=0;i<k;i++){
			apadd(a[(i+1)%k],tmp[i]);
		}
	}
}
int a[K],tmp[K];
int main(){
	lint n=ni;
	MOD=ni,k=ni;
	fpow(a,tmp,n*k);
	printf("%d\n",a[ni]);
}