#include <iostream>
#include <cstdio>
#include <cstring>
#define MOD 100003
using namespace std;
long long qpow(long long x,long long exp){
	if(exp==0){
		return 1;
	}
	long long ret=qpow(x,exp>>1);
	ret=(ret*ret)%MOD;
	if(exp&1){
		ret=(ret*x)%MOD;
	}
	return ret;
}
int main(){
	long long n,m;
	scanf("%lld%lld",&m,&n);
	m%=MOD,n%=MOD;
	printf("%lld",((qpow(m,n)-m*qpow(m-1,n-1))%MOD+MOD)%MOD);
}
