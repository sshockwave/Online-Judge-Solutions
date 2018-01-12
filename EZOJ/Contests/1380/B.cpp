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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=1010,O=998244353;
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
namespace brute1{
	const int N=1010*3;
	int fac[N],invfac[N];
	inline void gmath(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
			assert((lint)fac[i]*invfac[i]%O==1);
		}
	}
	inline int Main(int n,int m){
		gmath(n*=3);
		return (lint)fac[n]*invfac[m]%O*invfac[n-m]%O;
	}
}
int f[N][N*3][8];
int mp[6];
int bitcnt[8]={0};
int main(){
#ifndef ONLINE_JUDGE
	freopen("final.in","r",stdin);
	freopen("final.out","w",stdout);
#endif
	int n=ni,m=ni;
	if(m>n*3){
		puts("0");
		return 0;
	}
	int mask=0;
	for(int i=0;i<9;i++){
		mask|=ni<<i;
	}
	if(mask==(1<<4)){
		printf("%d\n",brute1::Main(n,m));
		return 0;
	}
	for(int s=1;s<8;s++){
		bitcnt[s]=bitcnt[s^(s&-s)]+1;
	}
	for(int i=0;i<6;i++){
		int x=i/3,y=i%3;
		int line[]={mask&7,(mask>>3)&7,(mask>>6)&7};
		if(y<=1){
			mp[i]=(line[x]>>(1-y))|((line[x+1]>>(1-y))<<3);
		}else{
			mp[i]=((line[x]<<1)&7)|(((line[x+1]<<1)&7)<<3);
		}
	}
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0,tj=min((i-1)*3,m);j<=tj;j++){
			for(int s=0;s<8;s++){
				lint F=f[i-1][j][s];
				if(F==0)continue;
				int mask=0;
				for(int k=0;k<3;k++){
					if((s>>k)&1){
						mask|=mp[k+3];
					}
				}
				for(int ts=0;ts<8;ts++){
					bool flag=true;
					int curmask=mask;
					for(int k=0;k<3;k++){
						if((ts>>k)&1){
							if(curmask&mp[k]){
								flag=false;
								break;
							}
							curmask|=mp[k];
						}
					}
					if(flag){
						(f[i][j+bitcnt[ts]][ts]+=F)%=O;
					}
				}
			}
		}
	}
	lint ans=0;
	for(int s=0;s<8;s++){
		ans+=f[n][m][s];
	}
	printf("%lld\n",ans%O);
	return 0;
}
