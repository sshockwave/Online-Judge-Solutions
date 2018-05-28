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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const db EPS=1e-8;
inline double Main(int n){
	db a=0,f=1;
	for(int i=0;f>=EPS;i++){
		f/=n+1+i;
		if(i&1){
			a-=f;
		}else{
			a+=f;
		}
	}
	return a;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("homework.in","r",stdin);
	freopen("homework.out","w",stdout);
#endif
	printf("%.4lf\n",Main(ni));
	return 0;
}
