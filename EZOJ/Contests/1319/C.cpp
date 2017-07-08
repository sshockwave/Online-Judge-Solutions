#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
typedef long long lint;
typedef complex<double>comp;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,const int &b){
	if(b<a){
		a=b;
	}
}
int gcd(const int &a,const int &b){
	return b==0?a:gcd(b,a%b);
}
const int L=10010,M=110,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
int inv[L];
int n,m,p,p1;
namespace poly{
	const int SH=15,N=1<<SH;
	int n,sh,rev[N]={0};
	comp o[SH][N>>1],mo[SH][N>>1];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
		for(int i=1,sh1=sh-1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<sh1);
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			double ang=M_PI*2/full,cs=cos(ang),sn=sin(ang);
			comp w=1,mw=1,wn=comp(cs,sn),mwn=comp(cs,-sn);
			for(int j=0;j<half;j++,w*=wn,mw*=mwn){
				o[i][j]=w,mo[i][j]=mw;
			}
		}
	}
	inline void fft(comp a[],int d){
		for(int i=0;i<n;i++){
			if(i<rev[i]){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				comp w=(d==1?o:mo)[i][j];
				for(int k=j;k<n;k+=full){
					comp p=a[k],q=a[k+half]*w;
					a[k]=p+q,a[k+half]=p-q;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]/=n;
			}
		}
	}
	comp lo[N],hi[N],lh[N];
	void sqr(int a[]){
		const static int S=15,AND=(1<<S)-1;
		for(int i=0;i<n;i++){
			hi[i]=a[i]>>S;
			lo[i]=a[i]&AND;
		}
		fft(hi,1),fft(lo,1);
		for(int i=0;i<n;i++){
			lh[i]=lo[i]*hi[i];
			hi[i]*=hi[i],lo[i]*=lo[i];
		}
		fft(hi,-1),fft(lo,-1),fft(lh,-1);
		for(int i=0;i<n;i++){
			const static int t1=1<<(S+1),t2=mul(1<<S,1<<S);
			lint tmp=(lint)(lo[i].real()+0.5);
			tmp+=mul((lint)(hi[i].real()+0.5)%MOD,t2);
			tmp+=(lint)(lh[i].real()+0.5)*t1%MOD;
			a[i]=tmp%MOD;
		}
	}
	void pow(int a[],int n,int e){
		if(e==0){
			memset(a,0,n<<3);
			a[0]=1;
			init((n<<1)-1);
			return;
		}
		pow(a,n,e>>1),sqr(a);
		for(int i=n,tn=n<<1;i<tn;i++){
			apadd(a[i-n],a[i]);
		}
		memset(a+n,0,n<<2);
		if(e&1){
			int v=a[n-1];
			for(int i=n-1;i;i--){
				a[i]=add(mul(p1,a[i]),mul(p,a[i-1]));
			}
			a[0]=add(mul(p1,a[0]),mul(p,v));
		}
	}
}
int c[M],f[L];
inline int work(){
	n=ni,m=ni,p=ni,p1=100-p;
	{//get c
		int a[M],t=0;
		bool mark[M];
		memset(mark+1,0,m);
		for(int i=1;i<=m;i++){
			a[i]=ni;
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=m;i++){
			if(!mark[i]){
				c[++t]=a[i];
				for(int j=i+1;j<=m;j++){
					if(!mark[j]&&a[j]%a[i]==0){
						mark[j]=true;
					}
				}
			}
		}
		m=t;
	}
	int len=0,g=0;
	{//get len && g
		for(int i=1,v=c[m];i<=m;i++){
			apmax(len,v/gcd(v,c[i])*c[i]);
			g=gcd(c[i],g);
		}
		apmin(len,n);
	}
	int ans=0;
	if(g>1){//loop
		static int a[L];
		poly::pow(a,g,n);
		for(int i=0;i<g;i++){
			apadd(ans,mul(i,a[i]));
		}
	}
	{//dp
		memset(f,false,len<<2);
		f[0]=true;
		for(int i=1;i<=m;i++){
			for(int v=c[i],j=v;j<len;j++){
				f[j]|=f[j-v];
			}
		}
		f[len]=0;
		for(int i=len-1;i>=0;i--){
			f[i]=f[i]?0:f[i+1]+1;
		}
	}
	for(int i=0,c=1,w=fpow(p1,n),dw=mul(p,inv[p1]);i<len;i++){//len
		apadd(ans,mul(sub(f[i],i%g),mul(w,c)));
		apmul(w,dw),apmul(c,mul(n-i,inv[i+1]));
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flair.in","r",stdin);
	freopen("flair.out","w",stdout);
#endif
	inv[1]=1;
	for(int i=2;i<L;i++){
		inv[i]=mul(MOD-MOD/i,inv[MOD%i]);
	}
	for(int tot=ni;tot--;){
		printf("%d\n",work());
	}
}
