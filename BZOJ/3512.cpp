#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=1000010,O=1000000007;
int invnum[N]={0,1};
int prime[N/10],ps=0;
int mu[N]={0,1},phi[N]={0,1},prephi[N]={0,1},mnfac[N]={0,1};
int sqf[N]={0,1};
bool np[N];
int f[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		invnum[i]=(lint)(O-O/i)*invnum[O%i]%O;
		assert((lint)invnum[i]*i%O==1);
		if(!np[i]){
			prime[ps++]=i;
			phi[i]=i-1;
			mu[i]=-1;
			sqf[i]=i;
			mnfac[i]=i;
		}
		prephi[i]=(prephi[i-1]+phi[i])%O;
		for(int j=0,p,t;j<ps&&(p=prime[j],t=i*p,t<=n);j++){
			np[t]=true;
			mnfac[t]=p;
			if(i%p){
				mu[t]=-mu[i];
				phi[t]=phi[i]*phi[p];
				sqf[t]=sqf[i]*p;
			}else{
				mu[t]=0;
				phi[t]=phi[i]*p;
				sqf[t]=sqf[i];
				break;
			}
		}
	}
}
int overall,cche[N];
int _phi(int n){
	if(n<N)return prephi[n];
	if(cche[overall/n]!=-1)return cche[overall/n];
	lint ans=(lint)n*(n+1)/2%O;
	for(int l=2,r,d;l<=n;l=r+1){
		r=n/(d=n/l);
		ans-=(lint)(r-l+1)*_phi(d)%O;
	}
	return cche[overall/n]=(ans%O+O)%O;
}
int Sup(int i,int m){
	if(m==0)return 0;
	if(m==1)return phi[i];
	if(i==1)return _phi(m);
	int p=mnfac[i];
	return ((lint)Sup(i/p,m)*(p-1)+Sup(i,m/p))%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
#endif
	memset(cche,-1,sizeof(cche));
	sieve(N-1);
	int n=ni,m=ni;
	if(n>m){
		swap(n,m);
	}
	overall=m;
	lint ans=0;
	for(int i=1;i<=n;i++){
		if(sqf[i]==i){
			f[i]=Sup(i,m);
		}
		ans+=(lint)i/sqf[i]*f[sqf[i]];
	}
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
