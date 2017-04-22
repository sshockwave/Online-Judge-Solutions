#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <complex>
#include <cmath>
#include <ctime>
using namespace std;
typedef long long lint;
typedef complex<double> comp;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int SHIFT=18,N=1<<SHIFT;
const double EPS=1e-3;
int n,MOD,rev[N];
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline comp omega(int i,int n){
	double angle=M_PI*2*i/n;
	return comp(cos(angle),sin(angle));
}
inline void dft(complex<double>a[],int inv){
	for(int i=0;i<N;i++){
		if(i<rev[i]){
			swap(a[i],a[rev[i]]);
		}
	}
	for(int i=2,half;i<N;i<<=1){
		half=i>>1;
		for(int j=0;j<half;j++){
			comp w=omega(j*inv,i),p,q;
			for(int k=j;k<N;k+=j){
				p=a[k],q=a[k+half]*w;
				a[k]=p+q;
				a[k+half]=p-q;
			}
		}
	}
	if(inv==-1){
		for(int i=0;i<N;i++){
			a[i]/=N;
		}
	}
}
struct Poly{
	int x[N];
	inline void operator *= (const Poly &b){
		static comp *ca=new comp[N],*cb=new comp[N];
		memset(ca,0,sizeof(ca));
		memset(cb,0,sizeof(cb));
		for(int i=0;i<n;i++){
			ca[i]=x[i],cb[i]=b.x[i];
		}
		dft(ca,1),dft(cb,1);
		for(int i=0;i<N;i++){
			ca[i]*=cb[i];
		}
		dft(ca,-1);
		memset(x,0,n<<2);
		for(int i=0;i<N;i++){
			apadd(x[i%n],ca[i].real()+EPS);
		}
	}
}trans,a;
int main(){
	rev[0]=0;
	for(int i=1,s=1<<(SHIFT-1);i<N;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=s;
		}
	}
	n=ni,MOD=ni;
	int t=ni;
	for(int i=0;i<n;i++){
		a.x[i]=ni-1;
	}
	for(;t;t>>=1,trans*=trans){
		if(t&1){
			a*=trans;
		}
	}
	for(int i=0;i<n;i++){
		printf("%d ",a.x[i]+1);
	}
}
