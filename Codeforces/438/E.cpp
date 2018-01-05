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
const int N=100010,O=998244353;
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
	const int SH=18,N=1<<SH;
	int n,sh,invn,mxn=0;
	int o[SH][N>>1],io[SH][N>>1];
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
			int wn=fpow(3,(O-1)/full),iwn=inv(wn);
			for(int j=0,w=1,iw=1;j<half;j++,w=(lint)w*wn%O,iw=(lint)iw*iwn%O){
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
	int* inv(const int a[],int n){
		static int* b=new int[N];
		assert(a!=b);
		assert(n);
		if(n==1){
			assert(a[0]);
			b[0]=::inv(a[0]);
			return b;
		}
		inv(a,n>>1);
		poly::init(n<<1);
		mem(b,n>>1);
		static int *ta=new int[N];
		memcpy(ta,a,n<<2),mem(ta,n);
		ntt(b),ntt(ta);
		for(int i=0;i<poly::n;i++){
			b[i]=((lint)(b[i]<<1)+O-(lint)ta[i]*b[i]%O*b[i]%O)%O;
		}
		ntt(b,-1);
		return b;
	}
	int* sqrt(const int a[],int n){
		static int* b=new int[N];
		assert(a!=b);
		assert(n);
		if(n==1){
			//can only deal with a[0]==1
			assert(a[0]==1);
			b[0]=1;
			return b;
		}
		sqrt(a,n>>1);
		static int *tb=new int[N];
		memset(b+(n>>1),0,(n>>1)<<2);
		memcpy(tb,inv(b,n),n<<2);
		poly::init(n<<1);
		mem(tb,n);
		static int *ta=new int[N];
		memcpy(ta,a,n<<2),mem(ta,n);
		ntt(tb),ntt(ta);
		for(int i=0;i<poly::n;i++){
			tb[i]=(lint)tb[i]*ta[i]%O;
		}
		ntt(tb,-1);
		static int inv2=::inv(2);
		for(int i=0;i<n;i++){
			b[i]=(lint)(b[i]+tb[i])*inv2%O;
		}
		return b;
	}
}
int c[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("child.in","r",stdin);
	freopen("child.out","w",stdout);
#endif
	int n=ni,m=ni;
	memset(c,0,sizeof(c));
	c[0]=1;
	for(int i=1;i<=n;i++){
		c[ni]=O-4;
	}
	int sh=0;
	for(;(1<<sh)<=m;sh++);
	poly::init(1<<(sh+1));
	memcpy(c,poly::sqrt(c,1<<sh),(m+1)<<2);
	c[0]=(c[0]+1)%O;
	memcpy(c,poly::inv(c,1<<sh),(m+1)<<2);
	for(int i=1;i<=m;i++){
		printf("%d\n",(c[i]<<1)%O);
	}
	return 0;
}
