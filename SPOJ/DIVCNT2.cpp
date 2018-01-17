#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=100000010;
int divpoint;
int pri[N/10],ps=0;
int mu[N],mncnt[N],nopw[N];
bool np[N];
inline lint _mu2(lint n){
	lint ans=0,sqi;
	for(int i=1;sqi=(lint)i*i,sqi<=n;i++){
		ans+=mu[i]*n/sqi;
	}
	return ans;
}
struct classSig0{
	lint a[N];
	inline lint operator [] (lint n){
		if(n<=divpoint)return a[n];
		lint ans=0;
		for(lint l=1,r,d;l<=n;l=r+1){
			r=n/(d=n/l);
			ans+=(r-l+1)*d;
		}
		return ans;
	}
}_sig0;
inline void sieve(int n){
	divpoint=n;
	memset(np,0,sizeof(np));
	mu[1]=1,mncnt[1]=0,nopw[1]=1,_sig0.a[1]=1;
	lint *sig0=_sig0.a;
	sig0[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			pri[ps++]=i;
			mu[i]=-1;
			mncnt[i]=1;
			nopw[i]=1;
		}
		sig0[i]=sig0[nopw[i]]*(mncnt[i]+1);
		for(int j=0,p,t;j<ps&&(p=pri[j],t=p*i,t<=n);j++){
			np[t]=true;
			if(i%p){
				mu[t]=-mu[i];
				mncnt[t]=1;
				nopw[t]=i;
			}else{
				mu[t]=0;
				mncnt[t]=mncnt[i]+1;
				nopw[t]=nopw[i];
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		_sig0.a[i]+=_sig0.a[i-1];
	}
}
inline lint Main(lint n){
	lint ans=0,v1,v2,l=1,r,d;
	for(lint m=pow(n,2.0/3.0);l<=m;l++){
		if(mu[l]){
			ans+=_sig0[n/l];
		}
	}
	v1=_mu2(l-1);
	for(;l<=n;l=r+1,v1=v2){
		r=n/(d=n/l);
		v2=_mu2(r);
		ans+=(v2-v1)*_sig0[d];
	}
	return ans;
}
lint q[10010];
int main(){
#ifndef ONLINE_JUDGE
	freopen("divcnt2.in","r",stdin);
	freopen("divcnt2.out","w",stdout);
#endif
	int tot=ni;
	lint mx=0;
	for(int i=1;i<=tot;i++){
		apmax(mx,q[i]=next_num<lint>());
	}
	sieve(min((int)pow(mx,2.0/3.0)+10,N-1));
	for(int i=1;i<=tot;i++){
		printf("%lld\n",Main(q[i]));
	}
	return 0;
}
