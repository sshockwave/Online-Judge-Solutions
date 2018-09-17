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
const int N=110;
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int mx=0;
	const int n=ni;
	int m=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		apmax(mx,a[i]);
	}
	mx+=m;
	for(;m--;){
		int p=1;
		for(int i=1;i<=n;i++){
			if(a[i]<a[p]){
				p=i;
			}
		}
		a[p]++;
	}
	int mn=0;
	for(int i=1;i<=n;i++){
		apmax(mn,a[i]);
	}
	printf("%d %d\n",mn,mx);
	return 0;
}
