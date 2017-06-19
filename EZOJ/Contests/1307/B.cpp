#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int N=50010;
int MOD;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
int gcd(const int &a,const int &b){
	return b==0?a:gcd(b,a%b);
}
inline int phi(int p){//O(sqrt(n))
	int q=p;
	for(int i=2;i*i<=q;i++){
		if(q%i==0){
			p=p/i*(i-1);
			for(;q%i==0;q/=i);
		}
	}
	if(q!=1){
		p=p/q*(q-1);
	}
	return p;
}
int a[N];
int n,tot,c;
struct BIT{
	int c[N];
	BIT(){
		memset(c,0,sizeof(c));
	}
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void add(int x,int v){
		for(;x<=n;apadd(c[x],v),x+=lowbit(x));
	}
	inline int sum(int x){
		int ans=0;
		for(;x;apadd(ans,c[x]),x^=lowbit(x));
		return ans;
	}
};
namespace task12{
	BIT B;
	inline void solve(){
		for(int i=1;i<=n;i++){
			B.add(i,a[i]);
		}
		while(tot--){
			if(ni){//ask
				int l=ni,r=ni;
				printf("%d\n",sub(B.sum(r),B.sum(l-1)));
			}else{
				int l=ni,r=ni;
				for(int i=l;i<=r;i++){
					int ta=fpow(c,a[i]);
					B.add(i,sub(ta,a[i]));
					a[i]=ta;
				}
			}
		}
	}
}
inline int fpow(int x,int n,int MOD){
	int ret=1;
	for(;n;n>>=1,x=(lint)x*x%MOD){
		if(n&1){
			ret=(lint)ret*x%MOD;
		}
	}
	return ret;
}
namespace rp{
	int pi;
	struct Num{
		int a,b;
		Num(int _a=0,int _b=0):a(_a%MOD),b(_b%pi){}
		inline Num nxt(){
			return Num(fpow(c,b,MOD),fpow(c,b,pi));
		}
	};
	inline void solve(){
		pi=phi(MOD);
		
	}
}
int main(){
	n=ni,tot=ni,MOD=ni,c=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	task12::solve();
}