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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
namespace sieve{
	const int N=1000010;
	bool np[N];
	int pri[N],ps=0;
	int mu[N];
	inline void main(int n){
		mu[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				mu[i]=-1;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				if(i%p){
					mu[t]=-mu[i];
				}else{
					mu[t]=0;
					break;
				}
			}
		}
	}
}
inline lint Main(int n,int r){
	lint ans=0;
	using sieve::mu;
	const static int denom=1000000;
	const static lint denom2=(lint)denom*denom;
	sieve::main(denom/r);
	for(int i=1;i<=n&&(lint)i*r<=denom;i++){
		if(mu[i]==0)continue;
		lint cur=0;
		lint lim2=denom2/((lint)r*r*i*i);
		lint nlim=n/i;
		for(lint a=1;a<=nlim&&a*a<=lim2;a++){
			lint b=sqrt((long double)denom2/((lint)r*r*i*i)-(lint)a*a);
			for(;b<=nlim&&a*a+b*b<=lim2;b++);
			apmin(b,nlim);
			for(;b>nlim||a*a+b*b>lim2;b--);
			if(b==0)break;
			cur+=b;
		}
		ans+=cur*mu[i];
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int n=ni,r=ni;
	if(n==1){
		puts("0");
	}else{
		printf("%lld\n",Main(n-1,r)+2);
	}
	return 0;
}
