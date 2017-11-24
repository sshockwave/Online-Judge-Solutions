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
const int N=200010;
#define f(i) (a[i]<=m)
int a[N],n,n2;
inline bool check(int m){
	int l=n,r=n;
	for(;l>1&&f(l-1)!=f(l);l--);
	for(;r<n2&&f(r+1)!=f(r);r++);
	return n-l<r-n?f(l):f(r);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("pyramid.in","r",stdin);
	freopen("pyramid.out","w",stdout);
#endif
	n=ni,n2=(n<<1)-1;
	for(int i=1;i<=n2;i++){
		a[i]=ni;
	}
	int l=1,r=n2;
	while(l<r){
		int m=(l+r)>>1;
		if(check(m)){
			r=m;
		}else{
			l=m+1;
		}
	}
	printf("%d\n",l);
	return 0;
}
