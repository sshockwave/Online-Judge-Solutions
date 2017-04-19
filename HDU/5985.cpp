#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmax(double &a,const double &b){
	if(a<b){
		a=b;
	}
}
const int N=12,T=1000;
const double EPS=1e-8;
inline double fpow(double x,int n){
	double ret=1;
	for(;n;n>>=1,x*=x){
		if(n&1){
			ret*=x;
		}
	}
	return ret;
}
int num[N];
double p[N],pw[N][T],ans[N],dispp[N][T];
int main(){
	for(int tot=ni();tot--;){
		int n=ni();
		double tmp;
		for(int i=1;i<=n;i++){
			scanf("%d%lf",num+i,p+i);
			pw[i][0]=1;
			ans[i]=dispp[i][0]=0;
		}
		if(n==1){
			puts("1.00000000");
			continue;
		}
		double mul1,mul2,delta;
		for(int t=1;t<T;t++){
			for(int i=1;i<=n;i++){
				pw[i][t]=pw[i][t-1]*p[i];
				dispp[i][t]=fpow(1-pw[i][t],num[i]);
			}
			for(int i=1;i<=n;i++){
				mul1=mul2=1;
				for(int j=1;j<=n;j++){
					if(j!=i){
						mul1*=dispp[j][t];
						mul2*=dispp[j][t-1];
					}
				}
				delta=(1-dispp[i][t])*(mul1-mul2);
				ans[i]+=delta;
			}
		}
		for(int i=1;i<=n;i++){
			printf("%.8lf ",ans[i]);
		}
		putchar('\n');
	}
}
