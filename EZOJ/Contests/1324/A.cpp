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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=45,MOD=1011110011;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
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
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
int c[N][N];
inline void math(int n){
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=add(c[i-1][j-1],c[i-1][j]);
		}
	}
}
int f[N][N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("container.in","r",stdin);
	freopen("container.out","w",stdout);
#endif
	int n=ni,m=ni,v=ni;
	math(m);
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){//the ith bucket
		for(int j=0;j<=m;j++){//end before i
			for(int k=0,tm=min(m-j,v);k<=tm;k++){//using i
				lint tmp=0;
				for(int a=0;a<=j;a++){//end at i-1
					for(int b=max(k+a-v,0),tb=k+a;b<=tb;b++){//start at i
						tmp+=mul(mul(c[k+a-b][a],c[m-j-k+b][b]),f[i-1][j-a][k+a-b]);
					}
				}
				f[i][j][k]=tmp%MOD;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=v;i++){
		apadd(ans,f[n][m-i][i]);
	}
	printf("%d\n",ans);
	return 0;
}
