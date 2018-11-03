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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
namespace B{
	int c[N],n;
	inline void init(int _n){
		mset(c+1,0,n=_n);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int a=0;
		for(;x;a+=c[x],x^=x&-x);
		return a;
	}
}
int a[N],n;
int _a[N];
inline lint Main2(int mid,int lenl,int lenr){
	_a[0]=0;
	int mn=0,mx=0;
	for(int i=1;i<=n;i++){
		_a[i]=_a[i-1]+(a[i]<=mid?1:-1);
		apmin(mn,_a[i]),apmax(mx,_a[i]);
	}
	lint ans=0;
	B::init(mx-mn+1);
	for(int i=0;i<=n;i++){
		_a[i]-=mn-1;
	}
	for(int i=0;i<=n;i++){
		B::add(_a[i],1);
		if(i+lenr+1<=n){
			ans-=B::sum(_a[i+lenr+1]);
		}
		if(i+lenl<=n){
			ans+=B::sum(_a[i+lenl]);
		}
	}
	return ans;
}
inline lint Main(){
	const int l1=ni,r1=ni,l2=ni,r2=ni;
	return Main2(r1,l2,r2)-Main2(l1-1,l2,r2);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
