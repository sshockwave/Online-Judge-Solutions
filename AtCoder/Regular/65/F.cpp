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
const int N=3010,O=1000000007;
inline int fpow(int x,int n){
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
int f[N][N];
int lpos[N],rpos[N],sum[N];
char s[N];
int fac[N],invfac[N];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
inline int C(int n,int k){
	assert(n>=k);
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
int main(){
	int n=ni,tot=ni;
	scanf("%s",s+1);
	sum[0]=lpos[0]=rpos[0]=0;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+(s[i]=='1');
	}
	for(int i=1;i<=tot;i++){
		lpos[i]=ni,rpos[i]=ni;
		if(rpos[i]<=rpos[i-1]){
			i--,tot--;
		}else if(lpos[i]==lpos[i-1]){
			rpos[i-1]=rpos[i];
			i--,tot--;
		}
	}
	lpos[tot+1]=n+1;
	memset(f,0,sizeof(f));
	gmath(n);
	f[0][0]=1;
	int lo=0,hi=0;
	for(int i=1;i<=tot;i++){
		int nxtl=min(lpos[i+1],rpos[i]+1);
		int one=sum[rpos[i]]-sum[max(lpos[i]-1,rpos[i-1])];
		int len1=nxtl-lpos[i],len2=rpos[i]-nxtl+1;
		int nlo=max(lo+one-len1,0),nhi=min(hi+one,len2);
		assert(nlo<=nhi);
		for(int j=nlo;j<=nhi;j++){
			lint tmp=0;
			for(int k=max(lo,j-one),tk=min(hi,len1+j-one);k<=tk;k++){
				tmp+=(lint)f[i-1][k]*C(len1,k+one-j)%O;
			}
			f[i][j]=tmp%O;
		}
		lo=nlo,hi=nhi;
	}
	printf("%d\n",f[tot][0]);
	return 0;
}
