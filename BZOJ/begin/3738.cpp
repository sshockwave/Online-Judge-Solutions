#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define MOD 1000000007
#define S 90010
#define D 10000010
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
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int f[S],fac[D],inv[D],invfac[D];
inline int c(int n,int m){//c(up,down)
	return (long long)fac[m]*invfac[n]%MOD*invfac[m-n]%MOD;
}
int main(){
	memset(f,0,sizeof(f));
	int n=ni(),m=ni(),k=ni(),w,sum=0;
	f[0]=1;
	for(int i=1;i<=m;i++){
		w=ni()+1;
		sum+=w;
		for(int j=sum;j>=w;j--){
			f[j]=(((long long)f[j]-f[j-w])%MOD+MOD)%MOD;
		}
	}
	fac[0]=fac[1]=inv[1]=invfac[0]=invfac[1]=1;
	for(int i=2,top=k+n-1;i<=top;i++){
		fac[i]=(long long)fac[i-1]*i%MOD;
		inv[i]=((-(long long)inv[MOD%i]*(MOD/i))%MOD+MOD)%MOD;
		invfac[i]=(long long)invfac[i-1]*inv[i]%MOD;
	}
	long long ans=0;
	apmin(sum,k);
	for(int i=0;i<=sum;i++){
		ans=(ans+(long long)f[i]*c(n-1,k+n-1-i)%MOD)%MOD;
	}
	printf("%d",ans);
}
