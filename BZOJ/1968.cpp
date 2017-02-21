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

int main(){
	int n=next_int(),ans=0;
	for(int i=1;i<=n;i++){
		ans+=n/i;
	}
	printf("%d\n",ans);
}
