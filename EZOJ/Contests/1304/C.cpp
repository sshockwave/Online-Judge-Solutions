#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010,MOD=1000000000,PHI=400000000;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	x%=MOD;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
inline int rev(int x){
	return fpow(x,PHI-1);
}
struct giant{
	int x,cnt2,cnt5;
	inline friend giant operator * (const giant &a,int b){
		giant c=a;
		for(;(b&1)==0;b>>=1,c.cnt2++);
		for(;b%5==0;b/=5,c.cnt5++);
		c.x=mul(c.x,b);
		return c;
	}
	inline friend giant operator * (const giant &a,const giant &b){
		return (giant){mul(a.x,b.x),a.cnt2+b.cnt2,a.cnt5+b.cnt5};
	}
	inline int eval(){
		assert(cnt2>=0&&cnt5>=0);
		return mul(x,mul(fpow(2,cnt2),fpow(5,cnt5)));
	}
}fac[N],refac[N];
inline giant rev(const giant &x){
	return (giant){rev(x.x),-x.cnt2,-x.cnt5};
}
void putint(int x,int k){
	if(k==0){
		return;
	}
	putint(x/10,k-1);
	putchar('0'+x%10);
}
int S[N];
inline int c(int n,int k){
	return (fac[n]*refac[k]*refac[n-k]).eval();
}
inline int work(int a,int b){
	S[0]=1;
	for(int i=1;i<=a;i++){
		S[i]=add(S[i-1],c(a,i));
	}
	int ans=0;
	for(int i=0;i<=b;i++){
		ans=add(ans,mul(S[i],c(b,i)));
	}
	return sub(fpow(2,a+b),ans);
}
int main(){
	fac[0]=(giant){1,0,0};
	for(int i=1;i<N;i++){
		fac[i]=fac[i-1]*i;
	}
	refac[N-1]=rev(fac[N-1]);
	for(int i=N-1;i;i--){
		refac[i-1]=refac[i]*i;
	}
	for(int a,b,k;scanf("%d%d%d",&a,&b,&k)!=EOF;putint(work(a,b),k),putchar('\n'));
}