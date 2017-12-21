#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=10010,M=200010,O=998244353;
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
	const int SH=20,N=1<<SH;
	int sh,n,invn,mxn=0;
	int o[SH][N>>1],io[SH][N>>1];
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
				swap(a[rev[i]],a[i]);
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
	struct node{
		int *a,len;
		inline friend bool operator < (const node &a,const node &b){
			return a.len>b.len;
		}
		inline friend node operator * (const node &a,const node &b){
			node c=(node){0,a.len+b.len};
			init(c.len+1);
			c.a=new int[n];
			int *d=new int[n];
			memcpy(c.a,a.a,(a.len+1)<<2);
			memset(c.a+a.len+1,0,(n-a.len-1)<<2);
			memcpy(d,b.a,(b.len+1)<<2);
			memset(d+b.len+1,0,(n-b.len-1)<<2);
			delete[] a.a;
			delete[] b.a;
			ntt(c.a),ntt(d);
			for(int i=0;i<n;i++){
				c.a[i]=(lint)c.a[i]*d[i]%O;
			}
			ntt(c.a,-1);
			delete[] d;
			return c;
		}
	};
}
int fac[M],invfac[M];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
inline int C(int n,int k){
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
int a[N];
priority_queue<poly::node>q;
int f[poly::N],g[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
#endif
	int n=ni,m=0;
	for(int i=1;i<=n;i++){
		m+=a[i]=ni;
	}
	gmath(m),poly::init(m+1);
	for(int i=1;i<=n;i++){
		poly::node p;
		p.len=a[i];
		p.a=new int[a[i]+1];
		p.a[0]=0;
		for(int j=1;j<=a[i];j++){
			p.a[j]=(lint)C(a[i]-1,j-1)*invfac[j]%O;
		}
		q.push(p);
	}
	while(q.size()>1){
		poly::node a=q.top(),b=(q.pop(),q.top());
		q.pop(),q.push(a*b);
	}
	poly::init((m<<1)|1);
	memset(f,0,poly::n<<2);
	memset(g,0,poly::n<<2);
	memcpy(f,q.top().a,(m+1)<<2);
	for(int i=n,sig=fpow(O-1,n);i<=m;i++,sig=O-sig){
		f[i]=(lint)f[i]*fac[i]%O*sig%O*fac[m-i]%O;
	}
	for(int i=0;i<=m;i++){
		g[i]=invfac[i];
	}
	poly::ntt(f),poly::ntt(g);
	for(int i=0;i<poly::n;i++){
		f[i]=(lint)f[i]*g[i]%O;
	}
	poly::ntt(f,-1);
	for(int i=n,sig=fpow(O-1,n);i<=m;i++,sig=O-sig){
		f[i]=(lint)f[i]*sig%O*invfac[m-i]%O;
	}
	for(int tot=ni;tot--;){
		int k=ni;
		printf("%d\n",f[m-k]);
	}
	return 0;
}
