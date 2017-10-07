#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=100010;
const double EPS=1e-6;
inline bool iszero(double x){
	return x>=-EPS&&x<=EPS;
}
struct Pt{
	int x,y;
}pt[N],pt1[N],pt2[N];
int ls1=0,ls2=0;
inline double F1(double x){
	int l=2,r=ls1;
	while(l<r){
		int m=(l+r)>>1;
		if(x>pt1[m].x){
			l=m+1;
		}else{
			r=m;
		}
	}
	assert(pt1[l-1].x!=pt1[l].x);
	return (x-pt1[l].x)/(pt1[l].x-pt1[l-1].x)*(pt1[l].y-pt1[l-1].y)+pt1[l].y;
}
inline double F2(double x){
	int l=2,r=ls2;
	while(l<r){
		int m=(l+r)>>1;
		if(x>pt2[m].x){
			l=m+1;
		}else{
			r=m;
		}
	}
	assert(pt2[l-1].x!=pt2[l].x);
	return (x-pt2[l].x)/(pt2[l].x-pt2[l-1].x)*(pt2[l].y-pt2[l-1].y)+pt2[l].y;
}
double x1,x2;
inline double three2(double x1){
	double y1=F1(x1),y2=F2(x1);
	double l=x1,r=pt1[ls1].x;
	while(r-l>EPS){
		double m1=(l*2+r)/3,m2=(l+r*2)/3;
		if((m1-x1)*(min(y1,F1(m1))-max(y2,F2(m1)))<(m2-x1)*(min(y1,F1(m2)-max(y2,F2(m2))))){
			l=m1;
		}else{
			r=m2;
		}
	}
	x2=l;
	return (l-x1)*(min(y1,F1(l))-max(y2,F2(l)));
}
inline void three1(){
	double l=pt1[1].x,r=pt1[ls1].x;
	double v1,v2;
	do{
		double m1=(l*2+r)/3,m2=(l+r*2)/3;
		v1=three2(m1),v2=three2(m2);
		if(v1<v2){
			l=m1;
		}else{
			r=m2;
		}
	}while(r-l>1e-3||!iszero(v1-v2));
	x1=l,three2(x1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
#endif
	int n=ni,ui=1,di=1;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		if(pt[i].x<pt[ui].x||(pt[i].x==pt[ui].x&&pt[i].y>pt[ui].y)){
			ui=i;
		}
		if(pt[i].x<pt[di].x||(pt[i].x==pt[di].x&&pt[i].y<pt[di].y)){
			di=i;
		}
	}
	for(pt1[0].x=pt[ui].x-1;pt1[ls1].x<pt[ui].x;pt1[++ls1]=pt[ui],ui=ui==n?1:ui+1);
	for(pt2[0].x=pt[di].x-1;pt2[ls2].x<pt[di].x;pt2[++ls2]=pt[di],di=di==1?n:di-1);
	three1();
	printf("%.10lf %.10lf %.10lf %.10lf\n",x1,max(F2(x1),F2(x2)),x2,min(F1(x1),F1(x2)));
	return 0;
}
