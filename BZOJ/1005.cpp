#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 1010
#define INF 0x7f7f7f7f
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
int exp[N],prime[N],ptop=0;
bool np[N];
inline void times(int n,int d){
	for(int i=0;prime[i]<=n;i++){
		for(int j=prime[i];j<=n;j*=prime[i]){
			exp[i]+=d*(n/j);
		}
	}
}
int main(){
	int n=ni(),cnt=0,rest;
	rest=n-2;
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ptop++]=i;
		}
		for(int j=0;j<ptop&&i*prime[j]<=n;j++){
			np[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
		}
	}
	prime[ptop]=INF;
	memset(exp,0,sizeof(exp));
	for(int i=0,d;i<n;i++){
		scanf("%d",&d);
		if(d==-1){
			cnt++;
		}else if(d>0){
			if(rest<d-1){
				printf("0");
				return 0;
			}
			times(rest,1),times(d-1,-1),times(rest-d+1,-1);
			rest-=d-1;
		}else{
			printf("0");
			return 0;
		}
	}
	ans.dtop=ans.digit[0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<exp[i];j++){
			ans*=prime[i];
		}
	}
	while(rest--){
		ans*=cnt;
	}
	ans.print();
}
