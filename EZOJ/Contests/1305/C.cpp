#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=4000010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int n;
namespace B{
	int c[N];
	inline int lowbit(const int &x){
		return x&(-x);
	}
	inline void init(){
		memset(c,0,sizeof(c));
	}
	inline void add(int x,int v){
		for(;x<=n;apadd(c[x],v),x+=lowbit(x));
	}
	inline int sum(int x){
		int ret=0;
		for(;x;apadd(ret,c[x]),x^=lowbit(x));
		return ret;
	}
}
int M[N],phi[N],prime[N],ps=0;
bool np[N];
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
inline void sieve(){
	memset(np,0,sizeof(np));
	phi[1]=M[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			phi[i]=i-1;
		}
		M[i]=add(M[i-1],mul(mul(i,i),phi[i]));
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
int f[N];
inline lint k(int a,int b){
	int d=gcd(a,b);
	return (lint)a*b/d/d;
}
int main(){
	int tot=ni;
	n=ni;
	sieve();
	B::init();
	for(int i=1;i<=n;i++){
		f[i]=mul(i,i);
		B::add(i,f[i]);
	}
	bool flag=true;
	while(tot--){
		int a=ni,b=ni,d=gcd(a,b),x=sub((nl/k(a,b))%MOD,f[d]),n=ni;
		if(x){
			flag=false;
		}
		if(flag){
			static int rev2=(MOD+1)>>1;
			printf("%d\n",mul(mul(mul(n,n+1),rev2),mul(mul(n,n+1),rev2)));
			continue;
		}
		B::add(d,x),apadd(f[d],x);
		int ans=0;
		for(int l=1,r;l<=n;l=r+1){
			r=n/(n/l);
			apadd(ans,mul(M[n/l],sub(B::sum(r),B::sum(l-1))));
		}
		printf("%d\n",ans);
	}
}