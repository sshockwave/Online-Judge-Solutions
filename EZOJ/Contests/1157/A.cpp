#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
using namespace std;
typedef long long lint;
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
inline double sqr(double x){
	return x*x;
}
inline double cub(double x){
	return x*x*x;
}
inline bool iszero(double x){
	static const double EPS=1e-9;
	return x>=-EPS&&x<=EPS;
}
inline double cbrt(double x){
	double y=x>=0?pow(x,1.0/3.0):-pow(-x,1.0/3.0);
	for(int i=1;i<=10;i++){
		y-=(cub(y)-x)/(sqr(y)*2);
	}
	assert(iszero(cub(y)-x));
	return y;
}
double B,C,D;
inline double F(double x){
	return ((x+B)*x+C)*x+D;
}
inline double dF(double x){
	return (3*x+B*2)*x+C;
}
inline double newt(double x){
	for(int i=1;i<=100;i++){
		x-=F(x)/dF(x);
	}
	assert(iszero(F(x)));
	return x;
}
inline double mxrt(){
	double p=C-sqr(B)/3,q=D+cub(B)*2/27-B*C/3;
	double a=-q/2,delta=sqr(q/2)+cub(p/3);
	double ans=0;
	if(delta>0){
		double b=sqrt(delta);
		ans=cbrt(a+b)+cbrt(a-b);
	}
	if(delta<=0){
		double b=sqrt(-delta);
		typedef complex<double>comp;
		comp T1(a,b),T2(a,-b);
		static const double ot=1.0/3.0;
		T1=pow(T1,ot),T2=pow(T2,ot);
		static const comp w1(-0.5,sqrt(3)/2),w2(-0.5,-sqrt(3)/2);
		ans=(T1+T2).real();
		apmax(ans,(T1*w1+T2*w2).real());
		apmax(ans,(T1*w2+T2*w1).real());
	}
	return newt(ans-B/3);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ellipsoid.in","r",stdin);
	freopen("ellipsoid.out","w",stdout);
#endif
	double a,b,c,d,e,f;
	while(scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f)!=EOF){
		B=-2*(a+b+c);
		C=(4*(a*b+b*c+a*c)-sqr(d)-sqr(e)-sqr(f));
		D=2*(a*sqr(d)+b*sqr(e)+c*sqr(f)-4*a*b*c-d*e*f);
		printf("%.10lf\n",sqrt(2/mxrt()));
	}
	return 0;
}
