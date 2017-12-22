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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=30010,O=104857601;
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
namespace poly{
	const int SH=16,N=1<<SH;
	int sh,mxn=0,n,invn,m;
	int o[SH][N>>1],io[SH][N>>1];
	int *mod,tmod[N];
	inline ostream & operator << (ostream & out,int a[]){
		for(int i=0;i<n;i++){
			out<<a[i]<<" ";
		}
		return out;
	}
	inline void mem(int a[],int x=0){
		memset(a+x,0,(n-x)<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		if(n<=mxn)return;
		mxn=n;
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			int w=1,iw=1,wn=fpow(3,(O-1)/full),iwn=inv(wn);
			for(int j=0;j<half;j++,w=(lint)w*wn%O,iw=(lint)iw*iwn%O){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	int rev[N]={0};
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
			if(rev[i]<i){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				lint w=(d==1?o:io)[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=w*a[k+half]%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
	inline void inv(int a[],int b[],int n){
		if(n==1)return b[0]=::inv(a[0]),void();
		inv(a,b,n>>1);
		init(n<<1);
		mem(b,n>>1);
		static int *c=new int[N];
		memcpy(c,a,n<<2);
		mem(c,n);
		ntt(b),ntt(c);
		for(int i=0;i<poly::n;i++){
			b[i]=((b[i]<<1)%O+O-(int)((lint)c[i]*b[i]%O*b[i]%O))%O;
		}
		ntt(b,-1);
	}
	int tmp[N];
	inline void init(int polym[],int len){
		mod=polym,m=len;
		init(m*2-1);
		for(int i=0;i<=m;i++){
			tmp[i]=mod[m-i];
		}
		mem(tmp,m);
		inv(tmp,tmod,n>>1);
		init(m*2-1);
		mem(tmod,m),ntt(tmod);
		mem(mod,m+1),ntt(mod);
	}
	inline void gpow(int a[],lint exp){
		if(exp<m){
			init(m*2-1);
			mem(a,0);
			a[exp]=1;
			return;
		}
		gpow(a,exp>>1);
		ntt(a);
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*a[i]%O;
		}
		ntt(a,-1);
		if(exp&1){
			for(int i=(m-1)*2;i>=0;i--){
				a[i+1]=a[i];
			}
			a[0]=0;
		}
		for(int i=0,tt=2*m-1;i<m;i++){
			tmp[i]=a[tt-i];
		}
		mem(tmp,m),ntt(tmp);
		for(int i=0;i<n;i++){
			tmp[i]=(lint)tmp[i]*tmod[i]%O;
		}
		ntt(tmp,-1);
		for(int i=0,j=m-1;i<j;i++,j--){
			swap(tmp[i],tmp[j]);
		}
		mem(tmp,m),ntt(tmp);
		for(int i=0;i<n;i++){
			tmp[i]=(lint)tmp[i]*mod[i]%O;
		}
		ntt(tmp,-1);
		for(int i=0;i<m;i++){
			a[i]=(a[i]+O-tmp[i])%O;
		}
		mem(a,m);
	}
}
int a[poly::N],b[poly::N],c[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("rng.in","r",stdin);
	freopen("rng.out","w",stdout);
#endif
	int n=ni;
	lint expn=next_num<lint>();
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	c[n]=1;
	for(int i=1;i<=n;i++){
		c[n-i]=(O-ni)%O;
	}
	poly::init(c,n);
	poly::gpow(b,expn-1);
	lint ans=0;
	for(int i=0;i<n;i++){
		ans+=(lint)a[i]*b[i]%O;
	}
	printf("%lld\n",ans%O);
	return 0;
}
