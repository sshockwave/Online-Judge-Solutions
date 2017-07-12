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
const int N=210,MOD=1000000007;
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
inline void apsub(int &a,const int &b){
	a=sub(a,b);
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
int fac[N*3],invfac[N*3],cat[N*3];
inline int c(int n,int k){
	assert(n>=k);
	return mul(fac[n],mul(invfac[k],invfac[n-k]));
}
int vt,vi,noun,adj;
int f[N<<1][N<<1],g[N<<1][N*3];
int main(){
#ifndef ONLINE_JUDGE
	freopen("write.in","r",stdin);
	freopen("write.out","w",stdout);
#endif
	vt=ni,vi=ni,noun=ni,adj=ni;
	{//get fac
		fac[0]=1;
		int n=max((vt<<1)+vi,noun);
		for(int i=1;i<=n;i++){
			fac[i]=mul(fac[i-1],i);
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=mul(invfac[i],i);
			assert(mul(fac[i],invfac[i])==1);
		}
	}
	//Catalan
	memset(cat,0,sizeof(cat));
	cat[0]=cat[1]=1;
	for(int i=2;i<=vt;i++){
		for(int j=1;j<=i;j++){
			apadd(cat[i],mul(cat[j-1],cat[i-j]));
		}
	}
	//init
	memset(f,0,sizeof(f)),f[0][0]=1;
	memset(g,0,sizeof(g));
	//two
	for(int i=1;i<=vt;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<=i;k++){
				apadd(f[i][j],mul(mul(mul(c(i,k),fac[k]),cat[k]),f[i-k][j-1]));
			}
		}
	}
	//one
	for(int i=max(1,vi-vt);i<=vt;i++){
		apadd(g[i][i+vt-vi],mul(f[vt][i],mul(c(i+vt,vi),fac[vi])));
	}
	for(int i=1,tn=vi+vt;i<=tn;i++){
		for(int j=min(tn,vt+i);j>=i;j--){
			for(int k=j;k>=0;k--){
				int &F=f[j][k]=0;
				if(k&&f[j-1][k-1]){
					apadd(F,mul(f[j-1][k-1],k));
				}
				if(f[j-1][k]){
					apadd(F,mul(f[j-1][k],k+j-i+(j-1)));
				}
				if(F){
					int zero=tn-j,two=j-i,ans=F;
					if(zero>vi){
						continue;
					}
					apmul(ans,mul(c(vt,two),c(vi,zero)));
					if(k+two>=zero){
						apmul(ans,mul(c(k+two,zero),fac[zero]));
						apadd(g[k][k+two-zero],ans);
					}
				}
			}
		}
	}
	//adj
	for(int i=1;i<=adj;i++){
		for(int j=vt+vi;j>=1;j--){
			for(int k=vt+j;k>=0;k--){
				apmul(g[j][k],vt+vi+i-1-j+k);
			}
		}
	}
	//get ans
	int ans=0;
	for(int i=1,tn=vi+vt,pw=1;i<=tn;i++,apmul(pw,3)){
		if(noun==0){
			apadd(ans,mul(g[i][0],pw));
		}else for(int j=min(noun,vt+i);j>=1;j--){
			apadd(ans,mul(mul(c(noun-1,j-1),g[i][j]),pw));
		}
	}
	printf("%d\n",mul(ans,fac[noun]));
}
