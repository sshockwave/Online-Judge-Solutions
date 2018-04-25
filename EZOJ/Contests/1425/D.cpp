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
const int N=100010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("red.in","r",stdin);
	freopen("red.out","w",stdout);
#endif
	int n=ni,q=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	while(q--){
		int t=ni;
		lint sum=0;
		if(t==1){
			int x=ni;
			for(int i=1;i<=n;i++){
				a[i]=(a[i]+x)%O;
				sum+=a[i];
			}
		}else{
			for(int i=1;i<=n;i++){
				a[i]=inv(a[i]);
				sum+=a[i];
			}
		}
		printf("%lld\n",sum%O);
	}
	return 0;
}
