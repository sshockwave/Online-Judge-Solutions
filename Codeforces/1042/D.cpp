#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
lint a[N];
lint sum[N];
int n;
int c[N];
inline int c_sum(int x){
	x++;
	int a=0;
	for(;x;a+=c[x],x^=x&-x);
	return a;
}
inline void add(int x,int v){
	x++;
	for(;x<=n;c[x]+=v,x+=x&-x);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
#endif
	memset(c,0,sizeof(c));
	a[0]=0,sum[0]=0;
	const int n=ni;
	::n=n+1;
	lint t=next_num<lint>();
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+ni;
		a[i]=sum[i];
	}
	sort(sum,sum+n+1);
	lint ans=0;
	for(int i=0;i<=n;i++){
		ans+=i-c_sum(upper_bound(sum,sum+n+1,a[i]-t)-sum-1);
		add(lower_bound(sum,sum+n+1,a[i])-sum,1);
	}
	printf("%I64d\n",ans);
	return 0;
}
