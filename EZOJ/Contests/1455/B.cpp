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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=32000,K=122,O=998244353;
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
	const int N=::K;
	int fac[N],ifac[N];
	inline void init(int n=N-1){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
			assert((lint)fac[i]*ifac[i]%O==1);
		}
	}
	inline int C(const int n,const int k){
		return (lint)fac[n]*ifac[k]%O*ifac[n-k]%O;
	}
}
int lend[N],rend[N],rem[N];
lint f[N][K];
int lst[N];
template<int* v>inline bool sat_cmp(int a,int b){
	return v[a]<v[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sleeve.in","r",stdin);
	freopen("sleeve.out","w",stdout);
#endif
	const int n=ni,a=ni,b=ni,c=ni+1,k=ni;
	gmath::init(k);
	int rt=1;
	for(;(lint)rt*rt<n;rt++);
	int bcnt=0;
	for(int &i=bcnt;i*rt+rt-1<=n;i++){
		lend[i]=i*rt,rend[i]=lend[i]+rt-1,rem[i]=(b+(lint)a*lend[i])%c;
		lst[i]=i;
	}
	lint ans=0;
	if(bcnt){
		sort(lst,lst+bcnt,sat_cmp<rem>);
		memset(f,0,sizeof(f));
		for(int i=0;i<rt;i++){
			int l=0,r=bcnt;
			const lint tv=(lint)a*i-((lint)a*i+rem[lst[0]])/c*c;
			while(l<r){
				int m=(l+r)>>1;
				if((lint)a*i-((lint)a*i+rem[lst[m]])/c*c==tv){
					l=m+1;
				}else{
					r=m;
				}
			}
			const int v1=(tv%O+O)%O,v2=(v1+O-c)%O;
			for(int j=0,pw1=1,pw2=1;j<=k;j++,pw1=(lint)pw1*v1%O,pw2=(lint)pw2*v2%O){
				f[0][j]+=pw1;
				f[l][j]+=pw2+O-pw1;
			}
		}
		for(int i=0;i<bcnt;i++){
			for(int j=0;j<=k;j++){
				if(i){
					f[i][j]+=f[i-1][j];
				}
				f[i][j]%=O;
			}
			for(int j=0,pw=1;j<=k;j++,pw=(lint)pw*rem[lst[i]]%O){
				ans+=(lint)gmath::C(k,j)*pw%O*f[i][k-j]%O;
			}
		}
	}
	for(int i=bcnt*rt;i<=n;i++){
		ans+=fpow((b+(lint)a*i)%c,k);
	}
	printf("%lld\n",ans%O);
	return 0;
}
