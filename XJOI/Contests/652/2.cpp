#include <cstdio>
#include <cstring>
#include <cmath>
#define N 100010
#define EPS 0.001
#define INF 1000
using namespace std;
double x[N];
int y[N],z[N],n;
double fpow(double x,int y){
	if(y==0){
		return 1;
	}
	double tmp=fpow(x,y>>1);
	return tmp*tmp*(y&1?x:1);
}
inline double cal(double pos){
	double ans=0;
	for(int i=1;i<=n;i++){
		if(x[i]>pos){
			if(y[i]){
				ans+=y[i]*fpow(x[i]-pos,y[i]-1);
			}
		}else if(pos>x[i]){
			if(z[i]){
				ans-=z[i]*fpow(pos-x[i],z[i]-1);
			}
		}
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%d%d",x+i,y+i,z+i);
	}
	double l=-INF,r=INF,mid;
	while(r-l>EPS){
		mid=(l+r)/2;
		if(cal(mid)>0){
			l=mid;
		}else{
			r=mid;
		}
	}
	printf("%.2f",(double)round(l*100)/100);
}
