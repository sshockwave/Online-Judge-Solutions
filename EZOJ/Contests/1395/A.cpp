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
const int O=998244353,MUL=19260817;
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
int m,a,n;
namespace sol1{
	const int N=3000010;
	namespace gmath{
		int fac[N],invfac[N];
		int pwa[N],pw1a[N];
		inline void main(int n){
			fac[0]=1;
			pwa[0]=pw1a[0]=1;
			for(int i=1;i<=n;i++){
				fac[i]=(lint)fac[i-1]*i%O;
				pwa[i]=(lint)pwa[i-1]*a%O;
				pw1a[i]=(lint)pw1a[i-1]*(O+1-a)%O;
			}
			invfac[n]=inv(fac[n]);
			for(int i=n;i>=1;i--){
				invfac[i-1]=(lint)invfac[i]*i%O;
			}
		}
		inline int C(int n,int k){
			return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
		}
	}
	inline int calc(int n,int m){
		lint ans=0;
		using namespace gmath;
		for(int j=0,mj=0;j+mj<=n;j++,mj+=m){
			ans+=(lint)C(n-mj,j)*pw1a[j]%O*pwa[n-mj-j];
			const static lint OO=(lint)O*O;
			if(ans>OO){
				ans-=OO;
			}
		}
		return ans%O;
	}
	inline int Main(){
		gmath::main(n);
		lint ans=0,pw=1;
		for(int i=1;i<=m&&i<=n;i++){//get m
			pw=pw*MUL%O;
			ans+=(calc(n-1,i)-calc(n-i-1,i))*pw%O;
		}
		ans=ans%O*a%O;
		if(m>n){//from n+1 to m
			ans+=(lint)gmath::pwa[n]*(fpow(MUL,m+1)-fpow(MUL,n+1))%O*inv(MUL-1)%O;
		}
		return (ans%O+O)%O;
	}
}
namespace sol2{
	const int N=1010;
	int f[N],tmp[N];
	inline void gmod(int i,int m){//mod x^m-ax^{m-1}+(a-1)
		for(;i>=m;i--){
			if(tmp[i]==0)continue;
			lint r=tmp[i];
			tmp[i]=0;
			tmp[i-1]=(tmp[i-1]+r*a)%O;
			tmp[i-m]=(tmp[i-m]+r*(O+1-a))%O;
		}
	}
	inline void gpw(int n,int m){
		if(n==0){
			memset(f,0,m<<2);
			f[0]=1;
			return;
		}
		gpw(n>>1,m);
		memset(tmp,0,(m*2-1)<<2);
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				tmp[i+j]=(tmp[i+j]+(lint)f[i]*f[j])%O;
			}
		}
		gmod(m*2-2,m),memcpy(f,tmp,m<<2);
		if(n&1){
			for(int i=m;i>=1;i--){
				tmp[i]=f[i-1];
			}
			tmp[0]=0;
			gmod(m,m);
			memcpy(f,tmp,m<<2);
		}
	}
	int pwa[N];
	inline int getval(int m){
		if(n<=m)return fpow(a,n);
		gpw(n-1,m+1);
		int r=(lint)f[m]*(a-1)%O;
		f[m]=0;
		lint ans=0;
		for(int i=0;i<m;i++){
			f[i]=(f[i]+r)%O;
			ans+=(lint)f[i]*pwa[i+1]%O;
		}
		return ans%O;
	}
	inline int Main(){
		lint cur=0,w=1;
		pwa[0]=1;
		for(int i=1;i<=m;i++){
			pwa[i]=(lint)pwa[i-1]*a%O;
			w=w*MUL%O;
			cur+=getval(i)*w%O;
		}
		return cur%O;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	m=ni,a=ni,n=ni;
	if(m<=300){
		printf("%d\n",sol2::Main());
	}else{
		printf("%d\n",sol1::Main());
	}
	return 0;
}
