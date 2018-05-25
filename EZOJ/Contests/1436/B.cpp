#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,logN=20;
int hb[N];
inline void g_hb(int n){
	hb[0]=-1;
	for(int i=1;i<=n;i++){
		hb[i]=hb[i>>1]+1;
	}
}
namespace rmq{
	template<int (*f)[logN],int (*join)(int,int)>inline void build(int n){
		for(int i=n;i>=1;i--){
			for(int j=0;i+(1<<(j+1))-1<=n;j++){
				f[i][j+1]=join(f[i][j],f[i+(1<<j)][j]);
			}
		}
	}
	template<int (*f)[logN],int (*join)(int,int)>inline int ask(int l,int r){
		const int j=hb[r-l+1];
		return join(f[l][j],f[r-(1<<j)+1][j]);
	}
}
int tol[N][logN],tor[N][logN];
int rad[N];
int lendx[N],rendx[N];
inline int min_lend(int a,int b){
	return lendx[a]<lendx[b]?a:b;
}
inline int max_rend(int a,int b){
	return rendx[a]>rendx[b]?a:b;
}
struct Cover{
	int lendx,rendx;
	int lp,rp;
	inline friend Cover operator + (const Cover &a,const Cover &b){
		return (Cover){
			min(a.lendx,b.lendx),max(a.rendx,b.rendx),min_lend(a.lp,b.lp),max_rend(a.rp,b.rp)
		};
	}
}cov[N][logN];
inline Cover step_k(int x,int k){
	Cover ans=(Cover){x,x,x,x};
	for(int j;j=hb[k],k;k^=1<<j){
		ans=cov[ans.lp][j]+cov[ans.rp][j];
	}
	return ans;
}
int ext_l[N],ext_r[N];
int _mn[N],mx_[N];
inline bool check_all(int n,int k){
	assert(k);
	for(int i=1;i<=n;i++){
		const Cover tmp=step_k(i,k-1);
		ext_l[i]=tmp.lendx;
		ext_r[i]=tmp.rendx;
	}
	_mn[0]=n+1;
	for(int i=1;i<=n;i++){
		_mn[i]=min(_mn[i-1],ext_r[i]);
	}
	mx_[n+1]=0;
	for(int i=n;i>=1;i--){
		mx_[i]=max(mx_[i+1],ext_l[i]);
	}
	for(int i=1;i<=n;i++){
		if(_mn[ext_l[i]-1]<i||i<mx_[ext_r[i]+1])return true;
	}
	return false;
}
/*inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}*/
int main(){
#ifndef ONLINE_JUDGE
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
#endif
	int n=ni;
	g_hb(n);
	for(int i=1;i<=n;i++){
		rad[i]=ni;
		lendx[i]=max(i-rad[i],1);
		rendx[i]=min(i+rad[i],n);
		tol[i][0]=tor[i][0]=i;
	}
	rmq::build<tol,min_lend>(n);
	rmq::build<tor,max_rend>(n);
	for(int i=1;i<=n;i++){
		cov[i][0]=(Cover){lendx[i],rendx[i],
			rmq::ask<tol,min_lend>(lendx[i],rendx[i]),
			rmq::ask<tor,max_rend>(lendx[i],rendx[i])
		};
	}
	for(int j=0;j<hb[n-1];j++){
		for(int i=1;i<=n;i++){
			cov[i][j+1]=cov[cov[i][j].lp][j]+cov[cov[i][j].rp][j];
		}
	}
	int l=0,r=n-1;
	while(l<r){
		int m=((l+r)>>1)+1;
		if(check_all(n,m)){
			l=m;
		}else{
			r=m-1;
		}
	}
	printf("%d\n",l);
	return 0;
}
