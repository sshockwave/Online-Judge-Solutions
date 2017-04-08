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
const int MOD=258280327;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int mul(int a,int b){
	return (long long)a*b%MOD;
}
inline bool check(int x,int n){
	int nx=x;
	for(int i=1;i<n;i++){
		nx=(nx*10)%MOD;
		if(nx<=x){
			return false;
		}
	}
	return true;
}
inline int cal(int n){
	int fac=1,cnt=0;
	for(int i=1;i<=n;i++){
		fac*=10;
	}
	for(int i=0;i<fac;i++){
		if(check(i,n)){
			cnt++;
		}
	}
	return cnt;
}
int main(){
	int n=ni(),ans=0;
	for(int i=1;i<=n;i++){
		ans=add(ans,mul(i*i,cal(n)));
	}
	printf("%d\n",ans);
}
