#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=10000010,O=1000000007;
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
namespace poly{
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
	}
	template<int f[]>inline void sqrt(const int n,const int a){//(1+ax)^(1/2)
		gmath::main(n);
		for(int i=0,pw=1,td=3ll*inv_pow(2)%O;i<=n;i++,pw=(lint)pw*a%O*--td%O){
			f[i]=(lint)pw*gmath::invfac[i]%O;
		}
	}
}
int f[N];
inline void calc_f(int n,int k){
	poly::sqrt<f>(n,(O-4ll*(k-1)%O)%O);
	const int kinv2=(lint)k*inv_pow(2)%O;
	f[0]=((lint)f[0]*k+O-(k-2))%O*inv_pow(2)%O;
	for(int i=1;i<=n;i++){
		f[i]=(lint)f[i]*kinv2%O;
	}
	const int k2=(lint)k*k%O;
	for(int i=1;i<=n;i++){
		f[i]=(f[i]+(lint)f[i-1]*k2)%O;
	}
}
/*inline string space(){
  ifstream fin("/proc/self/status");
  return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}*/
int main(){
#ifndef ONLINE_JUDGE
	freopen("quote.in","r",stdin);
	freopen("quote.out","w",stdout);
#endif
	int tot=ni,k=ni;
	calc_f(N-1,k);
	for(;tot--;printf("%d\n",f[ni]));
	return 0;
}
