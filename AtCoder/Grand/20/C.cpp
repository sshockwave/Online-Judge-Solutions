#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <bitset>
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
const int N=2010;
bitset<N*N>f;
int main(){
#ifndef ONLINE_JUDGE
	freopen("median.in","r",stdin);
	freopen("median.out","w",stdout);
#endif
	const int n=ni;
	int sum=0;
	f.set(0);
	for(int i=1;i<=n;i++){
		const int a=ni;
		f|=f<<a;
		sum+=a;
	}
	sum=(sum+1)>>1;
	for(int i=sum;;i++){
		if(f.test(i)){
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}
