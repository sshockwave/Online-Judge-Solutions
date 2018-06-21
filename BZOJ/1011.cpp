#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef double db;
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
const int N=100010;
db mass[N],sum[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("planet.in","r",stdin);
	freopen("planet.out","w",stdout);
#endif
	const int n=ni;
	db p;
	scanf("%lf",&p);
	sum[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%lf",mass+i);
		sum[i]=sum[i-1]+mass[i];
		const int m=i*p;
		db ans=0;
		for(int l=1,r;l<=m;l=r+1){
			r=min<int>(m,i-(i-l)/1.04);
			ans+=(sum[r]-sum[l-1])/(i-l);
		}
		printf("%.10lf\n",ans*mass[i]);
	}
	return 0;
}
