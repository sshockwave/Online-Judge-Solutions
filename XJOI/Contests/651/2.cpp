#include <iostream>
#include <cstdio>
#include <cstring>
#define MOD 998244353
using namespace std;
long long f[10000];
int main(){
	int n,k,num;
	scanf("%d%d",&n,&k);
	memset(f,0,sizeof(f));
	f[0]=1;
	while(n--){
		scanf("%d",&num);
		for(int i=k;i>=0;i--){
			for(int j=1;j<=num&&j<=i;j++){
				f[i]=(f[i]+f[i-j])%MOD;
			}
		}
	}
	printf("%d",f[k]);
}
