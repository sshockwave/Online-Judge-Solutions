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
const int dN=5010,O=1000000007;
inline int fpow(int x,int n){
	lint a=1;
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
int fact[dN],fs=0;
lint f[dN];
inline void addfact(int x,int e){
	for(int i=0,j=0;i<e;i++){
		for(int k=fs;j<k;j++){
			fact[fs++]=fact[j]*x;
		}
	}
}
int main(){
	int n=ni,k=ni;
	fact[fs++]=1;
	for(int x=2,e;x*x<=n;x++){
		for(e=0;n%x==0;n/=x,e++);
		addfact(x,e);
	}
	if(n!=1){
		addfact(n,1);
	}
	lint ans=0;
	for(int i=0;i<fs;i++){
		int d=fact[i];
		f[i]=fpow(k,(d+1)>>1);
		for(int j=0;j<i;j++){
			if(d%fact[j]==0){
				f[i]-=f[j];
			}
		}
		f[i]=(f[i]%O+O)%O;
		static int inv2=inv(2);
		ans+=d&1?f[i]*d%O:(f[i]*d%O*inv2%O);
	}
	printf("%lld\n",ans%O);
	return 0;
}
