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
int main(){
	int n,m1,m2,d,ans=0;
	scanf("%d%d%d%d%lf%lf",&n,&m1,&m2,&d,&b[0].x,&b[0].y);
	memset(f,-1,sizeof(f));
	f[0]=0;
	b[0].t=0;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&b[i].x,&b[i].y,&b[i].t);
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			if(f[j]!=-1&&sqr(b[i].x-b[j].x)+sqr(b[i].y-b[j].y)-sqr(b[i].t-b[j].t)<=EPS){
				apmax(f[i],f[j]+1);
			}
		}
		apmax(ans,f[i]);
		if(f[i]*d>=m2){
			printf("Y %.2f",b[i].t);
			return 0;
		}
		if((i-ans)*d>=m1){
			printf("N %.2f",b[i].t);
			return 0;
		}
	}
	printf("%d",ans);
}
