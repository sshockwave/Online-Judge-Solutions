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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1000010,T=2;
int a[N];
int ext[N],ext_inc[N],ext_dec[N];
struct Intv{
	int l,r;
}intv[N*2];
int vlst[N*2][T+1],vcnt[N*2];
int f(int,int);
inline bool calc(int m,int d){
	const int l=intv[m].l,r=intv[m].r;
	return !f(l-d+1,r+d)||!f(l-d,r+d-1);
}
int f(const int l,const int r){
	const int m=l+r;
	int t=max(0,min(r-intv[m].r,T));
	for(int &d=vcnt[m];d<t;d++,vlst[m][d]=calc(m,d));
	return vlst[m][t];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gameb.in","r",stdin);
	freopen("gameb.out","w",stdout);
#endif
	const int n=ni,tp=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	ext[n]=ext_inc[n]=ext_dec[n]=n;
	for(int i=n-1;i>=1;i--){
		ext_inc[i]=a[i]<=a[i+1]?ext_inc[i+1]:i;
		ext_dec[i]=a[i]>=a[i+1]?ext_dec[i+1]:i;
		ext[i]=ext_inc[i];
		if(tp==2){
			apmax(ext[i],ext_dec[i]);
		}
	}
	for(int l=1,r=1;l+r<=n*2;r<ext[l]?++r:++l){
		intv[l+r]=(Intv){l,r};
		vlst[l+r][vcnt[l+r]=0]=0;
	}
	for(int i=1;i<=n*2;i++){
		for(int j=1;j<=T;j++){
			if(intv[i].l-j<1||intv[i].r+j>n)break;
			f(intv[i].l-j,intv[i].r+j);
		}
	}
	for(int tot=ni;tot--;){
		const int l=ni,r=ni;
		puts(f(l,r)?"se":"liulei");
	}
	return 0;
}
