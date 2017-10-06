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
const int N=14010,K=10,KN=N*K,MOD=786433;
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
int fac[KN],invfac[KN];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=mul(fac[i-1],i);
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=mul(invfac[i],i);
	}
}
int g[K][N];
int f[2][KN];
inline int work(int n,int k){
	int top=0;
	bool r=false;
	f[r][0]=1;
	for(int t=1;t<k;t++,r=!r){
		memset(f[!r],0,(top+n+1)<<2);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=top;j++){
				apadd(f[!r][i+j],mul(g[t][i],f[r][j]));
			}
		}
		top+=n;
	}
	lint ans=0;
	for(int i=0;i<=top;i++){
		ans+=mul(fac[i],f[r][i]);
	}
	return ans%MOD;
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("int.in","r",stdin);
	freopen("int.out","w",stdout);
#endif
	int k=ni,n=ni,tot=ni;
	gmath(n*(k-1));
	for(int i=1;i<k;i++){
		scanf("%s",s);
		for(int j=0;j<=n;j++){
			g[i][j]=s[j]=='1'?invfac[j]:0;
		}
	}
	lint ans=work(n,k);
	while(tot--){
		int u=ni,v=ni;
		g[u][v]=invfac[v]-g[u][v];
		ans+=work(n,k);
	}
	printf("%lld\n",ans%MOD);
	return 0;
}
