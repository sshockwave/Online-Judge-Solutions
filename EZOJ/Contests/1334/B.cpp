#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=30010;
const double EPS=1e-7;
typedef complex<double>comp;
namespace poly{
	const int SH=16,N=1<<SH;
	int n,sh;
	int rev[N];
	comp o[SH][N>>1],io[SH][N>>1];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
		rev[0]=0;
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			double ang=2*M_PI/full;
			comp w(1,0),iw(1,0),wn(cos(ang),sin(ang)),iwn(wn.real(),-wn.imag());
			for(int j=0;j<half;j++,w*=wn,iw*=iwn){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	void fft(comp a[],int d=1){
		for(int i=0;i<n;i++){
			if(rev[i]<i){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				comp w=d==1?o[i][j]:io[i][j];
				for(int k=j;k<n;k+=full){
					comp p=a[k],q=a[k+half]*w;
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
}
comp g[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
#endif
	int n=ni;
	poly::init((n<<1)|1);
	memset(g,0,sizeof(g));
	static const comp idx(1,0);
	g[0]=idx;
	bool flag=false;
	int i=1;
	double ans=0;
	for(;i<=n;i++){
		poly::fft(g);
		for(int j=0;j<poly::n;j++){
			g[j]*=g[j];
		}
		poly::fft(g,-1);
		for(int j=n+1;j<poly::n;j++){
			g[j]=comp(0,0);
		}
		for(int j=n;j>=1;j--){
			g[j]=comp(g[j-1].real()/j,0);
		}
		g[0]=idx;
		double cur=g[n].real()-ans;
		ans=g[n].real();
		printf("%.7lf\n",cur);
		if(flag){
			if(cur<EPS){
				break;
			}
		}else if(cur>EPS){
			flag=true;
		}
	}
	for(;++i<=n;puts("0.0000000"));
	return 0;
}
