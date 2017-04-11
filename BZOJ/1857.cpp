#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline double sqr(double x){
	return x*x;
}
const double EPS=1e-4;
struct point{
	double x,y;
}a,b,c,d;
double P,Q,R;
inline point operator + (point a,point b){
	return (point){a.x+b.x,a.y+b.y};
}
inline point operator * (point a,double b){
	return (point){a.x*b,a.y*b};
}
inline point operator / (point a,double b){
	return (point){a.x/b,a.y/b};
}
inline ostream & operator << (ostream & out,point a){
	out<<"("<<a.x<<","<<a.y<<")"<<endl;
	return out;
}
inline double dist(point a,point b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
inline double chop2(point x){
	point l=c,r=d,m1,m2;
	while(dist(l,r)>EPS){
		m1=(l*2+r)/3,m2=(l+r*2)/3;
		if(dist(m1,x)/R+dist(m1,d)/Q>dist(m2,x)/R+dist(m2,d)/Q){
			l=m1;
		}else{
			r=m2;
		}
	}
	return dist(l,x)*R+dist(l,d)*Q;
}
inline double chop1(){
	point l=a,r=b,m1,m2;
	while(dist(l,r)>EPS){
		m1=(l*2+r)/3,m2=(l+r*2)/3;
		if(dist(a,m1)/P+chop2(m1)>dist(a,m2)/P+chop2(m2)){
			l=m1;
		}else{
			r=m2;
		}
	}
	return dist(a,l)/P+chop2(l);
}
int main(){
	cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y>>d.x>>d.y>>P>>Q>>R;
	printf("%.2lf",chop1());
}
