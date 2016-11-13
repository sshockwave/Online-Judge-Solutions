#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define EPS 0.0001
#define N 2020
using namespace std;
struct bullet{
	double x,y,t;
}b[N];
bool operator < (bullet a,bullet b){
	return a.t<b.t;
}
int f[N];
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline double sqr(double a){
	return a*a;
}
inline double abs(double a){
	return a>0?a:-a;
}
inline double process(double a){
	return (double)round(a*100)/100;
}
int main(){
	int n,m1,m2,d,ans=0;
	scanf("%d%d%d%d%d%d",&n,&m1,&m2,&d,&b[0].x,&b[0].y);
	memset(f,0,sizeof(f));
	b[0].t=0;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&b[i].x,&b[i].y,&b[i].t);
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			if(sqr(b[i].x-b[j].x)+sqr(b[i].y-b[j].y)-sqr(b[i].t-b[j].t)<=EPS){
				apmax(f[i],f[j]+1);
			}
		}
		if(f[i]*d>=m2){
			printf("Y %.2f",process(b[i].t));
			return 0;
		}
		if((i-f[i])*d>=m1){
			printf("N %.2f",process(b[i].t));
			return 0;
		}
		apmax(ans,f[i]);
	}
	printf("%d",ans);
}
