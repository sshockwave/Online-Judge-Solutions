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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
int O;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
inline void Main(){
	int k=ni;
	O=ni;
	k=inv_pow(k);
	int tx,ty;
	lint tans=0x7f7f7f7f7f7f7f7fll;
	for(int i=1;i<O;i++){
		int nx=i,ny=(lint)nx*k%O;
		lint nans=(lint)min(i,O-i)*ny;
		if(nans<tans||(nans==tans&&ny<ty)){
			tx=i<O-i?nx:-(O-i),ty=ny,tans=nans;
		}
	}
	printf("%d %d\n",tx,ty);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("frac.in","r",stdin);
	freopen("frac.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
