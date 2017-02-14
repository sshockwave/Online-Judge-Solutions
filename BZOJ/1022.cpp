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
inline bool is_n(int n){
	int ex=0;
	while(n--){
		if(next_int()==1){
			ex^=1;
		}else{
			ex^=2;
		}
	}
	return ex==0;
}
int main(){
	for(int tot=next_int();tot--;){
		printf(is_n(next_int())?"John\n":"Brother\n");
	}
}
