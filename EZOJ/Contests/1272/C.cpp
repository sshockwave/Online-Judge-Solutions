#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=15,MOD=1000000007;
int n,k,l,d[N],ans=0,fac[N];
long long f[N];
long long fpow(int x,int n){
	if(n==0){
		return 1;
	}
	long long ret=fpow(x,n>>1);
	ret=ret*ret%MOD;
	if(n&1){
		ret=ret*x&MOD;
	}
	return ret;
}
void dfs(int i){
	if(d[i]>k||i==n){
		long long mul=1,sing=l-k;
		for(int j=2;j<=i&&mul&&sing;j++){
			for(int k=1;k<j&&mul;k++){
				mul=mul*max(0,l-(d[j]-d[k])+1)%MOD;
			}
			sing=sing*(l-(k-d[j]))%MOD;
		}
		ans=(ans+mul*fpow(sing,n-i)%MOD*(fac[n]/fac[n-i])%MOD)%MOD;
		if(i==n){
			return;
		}
	}
	i++;
	for(d[i]=max(d[i-1],k-l*(n-i));d[i]<=k+1&&d[i]-d[i-1]<=l;d[i]++){
		dfs(i);
	}
}
int main(){
	n=ni(),k=ni(),l=ni();
	if(n==1){
		putchar(k?'0':'1');
		return 0;
	}
	if(k<l){
		putchar('0');
		return 0;
	}
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=fac[i-1]*i;
	}
	d[1]=0;
	dfs(1);
	printf("%lld",ans);
}
