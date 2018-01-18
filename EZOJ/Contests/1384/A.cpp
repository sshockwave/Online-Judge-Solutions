#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
int O;
namespace math{
	const int N=1000010*4;//TODO
	inline int fpow(int x,lint n){
		if(n<0){
			n=n%(O-1)+O-1;
		}
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
	int fac[N],invfac[N];
	inline void init(int n){
		assert(n<N);
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
			assert((lint)fac[i]*invfac[i]%O==1);
		}
	}
	inline int C(int n,int k){
		if(n<k)return 0;//TOCHECK
		if(n<0||k<0)return 0;
		assert(n<N&&fac[n]);
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
	inline int R(int n,int m){
		if(n<0||m<0)return 0;
		assert(n+m<N&&fac[n+m]);
		return (lint)fac[n+m]*invfac[n]%O*invfac[m]%O;
	}
	inline int divcnt(int n,int k){
		if(n<0||k<0)return 0;
		return C(n-1,k-1);
	}
	inline int empcnt(int n,int k){
		if(n<0||k<0)return 0;
		return divcnt(n+k,k);
	}
}
using math::fpow;
using math::R;
using math::empcnt;
inline int Main(){
	int n=ni,m=ni,s=ni;
	O=ni;
	math::init(s+max(n,m)*3);//TODO
	if(n==1)return empcnt(s,m-1);
	if(m==1)return empcnt(s,n-1);
	lint ans=0;
	int pw=fpow(s+1,(lint)n*m-((n-1)+(m-1))*2-1);
	for(int i=n-1;i>=1;i--){//last step:right
		int down=i-1,right=m-1;
		pw=(lint)pw*(s+1)%O;
		ans+=(lint)R(down,right-1)*empcnt(s-down,((down+right)<<1)+(n-i))%O*pw%O;
	}
	pw=fpow(s+1,(lint)n*m-((n-1)+(m-1))*2-1);
	for(int j=m-1;j>=1;j--){//last step:down
		int down=n-1,right=j-1;
		pw=(lint)pw*(s+1)%O;
		ans+=(lint)R(down-1,right)*empcnt(s-down,((down+right)<<1)+(m-j))%O*pw%O;
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("table.in","r",stdin);
	freopen("table.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
