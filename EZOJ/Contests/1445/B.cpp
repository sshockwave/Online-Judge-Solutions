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
template<class T>inline void apabs(T &x){if(x<0)x=-x;}
const int N=1010,O=1000000007,INF=0x7f7f7f7f;
int n,m;
namespace gmath{
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
	int fac[N],invfac[N];
	inline int C(int n,int k){
		assert(k<=n);
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
	inline void main(int n=N-1){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
}
int coor[2][N],nxt[N];
int f[N];
inline int gf(int x){
	apabs(x);
	return x<=m?f[x]:0;
}
inline int calc2(int x[]){
	int l=x[nxt[0]]-m,r=x[nxt[0]]+m;
	for(int i=0;i=nxt[i],i<=n;){
		apmax(l,x[i]-m),apmin(r,x[i]+m);
	}
	lint ans=0;
	for(int i=l;i<=r;i++){
		int cur=1;
		for(int j=0;j=nxt[j],j<=n&&cur;){
			cur=(lint)cur*gf(i-x[j])%O;
		}
		ans+=cur;
	}
	return ans%O;
}
inline int calc(){
	return (lint)calc2(coor[0])*calc2(coor[1])%O;
}
inline int Main(){
	n=ni;
	const int p[4]={0,ni,p[1]+ni,n};
	gmath::main(m=ni);
	for(int i=0;i<=m;i++){
		f[i]=(m-i)&1?0:gmath::C(m,(m-i)>>1);
	}
	for(int i=1;i<=n;i++){
		const int x=ni,y=ni;
		coor[0][i]=y+x,coor[1][i]=y-x;
		nxt[i]=i+1;
	}
	lint a[4],b[4];
	lint ans=0;
	for(int i=1;i<=3;i++){
		a[i]=(nxt[0]=p[i-1]+1,nxt[p[i]]=n+1,calc)();
		b[i]=(nxt[0]=1,nxt[p[i-1]]=p[i]+1,calc)();
		ans-=a[i]*b[i]%O;
		for(int j=0;j<=3;j++){
			nxt[p[j]]=p[j]+1;
		}
	}
	ans+=a[1]*a[2]%O*a[3]%O+calc()*2;
	return (ans%O+O)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dark.in","r",stdin);
	freopen("dark.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
