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
const int N=1000000010,K=1000010,MOD=998244353;
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
inline int bigfac(int n){
	const static int lst[]=
	{
		1,295201906,160030060,957629942,545208507,213689172,760025067,939830261,506268060,39806322,
		808258749,440133909,686156489,741797144,390377694,12629586,544711799,104121967,495867250,421290700,
		117153405,57084755,202713771,675932866,79781699,956276337,652678397,35212756,655645460,468129309,
		761699708,533047427,287671032,206068022,50865043,144980423,111276893,259415897,444094191,593907889,
		573994984,892454686,566073550,128761001,888483202,251718753,548033568,428105027,742756734,546182474,
		62402409,102052166,826426395,159186619,926316039,176055335,51568171,414163604,604947226,681666415,
		511621808,924112080,265769800,955559118,763148293,472709375,19536133,860830935,290471030,851685235,
		242726978,169855231,612759169,599797734,961628039,953297493,62806842,37844313,909741023,689361523,
		887890124,380694152,669317759,367270918,806951470,843736533,377403437,945260111,786127243,80918046,
		875880304,364983542,623250998,598764068,804930040,24257676,214821357,791011898,954947696,183092975,
	};
	if(n>=MOD){
		return 0;
	}
	int t=n/10000000,ans=lst[t];
	for(int i=t*10000000+1;i<=n;i++){
		apmul(ans,i);
	}
	return ans;
}
int fac[K],invfac[K];
inline int c(int n,int m){
	return mul(fac[n],mul(invfac[m],invfac[n-m]));
}
int f[2][K];
inline int getans(int n,int ans){
	apmul(ans,n);
	apmul(ans,fpow(2,(lint)(n-1)*(n-2)/2%(MOD-1)));
	return ans;
}
inline int work(int n,int k){
	bool r=0;
	memset(f,0,sizeof(f));
	f[r][0]=1;
	for(int t=2;t<=n;t++){
		r=!r;
		f[r][0]=mul(mul(f[!r][0],2),inv(t-1));
		for(int i=1;i<=k;i++){
			lint sum=0;
			for(int j=0;j<i;j++){
				sum+=mul(c(i-1,j),f[!r][j]);
			}
			f[r][i]=sum%MOD;
		}
	}
	return mul(f[r][k],bigfac(n-1));
}
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
inline int Main(int n,int k){
	if(k==0){
		return fpow(2,n-1);
	}
	if(k==1){
		return n==1?0:mul(n-1,fpow(2,n-2));
	}
	if(n>=MOD){
		return 0;
	}else if(n<=1000000){
		gmath(n);
		lint ans=0;
		for(int i=0;i<n;i++){
			ans+=mul(c(n-1,i),fpow(i,k));
		}
		return ans%MOD;
	}else{
		gmath(k);
		return work(n,k);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("value.in","r",stdin);
	freopen("value.out","w",stdout);
#endif
	int n=ni,k=ni;
	printf("%d\n",getans(n,Main(n,k)));
	return 0;
}
