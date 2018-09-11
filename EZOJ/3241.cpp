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
char outputbuf[2000000],*ous=outputbuf;
char inputbuf[2000000];
inline char gc(){
	static char *qh=inputbuf;
	return *(qh++);
}
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=gc())&&c!='-');
	bool neg=c=='-';
	neg?c=gc():0;
	while(i=i*10-'0'+c,isdigit(c=gc()));
	return neg?-i:i;
}
inline void putnum(int x){
	static char tmp[20];
	char *ts=tmp;
	for(;x;x/=10){
		*(ts++)=x%10+'0';
	}
	if(ts>tmp){
		for(;ts>tmp;*(ous++)=*--ts);
	}else{
		*(ous++)='0';
	}
	*(ous++)='\n';
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int O=998244353;
namespace poly{
	const int SH=17,N=1<<SH;
	int sh,n,invn,*o[SH],r[N];
	int hlen[N];
	int shinv[SH+1];
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
		r[0]=0;
		for(int i=0;i<SH;i++){
			const int half=1<<i,full=half<<1;
			o[i]=new int[half];
			o[i][0]=1;
			const int w=fpow(3,(O-1)/full);
			for(int j=1;j<half;j++){
				o[i][j]=(lint)o[i][j-1]*w%O;
			}
		}
		for(int i=0;i<=SH;i++){
			shinv[i]=inv_pow(1<<i);
		}
		hlen[0]=0;
		for(int i=1;i<N;i++){
			for(int &s=hlen[i]=hlen[i-1];(1<<s)<i;s++);
		}
	}
	inline void init(int _n){
		sh=hlen[_n],n=1<<sh,invn=shinv[sh];
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
		{//i==0
			const int w=o[0][0];
			for(int k=0;k<n;k+=2){
				const int p=a[k];
				const lint q=(lint)a[k+1]*w;
				a[k]=(p+q)%O;
				a[k+1]=(p-q)%O;
			}
		}
		for(int i=1;i<sh;i++){
			const int half=1<<i,full=half<<1;
			const int *w=o[i];
			for(int k=0;k<n;k+=full){
				for(int j=0;j<half;j+=2){
					int p=a[k+j];
					lint q=(lint)a[k+j+half]*w[j];
					a[k+j]=(p+q)%O;
					a[k+j+half]=(p-q)%O;
					p=a[k+j+1];
					q=(lint)a[k+j+1+half]*w[j+1];
					a[k+j+1]=(p+q)%O;
					a[k+j+1+half]=(p-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i+=2){
				a[i]=(lint)a[i]*invn%O;
				a[i+1]=(lint)a[i+1]*invn%O;
			}
		}
	}
	int ta[N],tb[N];
}
int ans=0,hp;
void solve(const int l,const int r,const int c[],int prod[],int pool[],bool flag){
	const int m=(l+r)>>1;
	const int len=r-l+1,lenl=m-l+1,lenr=r-m;
	if(r-l<=150){
		prod[0]=1;
		mset(prod+1,0,len);
		for(int i=1;i<=len;i++){
			const int p=(ans+ni)%O,p1=O+1-p;
			if(l+i-1<=hp){
				for(int j=i;j>=1;j--){
					prod[j]=((lint)prod[j-1]*p+(lint)prod[j]*p1)%O;
				}
				prod[0]=(lint)prod[0]*p1%O;
				ans=(ans+O-p)%O;
			}else{
				ans=0;
				for(int j=i;j>=1;j--){
					prod[j]=((lint)prod[j-1]*p+(lint)prod[j]*p1)%O;
					ans=(ans+(lint)prod[j]*c[j])%O;
				}
				prod[0]=(lint)prod[0]*p1%O;
				ans=((ans+(lint)prod[0]*c[0])%O+O)%O;
			}
			putnum(ans);
		}
		return;
	}
	solve(l,m,c,prod,pool,true);
	if(r>hp){
		using namespace poly;
		init(len+1);
		mcpy(ta,c,len+1),clr(ta,len+1),ntt(ta);
		clr(tb,0);
		tb[0]=prod[0];
		for(int i=1;i<=lenl;i++){
			tb[n-i]=prod[i];
		}
		ntt(tb);
		for(int i=0;i<n;i+=2){
			ta[i]=(lint)ta[i]*tb[i]%O;
			ta[i+1]=(lint)ta[i+1]*tb[i+1]%O;
		}
		ntt(ta,-1);
		mcpy(pool,ta,lenr+1);
	}
	solve(m+1,r,pool,prod+lenl+1,pool+lenr+1,flag);
	if(flag){
		using namespace poly;
		init(len+1);
		mcpy(ta,prod+lenl+1,lenr+1),clr(ta,lenr+1),ntt(ta);
		clr(prod,lenl+1),ntt(prod);
		for(int i=0;i<n;i+=2){
			prod[i]=(lint)prod[i]*ta[i]%O;
			prod[i+1]=(lint)prod[i+1]*ta[i+1]%O;
		}
		ntt(prod,-1);
	}
}
int init_c[poly::N],prod[poly::N<<1],pool[poly::N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("stormtrooper.in","r",stdin);
	freopen("stormtrooper.out","w",stdout);
#endif
	fread(inputbuf,1,2000000,stdin);
	poly::g_init();
	memset(init_c,0,sizeof(init_c));
	ans=hp=ni;
	for(int i=0;i<=ans;i++){
		init_c[i]=ans-i;
	}
	solve(1,ni,init_c,prod,pool,false);
	*ous='0';
	fwrite(outputbuf,1,ous-outputbuf,stdout);
	return 0;
}
