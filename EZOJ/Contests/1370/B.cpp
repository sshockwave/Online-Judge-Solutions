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
const int N=3010;
int O;
int inv[N];
inline void gmath(int n){
	inv[1]=1;
	for(int i=2;i<=n;i++){
		inv[i]=(lint)(O-O/i)*inv[O%i]%O;
		assert((lint)inv[i]*i%O==1);
	}
}
int f[N],g[N];
int invf[N];
int sumfg[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
#endif
	int n=ni;
	O=ni;
	gmath(n);
	memset(sumfg,0,sizeof(sumfg));
	memset(g,0,sizeof(g));
	f[0]=0,f[1]=1;
	for(int i=1;i<=n;i++){
		sumfg[i]++;
	}
	invf[0]=invf[1]=1;
	for(int i=2;i<=n;i++){
		//get f[i]
		lint ans=0;
		for(int j=1;j<i;j++){
			ans+=(lint)f[j]*sumfg[i-j]%O;
		}
		f[i]=ans%O*inv[i-1]%O;
		//get invf[i]
		ans=0;
		for(int j=0;j<i;j++){
			ans+=(lint)invf[j]*f[i-j]%O;
		}
		invf[i]=ans%O;
		//get invsh[i]
		ans=0;
		if((i&1)==0){
			g[i]=invf[i>>1];
		}
		ans=0;
		for(int j=0;j<=i;j++){
			if((j&1)==0){
				ans+=(lint)invf[j>>1]*f[i-j]%O;
			}
		}
		g[i]=(g[i]+ans%O)%O;
		g[i]=(lint)(g[i]+invf[i])*inv[2]%O;
		g[i]=(g[i]-f[i]+O)%O;
		ans=(lint)(f[i]+g[i])*i%O;
		for(int j=i;j<=n;j+=i){
			sumfg[j]=(sumfg[j]+ans)%O;
		}
	}
	printf("%d\n",f[n]);
	return 0;
}
