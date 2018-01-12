#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=10000010,O=998244353;
const int P=700000;
int prime[P],ps=0;
char mu[N];
bool np[N];
int pref[N];
const int M=6100000;
int lst[M],ls=0;
inline void sieve(int n){
	memset(np,0,sizeof(np));
	mu[1]=1;
	pref[1]=1;
	lst[ls++]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
		}
		pref[i]=pref[i-1]+(mu[i]!=0);
		if(mu[i]){
			lst[ls++]=i;
		}
		for(int j=0,cur=2,t;t=i*cur,j<ps&&t<=n;cur=prime[++j]){
			np[t]=1;
			if(i%cur){
				mu[t]=-mu[i];
			}else{
				mu[t]=0;
				break;
			}
		}
	}
}
lint rt=0;
inline lint F(lint n){
	if(n<=rt)return pref[n];
	lint ans=0,sqr;
	for(int i=0,j;j=lst[i],sqr=(lint)j*j,sqr<=n;i++){
		if(mu[j]==1){
			ans+=n/sqr;
		}else{
			ans-=n/sqr;
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
#endif
	lint n=next_num<lint>();
	for(;rt*rt<n;rt++);
	rt*=10;
	sieve(rt);
	int ans=0;
	lint cur,last=0;
	for(lint l=1,r,d;l<=n;l=r+1){
		r=n/(d=n/l);
		cur=F(r);
		ans=(ans+d*(cur-last))%O;
		last=cur;
	}
	printf("%d\n",ans);
	return 0;
}
