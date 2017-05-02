#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int SHIFT=17,N=1<<SHIFT;
struct comp{
	double r,i;
	comp(double _r=0,double _i=0):r(_r),i(_i){}
	inline friend comp operator + (const comp &a,const comp &b){
		return comp(a.r+b.r,a.i+b.i);
	}
	inline friend comp operator - (const comp &a,const comp &b){
		return comp(a.r-b.r,a.i-b.i);
	}
	inline friend comp operator * (const comp &a,const comp &b){
		return comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);
	}
};
inline ostream & operator << (ostream & out,const comp &a){
	out<<"("<<a.r<<","<<a.i<<")";
	return out;
}
int n,shift;
const double EPS=1e-4;
char a[N],b[N];
comp omega[N>>1][SHIFT+1];
int rev[N];
int ans[N];
inline void getrev(){
	rev[0]=0;
	for(int i=1,s=1<<(shift-1);i<n;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=s;
		}
	}
}
inline void fft(comp a[],int d){
	for(int i=0;i<n;i++){
		if(rev[i]<i){
			swap(a[rev[i]],a[i]);
		}
	}
	for(int i=1;i<=shift;i++){
		int full=1<<i,half=full>>1;
		for(int j=0;j<half;j++){
			comp w=omega[j][i],p,q;
			w.i*=d;
			for(int k=j;k<n;k+=full){
				p=a[k],q=a[k+half]*w;
				a[k]=p+q;
				a[k+half]=p-q;
			}
		}
	}
	if(d==-1){
		for(int i=0;i<n;i++){
			a[i].r/=n;
		}
	}
}
comp ca[N],cb[N];
int main(){
	memset(omega,0,sizeof(omega));
	for(int i=1;i<=SHIFT;i++){
		int full=1<<i,half=full>>1;
		for(int j=0;j<half;j++){
			double angle=2*M_PI*j/full;
			omega[j][i]=comp(cos(angle),sin(angle));
		}
	}
	for(int tot=ni;tot--;){
		scanf("%s%s",a,b);
		memset(ca,0,sizeof(ca));
		memset(cb,0,sizeof(cb));
		for(int i=0;a[i];i++){
			ca[i].r=a[i]-'0';
		}
		for(int i=0;b[i];i++){
			cb[i].r=b[i]-'0';
		}
		int n=strlen(a)+strlen(b);
		for(shift=0;(1<<shift)<n;shift++);
		n=1<<shift;
		getrev();
		fft(ca,1),fft(cb,1);
		for(int i=0;i<n;i++){
			ca[i]=ca[i]*cb[i];
		}
		fft(ca,-1);
		int r=0;
		for(int i=0;i<n;i++){
			ans[i]=ca[i].r+EPS;
			ans[i]+=r;
			r=ans[i]/10;
			ans[i]%=10;
		}
		for(r=n-1;r>=0&&ans[r]==0;r--);
		if(r<0){
			puts("0");
			continue;
		}
		for(;r>=0;r--){
			putchar('0'+ans[r]);
		}
		putchar('\n');
	}
}
