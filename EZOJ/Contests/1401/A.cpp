#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int SH=18,N=1<<18,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace gmath{
	int fac[N],invfac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
}
namespace sieve{
	int pri[N];
	bool np[N];
	int pw[N];
	inline void main(int n,int e){
		memset(np+1,0,n);
		int ps=0;
		pw[0]=e==0,pw[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				pw[i]=fpow(i,e);
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				pw[t]=(lint)pw[i]*pw[p]%O;
				if(i%p==0)break;
			}
		}
	}
}
namespace poly{
	int sh,n,invn;
	int o[N],rev[N];
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		o[0]=1,rev[0]=1;
		for(int i=1,w=fpow(3,(O-1)/n);i<n;i++){
			o[i]=(lint)o[i-1]*w%O;
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
	}
	inline void ntt(int a[],int d=1){
		for(int i=0;i<n;i++){
			if(rev[i]<i){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				lint w=o[j<<(sh-i)];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
int f[N],g[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("exp.in","r",stdin);
	freopen("exp.out","w",stdout);
#endif
	int n=ni,m=ni;
	gmath::main(n);
	sieve::main(n,n);
	for(int i=0;i<=n;i++){
		int tmp=(lint)gmath::invfac[i]*gmath::invfac[n-i]%O;
		f[i]=i&1?(O-tmp)%O:tmp;
		g[i]=sieve::pw[i];
	}
	poly::init(n*2+1);
	poly::clr(f,n+1),poly::ntt(f);
	poly::clr(g,n+1),poly::ntt(g);
	for(int i=0;i<poly::n;i++){
		f[i]=(lint)f[i]*g[i]%O;
	}
	poly::ntt(f,-1);
	lint ans=0;
	sieve::main(n,m);
	for(int i=0,cur,last=0;i<n;i++,last=cur){
		cur=f[i+1];
		ans+=(lint)(cur-last)*sieve::pw[i]%O;
	}
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
