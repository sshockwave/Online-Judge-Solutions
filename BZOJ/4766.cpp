#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
inline int nl(){
	lint i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const double EPS=1e-2;
lint MOD;
inline lint round(double x){
	return x+EPS;
}
inline double fmod(double x){
	return x-(double)round(x/MOD)*MOD;
}
inline lint mul(lint a,lint b){
	return round(fmod((double)a*b));
}
inline lint fpow(lint x,lint n){
	lint ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
int main(){
	lint n=nl(),m=nl();
	MOD=nl();
	n%=MOD,m%=MOD;
	printf("%lld",mul(fpow(n,(m+MOD-1)%MOD),fpow(m,(n+MOD-1)%MOD)));
}
