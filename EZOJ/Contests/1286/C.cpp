#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int SHIFT2=18,N2=1<<SHIFT2;
const double EPS=1e-3;
int n,MOD,rev[N2],N,SHIFT;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
struct comp{
	double r,i;
	comp(double _r=0,double _i=0):r(_r),i(_i){}
	inline friend comp operator + (const comp &a,const comp &b){
		return comp(a.r+b.r,a.i+b.i);
	}
	inline friend comp operator - (const comp &a,const comp &b){
		return comp(a.r-b.r,a.i-b.i);
	}
	inline friend comp operator * (const comp &a,const comp &b){
		return comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);
	}
}w1[N2>>1][SHIFT2+1],w2[N2>>1][SHIFT2+1];
inline comp omega(int i,int n){
	double angle=M_PI*2*i/n;
	return comp(cos(angle),sin(angle));
}
inline void dft(comp a[],bool inv){
	for(int i=0;i<N;i++){
		if(i<rev[i]){
			swap(a[i],a[rev[i]]);
		}
	}
	for(int i=1,full,half;i<=SHIFT;i++){
		full=1<<i,half=full>>1;
		for(int j=0;j<half;j++){
			comp w=inv?w2[j][i]:w1[j][i],p,q;
			for(int k=j;k<N;k+=full){
				p=a[k],q=a[k+half]*w;
				a[k]=p+q;
				a[k+half]=p-q;
			}
		}
	}
	if(inv){
		for(int i=0;i<N;i++){
			a[i].r/=N;
		}
	}
}
struct Poly{
	int x[N2];
	inline void operator *= (const Poly &b){
		static comp *ca=new comp[N2],*cb=new comp[N2];
		for(int i=0;i<n;i++){
			ca[i]=x[i],cb[i]=b.x[i];
		}
		for(int i=n;i<N;i++){
			ca[i]=cb[i]=0;
		}
		dft(ca,false),dft(cb,false);
		for(int i=0;i<N;i++){
			ca[i]=ca[i]*cb[i];
		}
		dft(ca,true);
		memset(x,0,n<<2);
		for(int i=0;i<N;i++){
			apadd(x[i%n],ca[i].r+EPS);
		}
	}
	inline void sqr(){
		static comp *ca=new comp[N];
		for(int i=0;i<n;i++){
			ca[i]=x[i];
		}
		for(int i=n;i<N;i++){
			ca[i]=0;
		}
		dft(ca,false);
		for(int i=0;i<N;i++){
			ca[i]=ca[i]*ca[i];
		}
		dft(ca,true);
		memset(x,0,n<<2);
		for(int i=0;i<N;i++){
			apadd(x[i%n],ca[i].r+EPS);
		}
	}
}trans,a;
int main(){
	n=ni,MOD=ni;
	for(N=1,SHIFT=0;N<(n<<1);N<<=1,SHIFT++);
	for(int i=1;i<=SHIFT;i++){
		for(int j=0;j<(1<<(i-1));j++){
			double angle=M_PI*2*j/(1<<i);
			w1[j][i]=comp(cos(angle),sin(angle));
			w2[j][i]=comp(w1[j][i].r,-w1[j][i].i);
		}
	}
	rev[0]=0;
	for(int i=1,s=1<<(SHIFT-1);i<N;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=s;
		}
	}
	int t=ni;
	for(int i=0;i<n;i++){
		a.x[i]=ni-1;
	}
	trans.x[0]=MOD-1,trans.x[n-1]=2;
	for(;t;t>>=1,trans.sqr()){
		if(t&1){
			a*=trans;
		}
	}
	for(int i=0;i<n;i++){
		printf("%d ",a.x[i]+1);
	}
}
