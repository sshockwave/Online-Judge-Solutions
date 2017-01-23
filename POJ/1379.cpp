#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define M 1010
#define G 30
#define EPS 0.001
#define PI 3.1415926535898
using namespace std;
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int w,h,m;
inline double apmin(double &a,double b){
	if(a>b){
		a=b;
	}
}
inline double random(){
	return (double)rand()/(double)RAND_MAX;
}
struct coor{
	double x,y,d;
	coor gen(double delta){
		double theta;
		coor res;
		do{
			res.x=x+delta*cos(theta);
			res.y=y+delta*sin(theta);
			res.d=1e100;
			for(int i=0;i<30)
		}while(theta);
	}
};
inline void generate(){
	gx=random()*w,gy=random()*h,gest=est(gx,gy);
	double nx,ny,nest,mx,my,mest;
	for(double delta=max(w,h),theta;delta>EPS;delta*=0.8){
		mest=0;
		for(int i=0;i<G;i++){
			theta=random()*PI*2;
			nx=gx+delta*cos(theta);
			ny=gy+delta*sin(theta);
			nest=est(nx,ny);
			if(valid(nx,ny)&&nest>mest){
				mx=nx,my=ny,mest=nest;
			}
		}
		if(mest>gest){
			gx=mx,gy=my,gest=mest;
		}
	}
}
int main(){
	srand(time(0));
	for(int tot=nextInt();tot--;){
		w=nextInt(),h=nextInt(),m=nextInt();
		for(int i=0;i<m;i++){
			x[i]=nextInt(),y[i]=nextInt();
		}
		double ansx,ansy,aest=0;
		for(int i=0;i<G;i++){
			generate();
			if(gest>aest){
				aest=gest;
				ansx=gx,ansy=gy;
			}
		}
		printf("The safest point is (%.1f, %.1f).\n",(double)round(ansx*10)/10.0,(double)round(ansy*10)/10.0);
	}
}
