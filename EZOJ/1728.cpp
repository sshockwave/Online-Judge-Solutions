#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <complex>
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
const int N=131072,SHIFT=17;
int rev[N];
typedef complex<double> comp;
comp a[N];
inline void bit_rev(){
	rev[0]=0;
	for(int i=1;i<N;i++){
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(SHIFT-1));
	}
}
inline void bit_rev(comp *a){
	for(int i=0;i<N;i++){
		if(i<rev[i]){
			swap(a[i],a[rev[i]]);
		}
	}
}
inline comp omega(int i,int n){
	double angle=M_PI*2/n*i;
	return comp(cos(angle),sin(angle));
}
inline void fft(comp *a,int d){
	bit_rev(a);
	for(int i=1;i<SHIFT;i++){
		int jmp=1<<i,half=jmp>>1;
		for(int j=0;j<half;j++){
			comp w=omega(d*j,jmp),p,q;
			for(int k=j;k<N;k+=jmp){
				p=a[k],q=a[k+half]*w;
				a[k]=p+q,a[k+half]=p-q;
			}
		}
	}
	if(d==-1){
		for(int i=0;i<N;i++){
			a[i]/=n;
		}
	}
}
int main(){
	bit_rev();
	for(int i=0;i<N;i++){
		a[i]=0;
	}
	for(int tot=ni();tot--;){
		a[ni()]+=1;
	}
	fft(a,1);
	for(int i=0;i<N;i++){
		a[i]*=a[i];
	}
	fft(a,-1);
	for(int i=0,j;i<N;i++){
		j=round(a[i].real);
		if(j){
			printf("%d %d\n",i,j);
		}
	}
}
