#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const double EPS=1e-10;
template<class T>inline T sqr(T x){
	return x*x;
}
inline double part1(double x,double y,double r){
	double ans=0,ang=M_PI*2;
	if(x+EPS<r){
		double tmp=sqrt(sqr(r)-sqr(x));
		double L=max(y-tmp,0.0),R=y+tmp;
		ans+=(R-L)*x/2;
		double a=r,b=sqrt(sqr(y-L)+sqr(x)),c=R-L;
		ang-=acos((sqr(a)+sqr(b)-sqr(c))/(2*a*b));
	}
	if(y+EPS<r){
		double tmp=sqrt(sqr(r)-sqr(y));
		double L=max(x-tmp,0.0),R=x+tmp;
		ans+=(R-L)*y/2;
		double a=r,b=sqrt(sqr(x-L)+sqr(y)),c=R-L;
		ang-=acos((sqr(a)+sqr(b)-sqr(c))/(2*a*b));
	}
	return ans+sqr(r)*ang/2;
}
inline double F(double x,double y){
	double r=sqrt(sqr(x)+sqr(y));
	return r*x+sqr(y)*log(fabs(x+r));
}
inline double part2(double x,double y,double z,double t){
	if(y>t*z-EPS){
		return 0;
	}
	double r=sqrt(sqr(t*z)-sqr(y)),l=max(x-r,0.0)-x;
	return (r-l)*z-(F(r,y)-F(l,y))/(t*2);
}
inline double Main(){
	double x,y,z,ang;
	scanf("%lf%lf%lf%lf",&x,&y,&z,&ang);
	double t=tan(ang);
	return part1(x,y,z*t)+part2(x,y,z,t)+part2(y,x,z,t);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("lamp.in","r",stdin);
	freopen("lamp.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%.4lf\n",Main()));
	return 0;
}
