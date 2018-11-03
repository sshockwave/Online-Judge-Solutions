#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=100010;
int fib[100];
int f[N];
int ta[N];
int que[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
#endif
	fib[0]=1,fib[1]=2;
	const int fcnt=44;
	for(int i=2;i<=fcnt;i++){
		fib[i]=fib[i-1]+fib[i-2];
	}
	const int n=ni;
	typedef map<int,int>mii;
	mii mp;
	int qh=0,qt=0;
	f[0]=0,que[qt++]=0;
	for(int i=1,j=0;i<=n;i++){
		const int a=ni;
		ta[i]=a;
		for(int k=0;k<=fcnt;k++){
			if(a<=fib[k]){
				mii::iterator it=mp.find(fib[k]-a);
				if(it!=mp.end()){
					apmax(j,it->second);
				}
			}
		}
		for(;que[qh]<j;qh++);
		assert(qh<qt);
		f[i]=f[que[qh]]+1;
		for(;qh<qt&&f[que[qt-1]]>=f[i];qt--);
		que[qt++]=i;
		mp[a]=i;
	}
	printf("%d\n",f[n]);
	return 0;
}
