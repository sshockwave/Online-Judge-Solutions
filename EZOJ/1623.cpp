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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
inline int fpow(int x,int n,int p){
	int ans=1;
	for(;n;n>>=1,x=(lint)x*x%p){
		if(n&1){
			ans=(lint)ans*x%p;
		}
	}
	return ans;
}
const int N=10000010,Q=10;
int phi[N],prime[N],ps=0;
bool np[N];
inline int inv(int x,int p){
	return fpow(x,phi[p]-1,p);
}
inline void sieve(int n){
	memset(np,0,sizeof(np));
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			phi[i]=i-1;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				phi[i*cur]=phi[i]*cur;
				break;
			}else{
				phi[i*cur]=phi[i]*phi[cur];
			}
		}
	}
}
int b[Q],m[Q];
int main(){
#ifndef ONLINE_JUDGE
	freopen("eqn.in","r",stdin);
	freopen("eqn.out","w",stdout);
#endif
	int n=ni,mx=0;
	lint prod=1;
	for(int i=1;i<=n;i++){
		b[i]=ni;
		apmax(mx,m[i]=ni);
		prod*=m[i];
	}
	sieve(mx);
	lint ans=0;
	for(int i=1;i<=n;i++){
		(ans+=(lint)b[i]*inv(prod/m[i]%m[i],m[i])%m[i]*(prod/m[i]))%=prod;
	}
	printf("%lld\n",ans);
}
