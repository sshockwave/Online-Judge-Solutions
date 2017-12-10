#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef long double ld;
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
const int N=200010;
int main(){
	int n=ni;
	ld a=ni,d=ni,ans=0;
	a-=d;
	for(;n>=1;n--){
		ans+=a+(n+0.5)*d;
		ld na=a+(a*2+d*3)/(n<<1),nd=(1+2.0/n)*d;
		a=na,d=nd;
	}
	printf("%.15Lf\n",ans);
	return 0;
}
