#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int main(){
	int n=next_int(),k=next_int();
	long long ans=1ll*n*k;
	apmin(n,k);
	for(int i=1,j;i<=n;i=j+1){
		j=min(n,k/(k/i));
		ans-=1ll*(j-i+1)*(i+j)/2*(k/i);
	}
	printf("%lld",ans);
}
