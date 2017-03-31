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
const int N=2010,MOD=1000000007;
int w[N],f[N],_f[N];
int pow(int x,int n){
	if(n==0){
		return 1;
	}
	int ret=pow(x,n>>1);
	ret=(long long)ret*ret%MOD;
	if(n&1){
		ret=(long long)ret*x%MOD;
	}
	return ret;
}
int main(){
	int n=ni(),ans=0;
	if(n<3){
		putchar('0');
		return 0;
	}
	for(int i=1;i<=n;i++){
		w[i]=ni();
	}
	_f[0]=0;
	for(int i=1;i<=n;i++){
		_f[i]=(long long)i*i*i%MOD*pow(n,n-3)%MOD;
		f[i]=((_f[i]-_f[i-1])%MOD+MOD)%MOD;
		ans=(pow(w[i],f[i])+ans)%MOD;
	}
	printf("%d",pow(ans,n-2));
}
