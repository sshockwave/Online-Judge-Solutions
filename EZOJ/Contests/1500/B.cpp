#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
typedef long double db;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
inline db Main(){
	const int n=ni,m=ni;
	if(n==m)return 1;
	const int g=gcd(n,m);
	if(n>m){
		return tan((db)M_PI/m)/tan((db)M_PI/n);
	}
	return sin((db)M_PI/m)/sin((db)M_PI/n);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
#endif
	printf("%.10lf\n",(double)Main());
	return 0;
}
