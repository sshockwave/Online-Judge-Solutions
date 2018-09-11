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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int O=998244353;
namespace poly{
	const int SH=18,N=1<<SH;
	int sh,n,invn,o[N],r[N];
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
	inline void g_init(){
		o[0]=1,r[0]=0;
		for(int i=1,w=fpow(3,(O-1)/N);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv_pow(n);
	}
	inline void clr(int a[],const int x){
		mset(a+x,0,n-x);
	}
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			const int full=1<<i,half=full>>1;
			for(int k=0;k<n;k+=full){
				for(int j=0;j<half;j++){
					const int p=a[k+j],q=(lint)a[k+j+half]*o[j<<(SH-i)]%O;
					a[k+j]=(p+q)%O;
					a[k+j+half]=(p+O-q)%O;
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
	int ta[N],tb[N];
	inline void conv(int a[],int b[],const int na,const int nb){
		init(na+nb-1);
		mcpy(ta,a,na),clr(ta,na),ntt(ta);
		mcpy(tb,b,nb),clr(tb,nb),ntt(tb);
		for(int i=0;i<n;i++){
			ta[i]=(lint)ta[i]*tb[i]%O;
		}
		ntt(ta,-1);
	}
}
int ans=0;
void solve(const int l,const int r,const int c[],int prod[],int pool[]){
	const int m=(l+r)>>1;
	if(l==r){
		prod[1]=(ans+ni)%O,prod[0]=(O+1-prod[1])%O;
		ans=((lint)prod[0]*c[0]+(lint)prod[1]*c[1])%O;
		printf("%d\n",ans);
		return;
	}
	const int len=r-l+1,lenl=m-l+1,lenr=r-m;
	solve(l,m,c,prod,pool);
	//cout
	{
		using namespace poly;
		init(len+1);
		mcpy(ta,c,len+1),clr(ta,len+1),ntt(ta);
		clr(tb,0);
		tb[0]=prod[0];
		for(int i=1;i<=lenl;i++){
			tb[n-i]=prod[i];
		}
		ntt(tb);
		for(int i=0;i<n;i++){
			ta[i]=(lint)ta[i]*tb[i]%O;
		}
		ntt(ta,-1);
		mcpy(pool,ta,lenr+1);
	}
	solve(m+1,r,pool,prod+lenl+1,pool+lenr+1);
	poly::conv(prod,prod+lenl+1,lenl+1,lenr+1);
	mcpy(prod,poly::ta,len+1);
}
int init_c[poly::N],prod[poly::N],pool[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("stormtrooper.in","r",stdin);
	freopen("stormtrooper.out","w",stdout);
#endif
	poly::g_init();
	memset(init_c,0,sizeof(init_c));
	memset(pool,0,sizeof(pool));
	ans=ni;
	for(int i=0;i<=ans;i++){
		init_c[i]=ans-i;
	}
	solve(1,ni,init_c,prod,pool);
	return 0;
}
