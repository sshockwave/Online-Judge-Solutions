#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define PI 3.14159265
using namespace std;
inline double round2(double x){
	return (double)round(x*100)/100;
}
int main(){
	int n;
	scanf("%d",&n);
	double x=0,y=0,r=0,l=0,sum=0;
	while(n--){
		scanf("%lf%lf",&r,&l);
		sum+=r;
		x+=cos(sum*PI/180.0)*l;
		y+=sin(sum*PI/180.0)*l;
	}
	printf("%.2lf %.2lf",round2(x),round2(y));
}
