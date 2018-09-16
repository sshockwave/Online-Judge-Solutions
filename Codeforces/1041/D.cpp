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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(a[0]));}
const int N=200010;
int lend[N],rend[N];
int a[N];
lint sum[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
#endif
	const int n=ni,h=ni;
	sum[0]=0;
	for(int i=1;i<=n;i++){
		lend[i]=ni,rend[i]=ni;
		a[i]=rend[i]-lend[i];
		sum[i]=sum[i-1]+a[i];
	}
	lint ans=0;
	for(int i=1,j=1;i<=n;i++){
		for(;j<n&&(rend[j+1]-lend[i]-(sum[j+1]-sum[i-1]))<h;j++);
		apmax(ans,h+sum[j]-sum[i-1]);
	}
	printf("%I64d\n",ans);
	return 0;
}
