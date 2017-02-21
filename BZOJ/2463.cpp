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
	for(int n;n=next_int();){
		puts(n&1?"Bob":"Alice");
	}
}
