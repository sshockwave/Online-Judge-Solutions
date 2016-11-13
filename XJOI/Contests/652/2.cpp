#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define N 100010
#define EPS 0.001
#define INF 1010
using namespace std;
long double x[N];
int y[N],z[N],n;
long double fpow(long double a,int b){
	if(b<0){
		return 0;
	}
	if(b==0){
		return 1;
	}
	long double tmp=fpow(a,b>>1);
	return tmp*tmp*(b&1?a:1);
}
inline long double cal(long double x0){
	long double ans=0;
	for(int i=1;i<=n;i++){
		if(x0<x[i]){
			ans-=y[i]*fpow(x[i]-x0,y[i]-1);
		}else if(x0>x[i]){
			ans+=z[i]*fpow(x0-x[i],z[i]-1);
		}
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%d%d",x+i,y+i,z+i);
	}
	long double l=-INF,r=INF,mid;
	while(r-l>EPS){
		mid=(l+r)/2;
		if(cal(mid)<0){
			l=mid;
		}else{
			r=mid;
		}
	}
	printf("%.2f",(long double)round(l*100)/100);
}
