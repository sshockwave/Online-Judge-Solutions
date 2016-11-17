#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define PI 3.14159265d
#define EPS 1e-8
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	double x=0,y=0,r=0,l=0,sum=0;
	while(n--){
		scanf("%lf%lf",&r,&l);
		sum+=r;
		x+=cos(sum/180*PI)*l;
		y+=sin(sum/180*PI)*l;
	}
	printf("%.2lf %.2lf",x+EPS,y+EPS);
	return 0;
}
