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
const int N=200010;
int f[N];
inline lint Main(){
	const int n=ni;
	for(int i=1;i<=n;i++){
		f[i]=i;
	}
	for(int i=1,las=-1;i<=n;i++){
		const int a=ni;
		if(a>las+1)return -1;
		apmax(f[i-a],i);
		las=a;
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=f[i]-i;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	printf("%lld\n",Main());
	return 0;
}
