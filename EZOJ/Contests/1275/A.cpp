#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long double ld;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline ld sqr(ld x){
	return x*x;
}
const int N=1010;
ld x[N],g[N],h[N];
int main(){
	ld w=ni(),k=(ld)ni()/w;
	int n=ni()+1;
	g[1]=0;
	h[1]=sqr((1+k)/2);
	for(int i=2;i<=n;i++){
		g[i]=(1-sqr(k))/(sqr(k-1)+h[i-1]*4-2*sqr(k));
		h[i]=((sqr(k-1)+4*h[i-1]-2*sqr(k))*sqr(k+1)-sqr(sqr(k)-1))/(4*sqr(k-1)+16*h[i-1]-8*sqr(k));
	}
	x[n]=w;
	for(int i=n;i>0;i--){
		x[i-1]=x[i]*g[i];
	}
	printf("%.8lf\n",(double)(sqr(w)*h[n]));
	for(int i=1,top=min(n,11);i<top;i++){
		printf("%.8lf\n",(double)x[i]);
	}
}
