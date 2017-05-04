#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,INF=0x7f7f7f7f,SPLIT=50;
int a[N],pre[N];
int stk[N],stop=0;
int pos[N];
int ints[N];
lint h[N];
namespace FFT{
	const int SHIFT=19,N=1<<SHIFT;
	const double EPS=1e-5;
	typedef complex<double> comp;
	comp a[N],b[N];
	int n,shift;
	int rev[N];
	inline comp omega(int exp,int n){
		double angle=M_PI*2*exp/n;
		return comp(cos(angle),sin(angle));
	}
	inline void dft(comp *a,int d){
		for(int i=0;i<n;i++){
			if(rev[i]<i){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=2,half;i<=n;i<<=1){
			half=i>>1;
			for(int j=0;j<half;j++){
				comp w=omega(j*d,i),p,q;
				for(int k=j;k<n;k+=i){
					p=a[k],q=a[k+half]*w;
					a[k]=p+q;
					a[k+half]=p-q;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]/=n;
			}
		}
	}
	inline void work(int sn){
		for(shift=0;(1<<shift)<(sn<<1);shift++);
		shift++;
		n=1<<shift;
		for(int i=0,j=(sn<<1)-1;i<sn;i++,j--){
			a[i]=b[j]=ints[i];
		}
		for(int i=0;i<sn;i++){
			b[i]=0;
		}
		for(int i=sn<<1;i<n;i++){
			b[i]=0;
		}
		for(int i=sn;i<n;i++){
			a[i]=0;
		}
		for(int i=0,s=1<<(shift-1);i<n;i++){
			rev[i]=rev[i>>1]>>1;
			if(i&1){
				rev[i]|=s;
			}
		}
		dft(a,1),dft(b,1);
		for(int i=0;i<n;i++){
			a[i]*=b[i];
		}
		dft(a,-1);
		for(int i=0;i<n;i++){
			int j=i%(sn<<1);
			if(j<sn){
				h[j+1]+=a[i].real()+EPS;
			}
		}
	}
}
inline void work(int r){
	int A=a[stk[stop]],n=0;
	for(;stop&&a[stk[stop]]==A;pos[n++]=stk[stop--]);
	reverse(pos,pos+n);
	ints[0]=pos[0]-pre[pos[0]];
	for(int i=1;i<n;i++){
		ints[i]=pos[i]-pos[i-1];
	}
	ints[n]=r-pos[n-1];
	if(n>SPLIT){
		FFT::work(n+1);
	}else for(int i=0;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			h[j-i]+=ints[i]*ints[j];
		}
	}
}
int main(){
	int n=ni;
	memset(h,0,sizeof(h));
	a[0]=a[n+1]=INF;
	stk[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		for(;stop&&a[stk[stop]]<a[i];work(i));
		pre[i]=stk[stop];
		stk[++stop]=i;
	}
	for(;stop;work(n+1));
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=i^h[i];
	}
	printf("%lld\n",ans);
}
