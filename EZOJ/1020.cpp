#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline lint nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=100000;
inline lint f(lint n){
	lint ans=0;
	for(lint l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=(n/l)*(r-l+1);
	}
	return ans;
}
int main(){
	lint n=nl(),ans=0;
	for(lint l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=f(n/l)*(r-l+1);
	}
	printf("%lld",ans);
}
