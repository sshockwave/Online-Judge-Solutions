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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(b));}
const int N=22,K=10010,Q=2e5+10,O=998244353;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
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
	const int N=::K;
	int fac[N],ifac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		ifac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			ifac[i-1]=(lint)ifac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		return (lint)fac[n]*ifac[k]%O*ifac[n-k]%O;
	}
}
namespace poly{
	const int SH=15,N=1<<SH;
	int o[N],r[N];
	inline void init(){
		o[0]=1,r[0]=0;
		for(int i=1,w=fpow(3,(O-1)>>SH);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline int hb(int n){
		int sn=1;
		for(;sn<n;sn<<=1);
		return sn;
	}
	inline void ntt(int a[],int n,int d=1){
		assert(n==(n&-n));
		for(int i=1;i<n;i++){
			r[i]=(r[i>>1]>>1)|(i&1?n>>1:0);
			if(i<r[i]){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;(1<<i)<=n;i++){
			int full=1<<i,half=full>>1;
			for(int k=0;k<n;k+=full){
				for(int j=k;j<k+half;j++){
					int p=a[j];
					lint q=(lint)a[j+half]*o[(j-k)<<(SH-i)];
					a[j]=(p+q)%O;
					a[j+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			const int ivn=inv_pow(n);
			for(int i=0;i<n;i++){
				a[i]=(lint)(a[i]+O)*ivn%O;
			}
		}
	}
}
struct Mat{
	const static int N=32;
	int n,a[N][N];
	inline void id(){
		for(int i=1;i<=n;i++){
			mset(a[i]+1,0,n);
			a[i][i]=1;
		}
	}
	inline void operator = (const Mat &b){
		n=b.n;
		for(int i=1;i<=n;i++){
			mcpy(a[i]+1,b.a[i]+1,n);
		}
	}
	inline void gmul(const Mat &x,const Mat &y){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				lint ans=0;
				for(int k=1;k<=n;k++){
					ans+=(lint)x.a[i][k]*y.a[k][j];
					if(ans>LINF-(lint)O*O){
						ans%=O;
					}
				}
				a[i][j]=ans%O;
			}
		}
	}
}mat[N];
int f[N][K];
struct Worker{
	int n,g[poly::N];
	Worker(){
		n=0;
	}
	inline void work(int l,int r){
		const int sn=poly::hb(n*2+1);
		static int ta[poly::N];
		mset(g,0,sn),mset(ta,0,sn);
		for(int i=0;i<=n;i++){
			g[i]=gmath::ifac[i];
			ta[i]=gmath::ifac[i];
			if(i&1){
				ta[i]=O-ta[i];
			}
		}
		for(int i=l;i<=r;i++){
			for(int j=0;j<=n;j++){
				g[j]=(lint)g[j]*f[i][j]%O;
			}
		}
		poly::ntt(g,sn);
		poly::ntt(ta,sn);
		for(int i=0;i<sn;i++){
			g[i]=(lint)g[i]*ta[i]%O;
		}
		poly::ntt(g,sn,-1);
		for(int i=0;i<=n;i++){
			g[i]=(lint)g[i]*gmath::fac[i]%O;
		}
		g[0]=0;
		for(int i=1;i<=n;i++){
			g[i]=(g[i]+g[i-1])%O;
		}
	}
}worker[N][N];
int mxk[N];
inline void getmat(Mat &mat){
	mat.n=ni,mat.id();
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		mat.a[u][v]=1;
		mat.a[v][u]=1;
	}
}
struct Query{
	int l,r,k;
}qry[Q];
int a[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cholferry.in","r",stdin);
	freopen("cholferry.out","w",stdout);
#endif
	poly::init();
	const int n=ni;
	for(int i=1;i<=n;i++){
		getmat(mat[i]);
		mxk[i]=0;
	}
	const int q=ni;
	int totk=0;
	for(int i=1;i<=q;i++){
		qry[i]=(Query){ni,ni,ni};
		apmax(worker[qry[i].l][qry[i].r].n,qry[i].k);
		apmax(totk,qry[i].k);
		for(int j=qry[i].l;j<=qry[i].r;j++){
			apmax(mxk[j],qry[i].k);
		}
	}
	gmath::main(totk);
	for(int i=1;i<=n;i++){
		static Mat pw;
		for(int j=0;j<=mxk[i];j++){
			if(j){
				static Mat tmp;
				tmp=pw;
				pw.gmul(tmp,mat[i]);
			}else{
				pw.n=mat[i].n,pw.id();
			}
			lint sum=0;
			for(int k=1;k<=mat[i].n;k++){
				sum+=pw.a[k][k];
			}
			f[i][j]=sum%O;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			worker[i][j].work(i,j);
		}
	}
	for(int i=1;i<=q;i++){
		printf("%d\n",worker[qry[i].l][qry[i].r].g[qry[i].k]);
	}
	return 0;
}
