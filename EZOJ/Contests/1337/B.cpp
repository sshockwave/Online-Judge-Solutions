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
const int N=110,O=1000000007;
inline int fpow(int x,int n){
	lint ret=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			(ret*=x)%=O;
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int f[N][N];
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
int main(){
#ifndef ONLINE_JUDGE
	freopen("neuron.in","r",stdin);
	freopen("neuron.out","w",stdout);
#endif
	int n=ni;
	gmath(n-1);
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		int d=ni;
		for(int j=i-1;j>=0;j--){
			for(int k=n-2;k>=0;k--){
				lint tmp=f[j][k];
				for(int l=min(d-1,n-2-k);l>=0;l--){
					(f[j+1][k+l]+=tmp*invfac[l]%O)%=O;
				}
			}
		}
	}
	printf("%d\n",n);
	for(int i=2;i<=n;i++){
		printf("%lld\n",(lint)f[i][i-2]*fac[i-2]%O);
	}
	return 0;
}
