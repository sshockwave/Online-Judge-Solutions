#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <complex>
#include <cassert>
#define L 50010
#define D 150000
using namespace std;
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const double PI=acos(-1);
complex<double> a[D],b[D];
char s1[L],s2[L];
int digit[D],rev[D];
inline complex<double> unit(int n){
	double angle=PI*2/n;
	return complex<double>(cos(angle),sin(angle));
}
inline void bitrev(int n){
	rev[0]=0;
	for(int i=1;i<n;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=n>>1;
		}
	}
}
inline void bitrev(int n,complex<double> *num){
	for(int i=0;i<n;i++){
		if(i<rev[i]){
			swap(num[i],num[rev[i]]);
		}
	}
}
inline void fft(int n,complex<double> *num,int d){
	bitrev(n,num);
	for(int i=2,half;i<=n;i<<=1){
		half=i>>1;
		complex<double>wn=unit(i*d),w=1,p,q;
		for(int j=0;j<half;j++){
			for(int k=j;k<n;k+=i){
				p=num[k],q=w*num[k+half];
				num[k]=p+q;
				num[k+half]=p-q;
			}
			w*=wn;
		}
	}
	if(d==-1){
		for(int i=0;i<n;i++){
			num[i]/=n;
		}
	}
}
inline int process(char *s,complex<double> *num){
	int n=0;
	for(;s[n];n++){
		num[n]=s[n]-'0';
	}
	for(int i=0,j=n-1;i<j;i++,j--){
		swap(num[i],num[j]);
	}
	return n;
}
int main(){
	while(scanf("%s%s",s1,s2)){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		int n=process(s1,a)+process(s2,b),shift=0,r=0;
		for(;(1<<shift)<n;shift++);
		n=(1<<shift);
		bitrev(n);
		fft(n,a,1);
		fft(n,b,1);
		for(int i=0;i<n;i++){
			a[i]*=b[i];
		}
		fft(n,a,-1);
		for(int i=0;i<n;i++){
			digit[i]=round(a[i].real())+r;
			r=digit[i]/10;
			digit[i]%=10;
		}
		while(r){
			digit[n++]=r%10;
			r/=10;
		}
		while(n&&digit[n-1]==0){
			n--;
		}
		if(n==0){
			n++;
		}
		for(int i=n-1;i>=0;i--){
			putchar(digit[i]+'0');
		}
		putchar('\n');
	}
}
