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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=20000010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
namespace gmath{
	int fac[N],invfac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		assert(n>=k);
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
	inline int cat_bio(int rig,int up){
		if(up<0){
			up=-up;
		}
		if(up>rig)return 0;
		up+=rig;
		assert((up&1)==0);
		up>>=1;
		return C(rig,up);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	const int n=ni*2-2,m=ni-2;
	gmath::main(n);
	using gmath::cat_bio;
	int ans=cat_bio(n,0);
	int to1=0,to2=0;
	for(int i=1;cabs(to1)<=n||cabs(to2)<=n;i++){
		to1=-2-to1,to2=((m+1)<<1)-to2,swap(to1,to2);
		const lint cur=cat_bio(n,to1)+cat_bio(n,to2);
		if(i&1){
			ans=(ans-cur+O*2)%O;
		}else{
			ans=(ans+cur)%O;
		}
	}
	printf("%d\n",ans);
	return 0;
}
