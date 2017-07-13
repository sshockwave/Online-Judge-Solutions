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
const double EPS=1e-7;
inline double okay(double x){
	return x>=-EPS&&x<=EPS;
}
double a,b;
inline double f(double x){
	return sqrt(a*(1-x*x/b));
}
inline double simpson(double l,double m,double r,double fl,double fm,double fr,double est){
	double lm=(l+m)*0.5,flm=f(lm),le=(fl+flm*4+fm)/6;
	double rm=(l+m)*0.5,frm=f(rm),re=(fm+frm*4+fr)/6;
	return okay(le+re-est)?le+re:simpson(l,lm,m,fl,flm,fm,le)+simpson(m,rm,r,fm,frm,fr,re);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("integrate.in","r",stdin);
	freopen("integrate.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		double l,r;
		scanf("%lf%lf%lf%lf",&l,&r,&a,&b);
		printf("%.10lf\n",simpson(l,(l+r)*0.5,r,f(l),f((l+r)*0.5),f(r),(f(l)+f((l+r)*0.5)*4+f(r))/6));
	}
}
