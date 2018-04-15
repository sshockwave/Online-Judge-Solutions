#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <algorithm>
#include <complex>
#include <cmath>
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
const int N=100010;
template<int O>inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
template<int O>inline int inv(int x){
	return fpow<O>(x,O-2);
}
namespace poly{
	const int SH=17,N=1<<SH,g=5;
	int n,sh,r[N];
	inline void cpy(int a[],const int b[],int n){
		memcpy(a,b,n*sizeof(a[0]));
	}
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)*sizeof(a[0]));
	}
	inline void hb(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
	}
	template<int O>inline void ntt(int a[],int d=1){
		for(int i=0;i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
			if(r[i]<i){
				swap(a[r[i]],a[i]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			lint w=1;
			for(int j=0,wn=fpow<O>(g,(O-1)>>i);j<half;j++,w=w*wn%O){
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			const int invn=inv<O>(n);
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
	/*
	   int ta[N],tb[N];
	   template<int O>inline void _conv(int a[],int b[],int lena,int lenb,int tc[]){
	   cpy(ta,a,lena+1),clr(ta,lena+1),ntt<O>(ta);
	   cpy(tb,b,lenb+1),clr(tb,lenb+1),ntt<O>(tb);
	   for(int i=0;i<n;i++){
	   tc[i]=(lint)ta[i]*tb[i]%O;
	   }
	   ntt<O>(tc,-1);
	   }
	   int tc[N],td[N];
	   inline void conv(int a[],int b[],int lena,int lenb){//put to ta
	   const static int O=99991,O1=998244353,O2=924844033;
	   hb(lena+lenb+1);
	   _conv<O1>(a,b,lena,lenb,tc);
	   _conv<O2>(a,b,lena,lenb,td);
	   for(int i=0;i<n;i++){
	   const static int inv1=inv<O1>(O2),inv2=inv<O2>(O1);
	   const static lint OO=(lint)O1*O2;
	   ta[i]=((lint)tc[i]*inv1%O1*O2+(lint)td[i]*inv2%O2*O1)%OO%O;
	   }
	   delete[] a;
	   delete[] b;
	   }*/
	typedef complex<double>comp;
	comp o[SH][N>>1];
	inline void init(){
		for(int i=0;i<SH;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				o[i][j]=comp(cos(M_PI*2*j/full),sin(M_PI*2*j/full));
			}
		}
	}
	inline void fft(comp a[],int d=1){
		for(int i=0;i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
			if(r[i]<i){
				swap(a[r[i]],a[i]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				comp w=o[i-1][j];
				for(int k=j;k<n;k+=full){
					comp p=a[k],q=a[k+half]*w;
					a[k]=p+q;
					a[k+half]=p-q;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			//cout
		}
	}
	int ta[N];
	comp tb[N],tc[N];
	inline void conv(int a[],int b[],int lena,int lenb){
		const static int O=99991;
		hb(lena+lenb+1);
		for(int i=0;i<=lena;i++){
			tb[i]=a[i];
		}
		for(int i=lena+1;i<n;i++){
			tb[i]=0;
		}
		for(int i=0;i<=lenb;i++){
			tc[i]=b[i];
		}
		for(int i=lenb+1;i<n;i++){
			tc[i]=0;
		}
		fft(tb),fft(tc);
		for(int i=0;i<n;i++){
			tb[i]*=tc[i];
		}
		fft(tb,-1);
		for(int i=0;i<n;i++){
			ta[i]=(lint)(tb[i].real()/n+0.3)%O;
			assert(false);
			assert(fabs(tb[i].real()/n-(lint)(tb[i].real()/n+0.3))<0.2);//cout
		}
		/*
		   cout<<"conv([";
		   for(int i=0;i<=lena;i++){
		   cout<<a[i]<<",";
		   }
		   cout<<"],[";
		   for(int i=0;i<=lenb;i++){
		   cout<<b[i]<<",";
		   }
		   cout<<"])=[";
		   for(int i=0;i<=lena+lenb;i++){
		   cout<<ta[i]<<",";
		   }
		   cout<<"]"<<endl;*/
		delete[] a;
		delete[] b;
	}
	int* recur_solve(int a[],int l,int r,int k){
		if(l==r){
			int *f=new int[2];
			f[0]=1,f[1]=a[l];
			return f;
		}
		int m=(l+r)>>1;
		conv(recur_solve(a,l,m,k),recur_solve(a,m+1,r,k),min(k,m-l+1),min(k,r-m));
		int len=min(r-l+1,k);
		int *f=new int[len+1];
		cpy(f,ta,len+1);
		return f;
	}
	inline int solve(int a[],int n,int k){
		int *f=recur_solve(a,1,n,k);
		int ans=f[k];
		delete[] f;
		return ans;
	}
}
int a[N],b[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("see.in","r",stdin);
	freopen("see.out","w",stdout);
#endif
	const static int O=99991;
	int n=ni,k=ni;
	if(k<0||k>n){
		puts("0");
		return 0;
	}
	poly::init();
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	int c1=ni,c2=ni;
	if(k==0){
		printf("%d\n",c1);
		return 0;
	}
	c2=(lint)(c1+c2)*inv<O>(4)%O;
	c1=(c1+O-c2)%O;
	for(int i=1;i<=n;i++){
		b[i]=fpow<O>(O-1,a[i]);
	}
	int ans=(lint)c1*poly::solve(b,n,k)%O;
	for(int i=1;i<=n;i++){
		b[i]=fpow<O>(3,a[i]);
	}
	ans=(ans+(lint)c2*poly::solve(b,n,k))%O;
	printf("%d\n",ans);
	return 0;
}
