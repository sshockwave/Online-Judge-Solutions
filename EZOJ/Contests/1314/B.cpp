#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
#define cout cerr
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int SHIFT=10,N=1<<SHIFT,MOD=998244353;
inline int mod(const int &x){
	return x>=MOD?x-MOD:x;
}
inline lint mod(const lint &x){
	return x>=MOD?x%MOD:x;
}
inline int add(const int &a,const int &b){
	return mod(a+b);
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return mod((lint)a*b);
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
inline int shifter(int n){
	int i=0;
	for(;(1<<i)<n;i++);
	return i;
}
int rev[N],omega[SHIFT+1][N>>1],revomega[SHIFT+1][N>>1];
inline void ntt(int a[],int sh,bool inv){
	int n=1<<sh;
	for(int i=0;i<n;i++){
		if(rev[i]<i){
			swap(a[i],a[rev[i]]);
		}
	}
	for(int i=1;i<=sh;i++){
		int full=1<<i,half=full>>1;
		for(int j=0;j<half;j++){
			int w=inv?revomega[i][j]:omega[i][j];
			for(int k=j;k<n;k+=full){
				int p=a[k],q=mul(a[k+half],w);
				a[k]=add(p,q),a[k+half]=sub(p,q);
			}
		}
	}
	if(inv){
		int revn=fpow(n,MOD-2);
		for(int i=0;i<n;i++){
			apmul(a[i],revn);
		}
	}
}
int f[N][N],g[N][N],x[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni,sh=shifter(n+1),sn=1<<sh;
	rev[0]=0;
	for(int i=0;i<sn;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=sn>>1;
		}
	}
	for(int i=1;i<=sh;i++){
		int full=1<<i,half=full>>1;
		int wn=fpow(3,(MOD-1)/full),iwn=fpow(wn,MOD-2);
		for(int j=0,w=1,iw=1;j<half;j++,apmul(w,wn),apmul(iw,iwn)){
			omega[i][j]=w;
			revomega[i][j]=iw;
		}
	}
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(x,0,sizeof(x));
	x[1]=1,ntt(x,sh,0);
	for(int i=0;i<sn;i++){
		f[0][i]=f[1][i]=1;
	}
	for(int i=2;i<=n;i++){
		for(int j=0;j<sn;j++){
			ull F=0,G=0;
			for(int k=1;k<i;k++){
				F+=(ull)f[i-k][j]*g[k][j]%MOD;
				G+=((ull)g[i-k][j]*(f[k][j]+g[k][j])+(ull)f[i-k][j]*f[k][j]%MOD*x[j])%MOD;
			}
			f[i][j]=F%MOD,g[i][j]=G%MOD;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<sn;j++){
			apadd(f[i][j],g[i][j]);
		}
		ntt(f[i],sh,1);
		for(int j=0;j<=n;j++){
			printf("%d ",f[i][i-j]);
		}
		putchar('\n');
	}
}
