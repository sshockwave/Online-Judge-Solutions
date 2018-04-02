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
const int N=500010,O=1000000007;
inline int fpow(int x,lint n){
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
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		assert(k<=n);
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
}
namespace newton{
	int pre[N],suf[N];
	inline int main(int f[],int k,lint n){
		pre[0]=1;
		for(int i=1;i<=k;i++){
			pre[i]=(lint)pre[i-1]*(n-i+1)%O;
		}
		suf[k]=1;
		for(int i=k-1;i>=0;i--){
			suf[i]=(lint)suf[i+1]*(n-i-1)%O;
		}
		lint ans=0;
		for(int i=0;i<=k;i++){
			using namespace gmath;
			int cur=(lint)pre[i]*suf[i]%O*invfac[i]%O*invfac[k-i]%O*f[i]%O;
			if((k-i)&1){
				ans-=cur;
			}else{
				ans+=cur;
			}
		}
		return (ans%O+O)%O;
	}
}
int f[N],g[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("four.in","r",stdin);
	freopen("four.out","w",stdout);
#endif
	lint n=next_num<lint>();
	int k=ni,q=ni;
	for(int i=0;i<=k;i++){
		f[i]=ni;
	}
	gmath::main(k+1);
	int a=0,b=1;
	lint ta=0,tb=0;//ta+tb*x==0
	f[k+1]=newton::main(f,k,k+1);
	lint invq=inv(q);
	for(int i=0;i<=k+1;i++){
		a=(a*invq+f[i])%O,b=b*invq%O;
		lint c=gmath::C(k+1,i);
		if((k+1-i)&1){
			ta+=a*c%O,tb+=b*c%O;
		}else{
			ta-=a*c%O,tb-=b*c%O;
		}
	}
	assert(tb%O);
	g[0]=((O-ta%O)*inv((tb%O+O)%O)%O*invq+f[0])%O;
	for(int i=1;i<=k;i++){
		g[i]=(g[i-1]*invq+f[i])%O;
	}
	printf("%lld\n",((lint)newton::main(g,k,n%O)*fpow(q,n)+(f[0]+O-g[0]))%O);
	return 0;
}
