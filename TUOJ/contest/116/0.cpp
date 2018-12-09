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
namespace poly{
	const int SH=18,N=1<<SH;
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
		for(int i=1;i<n;i++){
			r[i]=(r[i>>1]>>1)|(i&1?n>>1:0);
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;(1<<i)<=n;i++){
			const int full=1<<i,half=full>>1;
			for(int k=0;k<n;k+=full){
				for(int j=k;j<k+half;j++){
					int p=a[j];
					lint q=(lint)a[j+half]*o[(j-k)<<(SH-i)];
					a[j]=(p+q)%O;
					a[j+half]=(p-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			int iv=inv_pow(n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*iv%O;
			}
		}
	}
	inline void pmul(int a[],const int b[],const int n){
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*b[i]%O;
		}
	}
	inline void inv(int b[],const int a[],const int sn){
		static int ta[N];
		assert(a[0]);
		mset(b,0,sn);
		b[0]=inv_pow(a[0]);
		for(int n=2;n<=sn;n<<=1){
			const int tn=n<<1;
			mcpy(ta,a,n),mset(ta+n,0,n),ntt(ta,tn);
			ntt(b,tn);
			for(int i=0;i<tn;i++){
				b[i]=(2ll*b[i]-(lint)ta[i]*b[i]%O*b[i])%O;
			}
			ntt(b,tn,-1),mset(b+n,0,n);
		}
	}
}
struct Mat{
	const static int N=2;
	int a[N][N];
	inline void gmul(const Mat &x,const Mat &y){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				int &ans=a[i][j]=0;
				for(int k=0;k<N;k++){
					ans=(ans+(lint)x.a[i][k]*y.a[k][j])%O;
				}
			}
		}
	}
};
inline void fpow(Mat x,int n,int &a,int &b){
	Mat tmp;
	for(;n;n>>=1,tmp.gmul(x,x),x=tmp){
		if(n&1){
			lint ta=a,tb=b;
			a=(x.a[0][0]*ta+x.a[0][1]*tb)%O;
			b=(x.a[1][0]*ta+x.a[1][1]*tb)%O;
		}
	}
}
inline void work(const int n,const int w,int &a,int &b){
	Mat t=(Mat){0,1,O-w,1};
	a=b=1,fpow(t,n,a,b);
}
int a[poly::N],b[poly::N],c[poly::N];
inline int Main(){
	const int n=ni,m=ni;
	if(n<m)return 0;
	const int sn=poly::hb(n+1);
	for(int i=0,tmpm=poly::N/sn;i<sn;i++){
		work(m,poly::o[i*tmpm],a[i],b[i]);
	}
	poly::ntt(b,sn,-1);
	poly::inv(c,b,sn);
	poly::ntt(c,sn);
	poly::pmul(a,c,sn);
	poly::ntt(a,sn,-1);
	return (a[n]+O)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	poly::init();
	printf("%d\n",Main());
	return 0;
}
