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
int main(){
	freopen("rsmt1.in","r",stdin);
	freopen("rsmt1.out","w",stdout);
	int n=ni();
	puts("0\n");
	for(int i=1;i<n;i++){
		printf("%d %d\n",i,i+1);
	}
}
