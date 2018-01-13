#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
const int N=1000010,K=41;//TODO
int prime[N/10],ps=0;
int faccnt[N],mfac[N],mcnt[N];
bool np[N];
int k;
uint f[N],g[N];
inline int gcnt(int n,int p){
	int cnt=0;
	for(;n%p==0;n/=p,cnt++);
	return cnt;
}
inline int mu(int n,int k){
	return mcnt[n]>k?0:faccnt[n];
}
inline void sieve(int n){
	memset(np,0,sizeof(np));
	faccnt[1]=1;
	mcnt[1]=0;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			faccnt[i]=-1;
			mfac[i]=i;
			mcnt[i]=1;
		}
		for(int j=0,p,t;j<ps&&(p=prime[j],t=i*p,t<=n);j++){
			np[t]=true;
			faccnt[t]=-faccnt[i];
			int cnt=gcnt(i,p)+1;
			if(cnt>mcnt[i]){
				mfac[t]=p,mcnt[t]=cnt;
			}else{
				mfac[t]=mfac[i],mcnt[t]=mcnt[i];
			}
			if(i%p==0)break;
		}
	}
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			f[i]+=mu(i,j);
		}
		for(int j=1;i*j<=n;j++){
			g[i*j]+=f[i]*mu(j,1);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	int n=ni;
	k=ni;
	sieve(N-1);
	uint ans=0;
	for(uint i=1;i<=(uint)n;i++){
		uint d=n/i;
		ans+=g[i]*d*d;
	}
	printf("%u\n",ans&((1u<<30)-1));
	return 0;
}
