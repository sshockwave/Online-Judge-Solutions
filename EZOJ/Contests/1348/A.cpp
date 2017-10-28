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
template<class T>inline T sqr(T x){
	return x*x;
}
struct Pt{
	double x,y;
	inline void in(){x=ni,y=ni;}
	inline double d2(){return sqr(x)+sqr(y);}
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend Pt operator * (const Pt &a,const int &b){return (Pt){a.x*b,a.y*b};}
	inline friend Pt operator / (const Pt &a,const int &b){return (Pt){a.x/b,a.y/b};}
}A,B,C,D;
double P,Q,R;//R:plane
inline double trifind2(Pt fr){
	Pt l=C,r=D;
	while(((r-l).d2()>1e-7)){//tocheck
		Pt m1=(l*2+r)/3,m2=(l+r*2)/3;
		double v1=sqrt((fr-m1).d2())/R+sqrt((m1-D).d2())/Q;
		double v2=sqrt((fr-m2).d2())/R+sqrt((m2-D).d2())/Q;
		if(v1>v2){
			l=m1;
		}else{
			r=m2;
		}
	}
	return sqrt((fr-l).d2())/R+sqrt((l-D).d2())/Q;
}
inline double trifind1(){
	Pt l=A,r=B;
	while(sqrt((r-l).d2())>1e-7){
		Pt m1=(l*2+r)/3,m2=(l+r*2)/3;
		double v1=trifind2(m1)+sqrt((m1-A).d2())/P;
		double v2=trifind2(m2)+sqrt((m2-A).d2())/P;
		if(v1>v2){
			l=m1;
		}else{
			r=m2;
		}
	}
	return trifind2(l)+sqrt((l-A).d2())/P;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tape.in","r",stdin);
	freopen("tape.out","w",stdout);
#endif
	A.in(),B.in(),C.in(),D.in();
	P=ni,Q=ni,R=ni;
	printf("%.2lf\n",trifind1());
	return 0;
}
