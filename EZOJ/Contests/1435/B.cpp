#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef vector<int>vi;
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
inline int inv_pow(int x){
	return fpow(x,O-2);
}
namespace fac{
	int cnt[N],*arr[N];
	inline void main(int n){
		mset(cnt+1,0,n);
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j+=i){
				++cnt[j];
			}
			arr[i]=new int[cnt[i]]+cnt[i];
		}
		for(int i=n;i>=1;i--){
			for(int j=i;j<=n;j+=i){
				*--arr[j]=i;
			}
		}
	}
}
namespace gmath{
	const int N=::N+300;
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
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
}
namespace sieve{
	bool np[N];
	int pri[N],ps=0;
	vi expn[N];
	inline void main(int n){
		mset(np+1,0,n);
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				expn[i].push_back(1);
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				expn[t]=expn[i];
				if(i%p){
					expn[t].push_back(1);
				}else{
					++expn[t].back();
					break;
				}
			}
		}
	}
	inline int f(int k,int n){
		if(k==0)return n==1;
		lint a=1;
		for(vi::iterator it=expn[n].begin(),ti=expn[n].end();it!=ti;++it){
			a=a*gmath::C(k-1+*it,k-1)%O;
		}
		return a;
	}
}
int f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("machine.in","r",stdin);
	freopen("machine.out","w",stdout);
#endif
	int n=ni;
	fac::main(n);
	sieve::main(N-1);
	gmath::main(gmath::N-1);
	for(int i=1;i<=n;i++){
		f[i]=ni;
	}
	for(int tot=ni;tot--;){
		int k=ni,x=ni;
		const int* const fact=fac::arr[x];
		int ans=0;
		for(int i=0,ti=fac::cnt[x];i<ti;i++){
			const int d=fact[i];
			ans=(ans+(lint)f[d]*sieve::f(k,x/d))%O;
		}
		printf("%d\n",ans);
	}
	return 0;
}
