#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define S 100010
#define EPS 1e-5
using namespace std;
int h,n,astore[S];
inline int& a(int x,int y){
	return astore[x*h+y];
}
int main(){
	scanf("%d%d",&n,&h);
	double l=0,r=0,mid,sum,pre,avg;
	for(int i=0;i<n;i++){
		for(int j=0;j<h;j++){
			scanf("%d",&a(i,j));
			r=max(r,(double)a(i,j));
		}
	}
	while(r-l>EPS){
		mid=(l+r)/2;
		sum=0;
		for(int i=0;i<n;i++){
			pre=a(i,0);
			avg=pre-mid;
			for(int j=1;j<h;j++){
				pre+=a(i,j);
				avg=max(avg,pre-mid*(j+1));
			}
			sum+=avg;
		}
		if(sum>=0){
			l=mid;
		}else{
			r=mid;
		}
	}
	printf("%.4f",(double)round(l*1e4)/1e4);
}
