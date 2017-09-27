#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100000010,rtN=10010,K=110,MOD=1000000007,F=1<<15;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
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
inline int inv(int x){
	return fpow(x,MOD-2);
}
int fct[F],fphi[F],fs;
inline void spwn(int x,int e){
	int n=fs;
	for(int i=1,v=1,lst;i<=e;i++){
		lst=v,v*=x;
		for(int j=0;j<n;j++){
			fct[fs]=fct[j]*v,fphi[fs]=fphi[j]*(v-lst),fs++;
		}
	}
}
inline void tear(int n){
	fs=0;
	fct[fs]=1,fphi[fs]=1,fs++;
	for(int i=2;i*i<=n;i++){
		int e=0;
		for(;n%i==0;n/=i,e++);
		spwn(i,e);
	}
	if(n!=1){
		spwn(n,1);
	}
}
int c[K][K];
inline void gc(int n){
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=add(c[i-1][j-1],c[i-1][j]);
		}
	}
}
inline int Main(){
	int n=ni,k=ni;
	tear(n);
	lint ans=0;
	for(int i=0;i<=k;i++){
		lint cur=0;
		for(int j=0;j<fs;j++){
			cur+=mul(fpow(i,n/fct[j]),fphi[j]);
		}
		cur=mul(cur%MOD,c[k][i]);
		if((k-i)&1){
			ans-=cur;
		}else{
			ans+=cur;
		}
	}
	return mul((ans%MOD+MOD)%MOD,inv(n));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("necklace.in","r",stdin);
	freopen("necklace.out","w",stdout);
#endif
	gc(K-1);
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
