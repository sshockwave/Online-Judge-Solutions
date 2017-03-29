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
const int N=1<<17,SHIFT=17;
int rev[N],num[N];
typedef complex<double> comp;
comp a[N],b[N],c[N];
comp operator * (comp a,int b){
	return comp(a.real()*b,a.imag()*b);
}
comp operator / (comp a,int b){
	return comp(a.real()/b,a.imag()/b);
}
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
	for(int i=2;i<=N;i<<=1){
		int half=i>>1;
		for(int j=0;j<half;j++){
			comp w=omega(d*j,i),p,q;
			for(int k=j;k<N;k+=i){
				p=a[k],q=a[k+half]*w;
				a[k]=p+q,a[k+half]=p-q;
			}
		}
	}
	if(d==-1){
		for(int i=0;i<N;i++){
			a[i]/=N;
		}
	}
}
int main(){
	memset(num,0,sizeof(num));
	bit_rev();
	for(int tot=ni(),i;tot--;){
		i=ni();
		a[i]+=1,b[i<<1]+=1,c[i*3]+=1;
	}
	fft(a,1),fft(b,1),fft(c,1);
	for(int i=0;i<N;i++){
		a[i]=a[i]+(a[i]*a[i]-b[i])/2+(a[i]*a[i]*a[i]-a[i]*b[i]*3+c[i]*2)/6;
	}
	fft(a,-1);
	for(int i=0,cur;i<N;i++){
		cur=round(a[i].real());
		if(cur){
			printf("%d %d\n",i,cur);
		}
	}
}
