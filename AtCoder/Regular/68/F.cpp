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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=2010,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int f[N];
inline int Main(){
	int n=ni,k=ni;
	memset(f,0,sizeof(f));
	f[0]=1;
	for(int i=1;i<n;i++){
		for(int j=i;j>0;j--){
			f[j]=(f[j+1]+f[j-1])%O;
		}
		f[0]=f[1];
	}
	return (lint)f[n-k]*fpow(2,max(n-k-1,0))%O;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
