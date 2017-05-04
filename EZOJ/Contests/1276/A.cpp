#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int MOD=258280327,N=53,M=9;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return add(a,MOD-b);
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
inline void apmul(int &a,int b){
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
int c[N][N],pow2[N*N*M];
int f[N][M],g[N][N][M],p[N][N][M][1<<M];
int getp(int s,int t,int m,int k){
	if(~p[s][t][m][k]){
		return p[s][t][m][k];
	}
	if(s==0||t==0||k==0){
		return p[s][t][m][0]=p[t][s][m][0]=pow2[(s+t)*m];
	}
	if(s>t){
		swap(s,t);
	}
	int res;
	if(k<(1<<(m-1))){
		res=mul(2,pow2[(s+t)*(m-1)]);
		for(int s0=0;s0<=s;s0++){
			for(int t0=(s0==s),mx=t-(s0==0);t0<=mx;t0++){
				apadd(res,mul(mul(c[s][s0],c[t][t0]),mul(getp(s0,t0,m-1,k),getp(s-s0,t-t0,m-1,k))));
			}
		}
	}else{
		res=mul(2,getp(s,t,m-1,k^(1<<(m-1))));
	}
	return p[s][t][m][k]=p[t][s][m][k]=res;
}
int getg(int s,int t,int m){
	if(~g[s][t][m]){
		return g[s][t][m];
	}
	if(s>t){
		swap(s,t);
	}
	int res=0;
	for(int i=(1<<m)-1;i>0;i--){
		apadd(res,getp(s,t,m,i));
	}
	return g[s][t][m]=g[t][s][m]=res;
}
int getf(int n,int m){
	if(m==0||n<2){
		return 0;
	}
	if(~f[n][m]){
		return f[n][m];
	}
	int res=add(mul(2,getf(n,m-1)),mul(pow2[(n+1)*(m-1)],sub(pow2[n],2)));
	for(int i=1;i<n;i++){
		apadd(res,mul(c[n][i],add(add(mul(pow2[(m-1)*(n-i)],getf(i,m-1)),mul(pow2[(m-1)*i],getf(n-i,m-1))),getg(i,n-i,m-1))));
	}
	return f[n][m]=res;
}
int main(){
	pow2[0]=1;
	for(int i=1,_=N*N*M;i<_;i++){
		pow2[i]=mul(pow2[i-1],2);
	}
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<N;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=add(c[i-1][j-1],c[i-1][j]);
		}
	}
	int n=ni(),m=ni();
	memset(g,-1,sizeof(g));
	memset(p,-1,sizeof(p));
	memset(f,-1,sizeof(f));
	printf("%d\n",mul(getf(n,m),fpow(pow2[n*m],MOD-2)));
}
