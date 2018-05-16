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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010;
namespace sieve{
	bool np[N];
	int pri[N],ps=0;
	int phi[N];
	inline void main(int n){
		phi[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				phi[i]=i-1;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				if(i%p){
					phi[t]=phi[i]*phi[p];
				}else{
					phi[t]=phi[i]*p;
					break;
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int n=ni;
	if(n==1){
		puts("0");
	}else{
		--n;
		sieve::main(n);
		lint ans=0;
		for(int i=2;i<=n;i++){
			ans+=sieve::phi[i];
		}
		ans=ans*2+1;
		printf("%lld\n",ans+2);
	}
	return 0;
}
