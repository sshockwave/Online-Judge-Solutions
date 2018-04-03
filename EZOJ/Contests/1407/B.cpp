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
const int N=1010,O=998244353;
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
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("instinct.in","r",stdin);
	freopen("instinct.out","w",stdout);
#endif
	lint n=next_num<lint>();
	int m=ni;
	gmath::main(m);
	lint k=next_num<lint>();
	if(k>n||m>n){
		puts("0");
		return 0;
	}
	lint nk=n/k,mk=(m+k-1)/k;
	int ans=0;
	for(int j=0;j<=m;j++){
		lint cur;
		int jk=fpow(j,k);
		if(jk==0){
			cur=0;
		}else if(jk==1){
			cur=nk-mk+1;
		}else{
			int a1=fpow(jk,mk),an=(lint)fpow(jk,nk)*jk%O;
			cur=(lint)(an+O-a1)*inv(jk-1)%O;
		}
		cur=cur%O*gmath::invfac[j]%O*gmath::invfac[m-j]%O;
		if((m-j)&1){
			ans=(ans+O-cur)%O;
		}else{
			ans=(ans+cur)%O;
		}
	}
	printf("%d\n",ans);
	return 0;
}
