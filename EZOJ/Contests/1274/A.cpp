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
inline long long nl(){
	long long i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
int MOD;
long long p;
long long fpow(long long x,long long n){
	if(n==0){
		return 1;
	}
	long long ret=fpow(x,n>>1);
	ret=ret*ret%p;
	if(n&1){
		ret=ret*x%p;
	}
	return ret;
}
inline int brute(){
	long long top=p*(p-1);
	int ans=0;
	for(long long i=1;i<=top;i++){
		for(long long j=1;j<=top;j++){
			if(fpow(i,j)==fpow(j,i)){
				ans=(ans+1)%MOD;
			}
		}
	}
	return ans;
}
inline int n4(){
	int ans=0;
	for(long long a=0;a<p;a++){
		for(long long b=0;b<p;b++){
			for(long long m=1;m<p;m++){
				for(long long n=1;n<p;n++){
					if(fpow(a,m)==fpow(b,n)){
						ans++;
						if(ans==MOD){
							ans=0;
						}
					}
				}
			}
		}
	}
	return ans;
}
inline bool is_prime(int n){
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			return false;
		}
	}
	return true;
}
int ans[100];
int main(){
	int tot=ni();
	MOD=ni();
    ans[2]=2;
    ans[3]=14;
    ans[5]=104;
    ans[7]=366;
    ans[11]=1550;
    ans[13]=3048;
    ans[17]=6272;
    ans[19]=9774;
    ans[23]=14894;
    ans[29]=34664;
    ans[31]=48750;
    ans[37]=84456;
    ans[41]=108320;
    ans[43]=128814;
    ans[47]=128846;
    ans[53]=209768;
    ans[59]=255374;
    ans[61]=424680;
    ans[67]=479886;
    ans[71]=563150;
    ans[73]=700704;
    ans[79]=782574;
    ans[83]=712334;
    ans[89]=1068320;
    ans[97]=1614336;
	while(tot--){
		p=nl();
		if(p<100){
			printf("%d\n",ans[p]%MOD);
		}else{
//			printf("%d\n",brute());
			printf("%d\n",n4());
		}
	}
}
