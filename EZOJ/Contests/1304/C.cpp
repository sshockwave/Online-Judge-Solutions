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
const int N=110,MOD=1000000000;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
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
struct giant{
	int p[N];
	inline int eval(){
		int ret=1;
		for(int i=2;i<N;i++){
			ret=mul(ret,fpow(i,p[i]));
		}
		return ret;
	}
	inline friend giant operator * (const giant &a,int x){
		giant b;
		for(int i=2;i<N;i++){
			b.p[i]=a.p[i];
			for(;x%i==0;x/=i,b.p[i]++);
		}
		return b;
	}
	inline friend giant operator / (const giant &a,const giant &b){
		giant c;
		for(int i=0;i<N;i++){
			c.p[i]=a.p[i]-b.p[i];
		}
		return c;
	}
}fac[N];
int c[N][N];
void putint(int x,int k){
	if(k==0){
		return;
	}
	putint(x/10,k-1);
	putchar('0'+x%10);
}
int main(){
	for(int i=1;i<N;i++){
		fac[i]=fac[i-1]*i;
	}
	c[0][0]=1;
	for(int i=1;i<N;i++){
		for(int j=0;j<=i;j++){
			c[i][j]=(fac[i]/fac[j]/fac[i-j]).eval();
		}
	}
	for(int a,b,k;scanf("%d%d%d",&a,&b,&k)!=EOF;){
		int ans=0;
		for(int i=0;i<=b;i++){
			int cur=0;
			for(int j=i+1;j<=a;j++){
				cur=add(cur,c[a][j]);
			}
			ans=add(ans,mul(cur,c[b][i]));
		}
		putint(ans,k),putchar('\n');
	}
}