#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
inline lint nl(){
	lint i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const long double EPS=1e-2;
lint MOD;
inline lint fmul(lint x,lint n){
	lint ret=0;
	for(;n;n>>=1,x=(x<<1)%MOD){
		if(n&1){
			ret=(ret+x)%MOD;
		}
	}
	return ret;
}
inline lint fpow(lint x,lint n){
	lint ret=1;
	for(;n;n>>=1,x=fmul(x,x)){
		if(n&1){
			ret=fmul(ret,x);
		}
	}
	return ret;
}
int main(){
	lint n=nl(),m=nl();
	MOD=nl();
	n%=MOD,m%=MOD;
	printf("%lld",fmul(fpow(n,(m+MOD-1)%MOD),fpow(m,(n+MOD-1)%MOD)));
}
