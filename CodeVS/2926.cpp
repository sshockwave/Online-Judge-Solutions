#include <iostream>
#include <cstdio>
#include <cstring>
#define N 22
#define S 210
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
struct BigInt{
	int digit[S],dtop;
	void maintain(){
		for(int i=0;i<dtop;i++){
			digit[i+1]+=digit[i]/10;
			digit[i]%=10;
		}
		for(;digit[dtop];dtop++){
			digit[dtop+1]+=digit[dtop]/10;
			digit[dtop]%=10;
		}
	}
	BigInt(){
		memset(digit,0,sizeof(digit));
	}
	void print(){
		for(int i=dtop-1;i>=0;i--){
			putchar(digit[i]+'0');
		}
	}
	void operator += (BigInt &b){
		apmax(dtop,b.dtop);
		for(int i=0;i<dtop;i++){
			digit[i]+=b.digit[i];
		}
		maintain();
	}
	void operator *= (int b){
		for(int i=0;i<dtop;i++){
			digit[i]*=b;
		}
		maintain();
	}
	void operator /= (int n){
		int r=0;
		for(int i=dtop-1;i>=0;i--){
			digit[i]+=r*10;
			r=digit[i]%n;
			digit[i]/=n;
		}
		while(digit[dtop-1]==0){
			dtop--;
		}
	}
}ans,fac[N*N],pow;
int f[N],g[N],h[N];
int main(){
	f[1]=1,f[2]=1,f[3]=2;
	for(int i=4;i<N;i++){
		f[i]=f[i-3]+i-1;
	}
	g[0]=0;
	for(int i=1;i<N;i++){
		g[i]=g[i-1]+(i>>1)+(i&1);
	}
	pow.digit[0]=1;
	pow.maintain();
	for(int i=0;i<N*N;i++){
		fac[i]=pow;
		pow*=2;
	}
	int n=next_int();
	ans+=fac[n*(n+1)/2];
	ans+=fac[f[n]+1];
	ans+=fac[g[n]+1];
	ans+=fac[g[n]];
	ans/=6;
	ans.print();
}
