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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=200010,A=1000010;
int f[A];
int sum[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	f[0]=0;
	sum[0]=0;
	for(int i=1;i<n;i++){
		sum[i]=sum[i-1]+ni;
		for(int j=sum[i-1]+1;j<=sum[i];j++){
			const int len=j-sum[i-1];
			f[j]=sum[i-1]<len?len-sum[i-1]:f[sum[i-1]-len];
		}
	}
	for(int tot=ni;tot--;){
		int t=ni;
		printf("%d ",t>sum[n-1]?t-sum[n-1]:f[sum[n-1]-t]);
	}
	putchar('\n');
	return 0;
}
