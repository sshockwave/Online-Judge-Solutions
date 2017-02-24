#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
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
int num[N],lexp[N*2],rexp[N*2];
int main(){
	int n=next_int(),b=next_int(),posb;
	long long cnt=0;
	for(int i=1;i<=n;i++){
		num[i]=next_int();
		if(num[i]==b){
			posb=i;
		}
	}
	memset(lexp,0,sizeof(lexp));
	memset(rexp,0,sizeof(rexp));
	for(int i=posb,sum=0;i>0;i--){
		if(num[i]<b){
			sum--;
		}else if(num[i]>b){
			sum++;
		}
		lexp[sum+N]++;
	}
	for(int i=posb,sum=0;i<=n;i++){
		if(num[i]<b){
			sum--;
		}else if(num[i]>b){
			sum++;
		}
		rexp[sum+N]++;
	}
	for(int i=-n;i<=n;i++){
		cnt+=lexp[N+i]*rexp[N-i];
	}
	printf("%d",cnt);
}
