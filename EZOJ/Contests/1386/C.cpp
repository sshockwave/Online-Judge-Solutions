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
template<class T>T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
template<class T>T lcm(const T &a,const T &b){return a/gcd(a,b)*b;}
const int N=55;
int n,O;
namespace euler{
	inline int fpow(int x,int n){
		int a=1;
		for(;n;n>>=1,x=(lint)x*x%O){
			if(n&1){
				a=(lint)a*x%O;
			}
		}
		return a;
	}
	template<class T>void ex_gcd(T a,T b,T &x,T &y){
		if(b==0){
			x=1,y=1;
			return;
		}
		ex_gcd(b,a%b,y,x);
		y-=a/b*x;
	}
	inline int inv(int x){
		return fpow(x,O-2);
		lint u,v;
		ex_gcd((lint)x,(lint)O,u,v);
		return (u%O+O)%O;
	}
}
namespace cmath{
	int c[N][N];
	int fac[N];
	inline void init(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		memset(c,0,sizeof(c));
		for(int i=0;i<=n;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=(c[i-1][j-1]+c[i-1][j])%O;
			}
		}
	}
}
using euler::inv;
using cmath::c;
using cmath::fac;
int f[N][40000];
int main(){
#ifndef ONLINE_JUDGE
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
#endif
	n=ni,O=ni;
	cmath::init(n);
	f[0][1]=1;
	int mx=1;
	lint ans=0;
	for(int t=1;t<=n;t++){
		int nmx=1;
		for(int i=n;i>=t-1;i--){
			for(int j=mx;j>=1;j--){
				lint F=f[i][j];
				if(F==0)continue;
				f[i][j]=0;
				for(int k=n;k>i;k--){
					int d=lcm(j,k-i);
					apmax(nmx,d);
					f[k][d]=(int)(f[k][d]+F*c[k-1][k-i-1]%O*fac[k-i-1]%O)%O;
				}
			}
		}
		mx=nmx;
		for(int i=1;i<=mx;i++){
			ans+=(lint)i*i*f[n][i]%O;
		}
	}
	printf("%lld\n",ans%O*inv(fac[n])%O);
	return 0;
}
