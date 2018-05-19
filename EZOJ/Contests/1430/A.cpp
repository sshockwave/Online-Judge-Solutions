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
const int N=100010,M=10000010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
namespace gmath{
	int fac[N+M],invfac[N+M];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int walk(int a,int b){
		return (lint)fac[a+b]*invfac[a]%O*invfac[b]%O;
	}
}
inline void getpw(int a[],int x,int n){
	a[0]=1;
	for(int i=1;i<=n;i++){
		a[i]=(lint)a[i-1]*x%O;
	}
}
int f[N];
int pw_a[M],pw_b[N],pw_ba[N],pw_1a[M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("table.in","r",stdin);
	freopen("table.out","w",stdout);
#endif
	const int m=ni,n=ni,a=ni,b=ni,p=ni,q=ni;
	gmath::main(n+m);
	for(int i=1;i<=n;i++){
		f[i]=ni;
	}
	const int inva=inv_pow(a);
	getpw(pw_a,a,m);
	getpw(pw_b,b,min(n,m));
	getpw(pw_ba,(O-(lint)b*inva%O)%O,n);
	getpw(pw_1a,inva,m);
	for(int tot=q;tot--;){
		int x=ni,y=ni;
		int ans=0;
		using gmath::walk;
		if(x<p){
			for(int i=1;i<=y;i++){
				int up=p-x-1,rig=y-i;
				ans=(ans+(lint)walk(up,rig)*pw_ba[rig]%O*pw_1a[up]%O*f[i])%O;
			}
			ans=(lint)ans*inva%O;
		}else if(x>p){
			for(int i=1;i<=y;i++){
				int dn=x-p,rig=y-i;
				if(dn<rig)continue;
				int bcnt=rig,acnt=dn-rig;
				ans=(ans+(lint)walk(acnt,bcnt)*pw_a[acnt]%O*pw_b[bcnt]%O*f[i])%O;
			}
		}else{
			ans=f[y];
		}
		printf("%d\n",ans);
	}
	return 0;
}
