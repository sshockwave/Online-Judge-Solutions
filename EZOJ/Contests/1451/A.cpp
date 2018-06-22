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
const int N=1210,O=1000000007;
const lint limO=0x7f7f7f7f7f7f7f7f-(lint)O*O;
namespace gmath{
	const int N=::N<<1;
	int fac[N],ifac[N];
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
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
		}
	}
	inline int bio(int a,int b){
		return (lint)fac[a+b]*ifac[a]%O*ifac[b]%O;
	}
}
namespace newton{
	int n;
	int f[N];
	int a[N],b[N];
	inline void init(int _n){
		n=_n;
		for(int i=0;i<=n;i++){
			f[i]=(lint)f[i]*gmath::ifac[i]%O*gmath::ifac[n-i]%O;
		}
	}
	inline int main(lint _x){
		const int x=_x%O;
		a[0]=1;
		for(int i=1;i<=n;i++){
			a[i]=(lint)a[i-1]*(x+O-i+1)%O;
		}
		b[n]=1;
		for(int i=n-1;i>=0;i--){
			b[i]=(lint)b[i+1]*(x+O-i-1)%O;
		}
		lint ans=0;
		for(int i=0;i<=n;i++){
			lint cur=(lint)f[i]*a[i]%O*b[i];
			if(i&1){
				ans-=cur;
				if(ans<-limO){
					ans%=O;
				}
			}else{
				ans+=cur;
				if(ans>limO){
					ans%=O;
				}
			}
		}
		if(n&1){
			ans=-ans;
		}
		return (ans%O+O)%O;
	}
}
int ord=0;
int k;
int bioc[N];
inline void dp(const lint d,const lint r){
	static int f[N];
	ord+=k;
	for(int i=0;i<=ord;i++){
		f[i]=newton::main(i*d+r);
	}
	for(int i=0;i<=ord;i++){
		lint ans=0;
		for(int j=0;j<=i;j++){
			ans+=(lint)f[i-j]*bioc[j];
			if(ans>limO){
				ans%=O;
			}
		}
		newton::f[i]=ans%O;
	}
	newton::init(ord);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("split.in","r",stdin);
	freopen("split.out","w",stdout);
#endif
	const lint n=next_num<lint>(),m=next_num<lint>();
	gmath::main(gmath::N-1);
	newton::f[0]=1;
	newton::init(0);
	lint las=1,pw=1;
	k=ni;
	for(int i=0;i<N;i++){
		bioc[i]=gmath::bio(i,k-1);
	}
	for(;pw<=n;las=pw,pw*=m){
		dp(pw/las,n%pw/las);
		if(pw>n/m)break;
	}
	printf("%d\n",newton::main(n/pw));
	return 0;
}
