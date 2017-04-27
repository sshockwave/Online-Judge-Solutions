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
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=10010;
const double EPS=1e-10;
struct point{
	long double x,y;
	point(long double _x=0,long double _y=0):x(_x),y(_y){}
	inline friend point operator + (const point &a,const point &b){
		return point(a.x+b.x,a.y+b.y);
	}
	inline friend point operator - (const point &a,const point &b){
		return point(a.x-b.x,a.y-b.y);
	}
	inline point operator * (const long double &w){
		return (point){x*w,y*w};
	}
	inline long double len(){
		return sqrt(x*x+y*y);
	}
	inline point unit(){
		long double l=len();
		return point(x/l,y/l);
	}
}pt[N];
int w[N],n;
inline point cal(point p){
	point ans;
	for(int i=1;i<=n;i++){
		ans=ans+(pt[i]-p).unit()*w[i];
	}
	return ans;
}
int main(){
	n=ni;
	point ans;
	for(int i=1;i<=n;i++){
		pt[i].x=ni,pt[i].y=ni;
		w[i]=ni;
		ans=ans+pt[i]*w[i];
	}
	ans.x/=n,ans.y/=n;
	for(long double t=10000;t>EPS;t*=t>0.5?0.5:0.97){
		ans=ans+cal(ans)*t;
	}
	printf("%.3lf %.3lf",(double)ans.x,(double)ans.y);
}
