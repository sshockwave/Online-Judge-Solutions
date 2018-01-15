#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
const int N=1000010,O=1004535809;
int pri[N],ps=0,sqcnt=1;
int phi[N],mu[N],f[N],sqf[N];
bool np[N];
int g[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	phi[1]=1,mu[1]=1,f[1]=1,sqf[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			pri[ps++]=i;
			phi[i]=i-1;
			mu[i]=-1;
			sqf[i]=i;
		}
		if(sqf[i]==1){
			sqcnt++;
			assert(sqcnt*sqcnt==i);
			f[i]=phi[sqcnt]*sqcnt;
		}else{
			f[i]=(lint)f[i/sqf[i]]*sqf[i]%O;
		}
		for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
			np[t]=true;
			if(i%p){
				phi[t]=phi[i]*(p-1);
				mu[t]=-mu[i];
				sqf[t]=sqf[i]*p;
			}else{
				phi[t]=phi[i]*p;
				mu[t]=0;
				sqf[t]=sqf[i/p];
				break;
			}
		}
	}
	for(int i=1,sqi;sqi=i*i,sqi<=n;i++){
		for(int j=1,sqj;sqj=j*j,sqi+sqj<=n;j++){
			int p=sqi+sqj;
			for(int k=p;k<=n;k+=p){
				g[k]=(g[k]+i)%O;
			}
		}
	}
	for(int i=1;i<=n;i++){
		f[i]=(f[i-1]+f[i])%O;
		g[i]=(g[i-1]+g[i])%O;
	}
}
inline int _n2(lint n){
	n%=O;
	lint m=n+1;
	if(n&1){
		m>>=1;
	}else{
		n>>=1;
	}
	return m*n%O;
}
inline int F(lint n){
	if(n<N)return f[n];
	lint ans=0;
	for(lint i=1,sqi;sqi=i*i,sqi<=n;i++){
		ans+=(lint)mu[i]*i*_n2(n/sqi);
	}
	return (ans%O+O)%O;
}
inline int G(lint n){
	if(n<N)return g[n];
	lint ans=0;
	for(lint i=1,sqi;sqi=i*i,sqi<=n;i++){
		lint cur=0;
		for(lint j=1,sqj;sqj=j*j,sqi+sqj<=n;j++){
			cur+=n/(sqi+sqj);
		}
		ans+=cur%O*i%O;
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("div.in","r",stdin);
	freopen("div.out","w",stdout);
#endif
	sieve(N-1);
	lint n=next_num<lint>();
	lint ans=0;
	int cur,last=0;
	for(lint l=1,r,d;l<=n;l=r+1,last=cur){
		r=n/(d=n/l);
		cur=F(r);
		ans+=(lint)(cur+O-last)*G(d)%O;
	}
	ans=(ans<<1)%O;
	last=0;
	for(lint l=1,r,d;l<=n;l=r+1,last=cur){
		r=n/(d=n/l);
		cur=_n2(r);
		ans+=d*(cur+O-last)%O;
	}
	printf("%lld\n",ans%O);
	return 0;
}
