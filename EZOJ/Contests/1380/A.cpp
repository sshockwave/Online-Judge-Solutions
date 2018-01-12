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
const int N=1000010,O=998244353;
int _mu[N],prime[N/10],ps=0;
char mu[N];
bool np[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	_mu[0]=0;
	mu[1]=_mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
		}
		_mu[i]=_mu[i-1]+mu[i];
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
inline int F(lint n){
	lint ans=0;
	for(lint l=1,r,d;l<=n;l=r+1){
		r=n/(d=n/l);
		ans+=(r-l+1)*d;
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
#endif
	lint n=next_num<lint>();
	for(;rt*rt<n;rt++);
	sieve(rt);
	lint ans=0;
	for(lint l=1,r;l*l<=n;l=r+1){
		r=n/(n/l);
		ans+=(_mu[r]-_mu[l-1])*F(n/(l*l))%O;
	}
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
