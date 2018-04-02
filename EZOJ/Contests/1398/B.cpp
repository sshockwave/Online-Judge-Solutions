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
const int N=1000010,O=1000000007;
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
namespace gmath{
	int fac[N],invfac[N];
	int invpw2[N];
	inline void main(int n){
		fac[0]=invpw2[0]=1;
		const int inv2=inv(2);
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
			invpw2[i]=(lint)invpw2[i-1]*inv2%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
}
inline int f(int n){
	using namespace gmath;
	assert((n&1)==0);
	n>>=1;
	return (lint)fac[n<<1]*invfac[n]%O*invpw2[n]%O;
}
int n;
inline int calc(int mxsum){
	assert(mxsum>=n+1);
	int i=(mxsum+1)>>1;
	return (lint)fpow(mxsum-n,n-i)*f(i-(n-i))%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("six.in","r",stdin);
	freopen("six.out","w",stdout);
#endif
	n=ni;
	gmath::main(n<<1);
	int ans=0;
	lint cur=0,last=0;
	for(int i=n+1;i<=n-1+n;i++,last=cur){
		cur=calc(i);
		ans=(ans+(cur-last)*i)%O;
	}
	printf("%lld\n",(lint)(ans+O)%O*inv(f(n))%O);
	return 0;
}
