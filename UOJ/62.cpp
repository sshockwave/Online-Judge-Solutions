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
const int N=100010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int mod_inv(int x){
	return fpow(x,O-2);
}
namespace sieve{
	int n;
	int pri[N],ps=0;
	bool np[N];
	int mu[N];
	inline void main(int _n){
		n=_n;
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
	inline void gpw(int pw[],int e){
		e=(e%(O-1)+O-1)%(O-1);
		pw[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pw[i]=fpow(i,e);
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				pw[t]=(lint)pw[i]*pw[p]%O;
				if(i%p==0)break;
			}
		}
	}
}
using sieve::mu;
int g[N];
int invpwd[N],pwe[N];
lint b[N];
inline void Main(int n){
	mset(b+1,0,n);
	for(int i=1;i<=n;i++){
		int a=next_num<lint>()*invpwd[i]%O;
		for(int j=1,k=i;k<=n;j++,k+=i){
			if(mu[j]){
				b[k]+=a*mu[j];
			}
		}
	}
	for(int i=1;i<=n;i++){
		b[i]%=O;
		if(b[i]<0){
			b[i]+=O;
		}
		if(b[i]!=0&&g[i]==0){
			puts("-1");
			return;
		}
		b[i]=(lint)b[i]*g[i]%O;
	}
	for(int i=1;i<=n;i++){
		lint x=0;
		for(int j=1,k=i;k<=n;j++,k+=i){
			if(mu[j]){
				x+=b[k]*mu[j];
			}
		}
		x=((lint)x%O*invpwd[i]%O+O)%O;
		printf("%lld ",x);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("round.in","r",stdin);
	freopen("round.out","w",stdout);
#endif
	int n=ni,c=ni,d=ni;
	sieve::main(n);
	sieve::gpw(pwe,c-d);
	sieve::gpw(invpwd,-d);
	{//g
		mset(g+1,0,n);
		for(int i=1;i<=n;i++){
			for(int j=1,k=i;k<=n;j++,k+=i){
				if(mu[j]){
					g[k]=((lint)g[k]+O+pwe[i]*mu[j])%O;
				}
			}
			g[i]=mod_inv(g[i]);
		}
	}
	for(int tot=ni;tot--;Main(n));
	return 0;
}
