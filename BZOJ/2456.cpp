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
	int cur,cnt=0;
	for(int tot=next_int();tot--;){
		if(cnt==0){
			cur=next_int();
			cnt++;
		}else if(next_int()==cur){
			cnt++;
		}else{
			cnt--;
		}
	}
	printf("%d\n",cur);
}
