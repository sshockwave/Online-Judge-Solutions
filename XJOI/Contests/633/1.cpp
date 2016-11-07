#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define MOD 1000000007
#define N 100010
using namespace std;
char s[N],t[N];
int n,k,pwr[N],fac[N],rfac[N],ans=1;
inline void append(long long v){
	ans=(v+ans)%MOD;
}
inline int c(int up,int dwn){
	if(up>dwn){
		return 0;
	}
	return 1ll*fac[dwn]*rfac[up]%MOD*rfac[dwn-up]%MOD;
}
int main(){
	scanf("%d%d%s%s",&n,&k,s,t);
	fac[0]=pwr[0]=rfac[0]=rfac[1]=1;
	for(int i=1;i<=n;i++){
		fac[i]=1ll*fac[i-1]*i%MOD;
	}
	for(int i=2;i<=n;i++){
		rfac[i]=1ll*(MOD-MOD/i)*rfac[MOD%i]%MOD;
	}
	for(int i=2;i<=n;i++){
		rfac[i]=1ll*rfac[i-1]*rfac[i]%MOD;
	}
	for(int i=1;i<=n;i++){
		pwr[i]=1ll*pwr[i-1]*25%MOD;
	}
	for(int i=0;i<n;i++){
		if(s[i]<t[i]){
			//cur==s[i]
			append(1ll*c(k,n-i-1)*pwr[k]);
			//cur!=s[i]
			if(t[i]>'b'){
				append(1ll*c(k-1,n-i-1)*pwr[k-1]%MOD*(t[i]-'a'-1));
			}
		}else{
			append(1ll*c(k-1,n-i-1)*pwr[k-1]%MOD*(t[i]-'a'));
		}
		if(s[i]!=t[i]){
			k--;
		}
	}
	printf("%d",ans);
}
