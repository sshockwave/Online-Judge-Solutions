#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define EPS 1e-3
using namespace std;
double oa,ob,oc,od;
double f(double x){
	return oa*x*x*x+ob*x*x+oc*x+od;
}
double delta(double a,double b,double c){
	return b*b-4*a*c;
}
double root1(double a,double b,double c){
	return (-b-sqrt(delta(a,b,c)))/(a*2);
}
double root2(double a,double b,double c){
	return (-b+sqrt(delta(a,b,c)))/(a*2);
}
double workans(double x){
//	cout<<"end"<<endl;
	return (double)round(x*100)/100.0;
}
double bchop(double l,double r){
	if(r-l<EPS){
		return l;
	}
//	cout<<"("<<l<<","<<r<<")"<<endl;
	double mid=(l+r)/2;
	if(f(l)*f(mid)>0){
		return bchop(mid,r);
	}else{
		return bchop(l,mid);
	}
}
int main(){
	double x1,x2;
	cin>>oa>>ob>>oc>>od;
	x1=root1(oa*3,ob*2,oc);
	x2=root2(oa*3,ob*2,oc);
	printf("%.2f %.2f %.2f",workans(bchop(-101,x1)),workans(bchop(x1,x2)),workans(bchop(x2,101)));
}
