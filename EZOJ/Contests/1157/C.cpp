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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=1010,MOD=1000000007;
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
inline int A(int n,int m){
	assert(n>=m&&n>=0&&m>=0);
	int x=1;
	for(;m--;apmul(x,n--));
	return x;
}
int c[N][N];
int card[N],f[N],_g[N],gm[N],g[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cardgame.in","r",stdin);
	freopen("cardgame.out","w",stdout);
#endif
	int n=ni,totk=ni,k=min((n-1)/2,totk),siga=0;
	for(int i=1;i<=9;i++){
		siga+=card[i]=ni;
	}
	apmin(k,siga-1);
	int seg=k+1;
	{//c
		memset(c,0,sizeof(c));
		c[0][0]=1;
		for(int i=1;i<=seg;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=add(c[i-1][j-1],c[i-1][j]);
			}
		}
	}{//f
		memset(f,0,sizeof(f));
		f[0]=1;
		for(int i=1;i<=9;i++){
			static int A[N];
			A[0]=1;
			for(int k=1,tk=min(seg,card[i]);k<=tk;k++){
				A[k]=mul(A[k-1],mul(card[i]-k+1,i));
			}
			for(int j=seg;j>=0;j--){
				lint tmp=0;
				for(int k=min(j,card[i]);k>=0;k--){
					tmp+=mul(f[j-k],mul(c[j][k],A[k]));
				}
				f[j]=tmp%MOD;
			}
		}
	}{//g
		memset(_g,0,sizeof(_g));
		memset(gm,0,sizeof(gm));
		memset(g,0,sizeof(g));
		for(int i=1;i<=n;i++){
			apadd(_g[0],gm[0]);
			g[0]=add(mul(gm[0]=g[0],10),1);
			for(int j=1;j<=k;j++){
				apadd(_g[j],gm[j]);
				g[j]=add(mul(gm[j]=g[j],10),_g[j-1]);
			}
		}
	}{//ans
		lint ans=0;
		for(int i=max(0,n-siga);i<=k;i++){
			ans+=mul(mul(g[i],f[i+1]),mul(A(siga-(i+1),n-i-(i+1)),A(totk,i)));
		}
		printf("%lld\n",ans%MOD);
	}
	return 0;
}
