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
	const int RT=2010;
	int n,rt=0,ndrt;
	int pre[N],blk[RT];
	inline void init(int _n){
		n=_n+1;
		for(;rt*rt<n;rt++);
		ndrt=(n-1)/rt;
		memset(pre,0,sizeof(pre));
		memset(blk,0,sizeof(blk));
	}
	inline void add(int x,int v){
		int xd=x/rt;
		for(int i=x;i<n&&i/rt==xd;i++){
			apadd(pre[i],v);
		}
		for(int i=xd;i<=ndrt;i++){
			apadd(blk[i],v);
		}
	}
	inline int sum(int x){
		int ans=pre[x];
		if(x/rt){
			apadd(ans,blk[x/rt-1]);
		}
		return ans;
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
	B::init(n);
	for(int i=1;i<=n;i++){
		f[i]=mul(i,i);
		apadd(B::pre[i],add(f[i],(i%B::rt==0?0:B::pre[i-1])));
		apadd(B::blk[i/B::rt],f[i]);
	}
	for(int i=1;i<=B::ndrt;i++){
		apadd(B::blk[i],B::blk[i-1]);
	}
	while(tot--){
		int a=ni,b=ni,d=gcd(a,b),x=sub((nl/k(a,b))%MOD,f[d]),n=ni;
		B::add(d,x),apadd(f[d],x);
		int ans=0;
		for(int l=1,r;l<=n;l=r+1){
			r=n/(n/l);
			apadd(ans,mul(M[n/l],sub(B::sum(r),B::sum(l-1))));
		}
		printf("%d\n",ans);
	}
}