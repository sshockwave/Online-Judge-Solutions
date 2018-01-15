#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int SH=18,N=1<<SH,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace poly{
	int sh,n,invn;
	int o[SH][N>>1],io[SH][N>>1];
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			lint wn=fpow(3,(O-1)/full),iwn=inv(wn);
			for(int j=0,w=1,iw=1;j<half;j++,w=w*wn%O,iw=iw*iwn%O){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	int rev[N]={0};
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
			if(i<rev[i]){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				lint w=(d==1?o:io)[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=w*a[k+half]%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
int mlen;
int a[4][N];
void fpow(int n){
	if(n==0){
		memset(a,0,sizeof(a));
		a[0][0]=a[3][0]=1;
		return;
	}
	fpow(n>>1);
	for(int i=0;i<4;i++){
		poly::ntt(a[i]);
	}
	lint b[2][2];
	for(int i=0;i<poly::n;i++){
		for(int j=0;j<4;j++){
			b[j>>1][j&1]=a[j][i],a[j][i]=0;
		}
		a[0][i]=(b[0][0]*b[0][0]+b[0][1]*b[1][0])%O;
		a[1][i]=(b[0][0]*b[0][1]+b[0][1]*b[1][1])%O;
		a[2][i]=(b[1][0]*b[0][0]+b[1][1]*b[1][0])%O;
		a[3][i]=(b[1][0]*b[0][1]+b[1][1]*b[1][1])%O;
	}
	for(int i=0;i<4;i++){
		poly::ntt(a[i],-1);
		poly::clr(a[i],mlen+1);
	}
	if(n&1){
		for(int i=mlen;i>=0;i--){
			a[1][i]=(a[0][i]<<1)%O;
			a[3][i]=(a[2][i]<<1)%O;
			if(i){
				a[0][i]=(a[0][i]+a[1][i-1])%O;
				a[1][i]=(a[1][i]+a[1][i-1])%O;
				a[2][i]=(a[2][i]+a[3][i-1])%O;
				a[3][i]=(a[3][i]+a[3][i-1])%O;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
#endif
	int n=ni;
	mlen=ni;
	poly::init((mlen<<1)+1);
	fpow(n);
	for(int i=1;i<=mlen;i++){
		printf("%d ",(a[0][i]+a[2][i])%O);
	}
	putchar('\n');
	return 0;
}
