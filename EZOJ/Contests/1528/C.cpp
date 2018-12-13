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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=1010,O=998244353;
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
	int fac[N],ifac[N];
	int c[N][N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
		}
		for(int i=0;i<=n;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=(c[i-1][j-1]+c[i-1][j])%O;
			}
		}
	}
}
namespace dp1{
	int f[N][N];
	inline void main(int n){
		for(int i=1;i<=n;i++){
			f[i][0]=1;
			f[i][1]=i&1;
			for(int j=2;j<=n;j++){
				f[i][j]=((lint)f[i][j-1]*(i&1)+(lint)f[i][j-2]*(j-1)*i)%O;
			}
		}
	}
}
int f[N],g[N];
vi vec[N];
inline int Main(){
	const int n=ni;
	lint ab=0;
	{
		lint a=next_num<lint>();
		lint b=next_num<lint>();
		lint c=next_num<lint>();
		if(a==0&&b==0&&c==0){
			static int f[N];
			f[0]=1,f[1]=1;
			for(int i=2;i<=n;i++){
				f[i]=(f[i-1]+(lint)f[i-2]*(i-1))%O;
			}
			return (lint)f[n]*fpow(n,n)%O;
		}
		ab=a-b+c;
	}
	if(ab<0){
		ab=-ab;
	}
	using gmath::fac;
	using gmath::ifac;
	using gmath::c;
	for(int i=1;i<=n;i++){
		vec[i].clear();
	}
	for(int i=1;i<=n;i++){
		const int cnt=gcd<lint>(i,ab);
		vec[i/cnt].push_back(cnt);
	}
	g[0]=1,mset(g+1,0,n);
	for(int i=1;i<=n;i++){
		f[0]=1,mset(f+1,0,n);
		for(int j=1;j<=n/i;j++){
			for(vi::iterator it=vec[i].begin(),ti=vec[i].end();it!=ti;++it){
				const int cnt=*it;
				if(j>=cnt){
					f[j]=(f[j]+(lint)f[j-cnt]*fac[i*j-1]%O*ifac[i*(j-cnt)])%O;
				}else break;
			}
		}
		for(int j=0;j<=n/i;j++){
			f[j]=(lint)f[j]*dp1::f[i][j]%O;
		}
		for(int j=n;j>=0;j--){
			int F=0;
			for(int k=0;i*k<=j;k++){
				F=(F+(lint)g[j-k*i]*f[k]%O*c[j][i*k])%O;
			}
			g[j]=F;
		}
	}
	return g[n];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dragonfly.in","r",stdin);
	freopen("dragonfly.out","w",stdout);
#endif
	gmath::main(N-1);
	dp1::main(N-1);
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
