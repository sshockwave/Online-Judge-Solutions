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
const int N=100010,O=1000000007;
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
	inline void init(int n){
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
		if(n<k)return 0;
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
}
using gmath::C;
char s[N];
int f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
#endif
	const int n=ni;
	gmath::init(n);
	const int invn2=inv(C(n,2));
	const int inv2n=inv(fpow(2,n));
	f[0]=inv(2),f[1]=(f[0]+O-inv2n)%O;
	for(int i=2;i<n;i++){
		lint A=C(n-(i-1),2),B=C(i-1,2);
		//f[i-1]=inv2n+f[i]*A*invn2+f[i-2]*B*invn2+f[i-1]*(A+B)*invn2
		f[i]=(f[i-1]+O-f[i-2]*B%O*invn2%O+O-f[i-1]*(A+B)%O*invn2%O+O-inv2n)%O*inv(A*invn2%O)%O;
	}
	f[n]=inv(2);
	for(int i=0,j=n;i<j;i++,j--){//debug
		assert(f[i]==f[j]);
	}
	scanf("%s",s);
	int cnt=0;
	for(int i=0;s[i];i++){
		cnt+=s[i]-'A';
	}
	printf("%d\n",f[cnt]);
	return 0;
}
