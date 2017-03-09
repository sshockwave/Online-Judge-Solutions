#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 110
#define D 100
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
inline int abs(int a){
	return a>0?a:-a;
}
struct bigint{
	int digit[D],dtop;
	void operator *= (int b){
		int r=0;
		for(int i=0;i<dtop;i++){
			digit[i]*=b;
			digit[i]+=r;
			r=digit[i]/10;
			digit[i]%=10;
		}
		while(r){
			digit[dtop++]=r%10;
			r/=10;
		}
	}
	void operator += (int r){
		for(int i=0;i<dtop&&r;i++){
			digit[i]+=r;
			r=digit[i]/10;
			digit[i]%=10;
		}
		while(r){
			digit[dtop++]=r%10;
			r/=10;
		}
	}
	void operator -= (int r){
		for(int i=0;i<dtop&&r;i++){
			digit[i]-=r;
			if(digit[i]<0){
				digit[i]+=10;
				r=1;
			}else{
				r=0;
			}
		}
	}
	void print(){
		for(int i=dtop-1;i>=0;i--){
			putchar(digit[i]+'0');
		}
	}
}ans;
int small[]={0,1,5,16,81};
int main(){
	int n=ni();
	if(n<5){
		printf("%d",small[n]);
		return 0;
	}
	ans.digit[0]=1;
	ans.dtop=1;
	for(int i=0;i<n;i++){
		ans*=3;
	}
	if(n&1){
		ans-=2;
	}else{
		ans+=2;
	}
	ans.print();
}
