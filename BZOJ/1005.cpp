#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 1010
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
long long c[N][N];//c[up][down]
struct bigint{
	int digit[4000],dtop;
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
	void print(){
		for(int i=dtop-1;i>=0;i--){
			putchar(digit[i]+'0');
		}
	}
}ans;
int main(){
	int n=ni(),cnt=0,rest;
	ans.dtop=ans.digit[0]=1;
	rest=n-2;
	memset(c,0,sizeof(c));
	for(int i=0;i<=n;i++){
		c[0][i]=1;
		for(int j=1;j<=i;j++){
			c[j][i]=c[j][i-1]+c[j-1][i-1];
		}
	}
	for(int i=0,d;i<n;i++){
		scanf("%d",&d);
		if(d==-1){
			cnt++;
		}else if(d>0){
			if(rest<d-1){
				printf("0");
				return 0;
			}
			ans*=c[d-1][rest];
			rest-=d-1;
		}else{
			printf("0");
			return 0;
		}
	}
	while(rest--){
		ans*=cnt;
	}
	ans.print();
}
