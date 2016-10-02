#include <iostream>
#include <cstdio>
#include <cstring>
#define K 1010
#define MOD 10007
using namespace std;
long long c[K];
int main(){
	int a,b,k,m,n,lower;
	long long ans;
	scanf("%d%d%d%d%d",&a,&b,&k,&n,&m);
	upper=m<n?m:n;
	//C(m,k)*a^n*b^m
	c[0]=1;
	for(int i=1;i<=lower;i++){
		c[i]=(c[i-1]*(k-i+1)/i)%MOD;
	}
	ans=c[lower];
	for(int i=1;i<=n;i++){
		ans=(ans*a)%MOD;
	}
	for(int i=1;i<=m;i++){
		ans=(ans*b)%MOD;
	}
	printf("%lld",ans);
}
