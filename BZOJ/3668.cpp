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
const int N=100010;
int f[2];
int main(){
	int n=ni(),mx=ni();
	f[0]=0;
	f[1]=0x7fffffff;
	char op[5];
	for(int i=1,t;i<=n;i++){
		scanf("%s%d",op,&t);
		switch(op[0]){
			case 'A':{
				f[0]&=t;
				f[1]&=t;
				break;
			}
			case 'O':{
				f[0]|=t;
				f[1]|=t;
				break;
			}
			case 'X':{
				f[0]^=t;
				f[1]^=t;
				break;
			}
		}
	}
	int ans=0;
	for(int i=0;i<32;i++){
		if(mx&(1<<i)){
			ans=max((f[0]&(1<<i))|((f[0]|f[1])&((1<<i)-1)),(f[1]&(1<<i))|ans);
		}else{
			ans=(f[0]&(1<<i))|ans;
		}
	}
	printf("%d",ans);
}
