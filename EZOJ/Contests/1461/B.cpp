#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
namespace IO{
	const int N=10000000;
	char s[N],*t=s,*tt=s+N;
	inline char getchar(){
		if(t==tt){
			fread(s,1,N,stdin);
			t=s;
		}
		return t++[0];
	}
}
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=IO::getchar()));
	while(i=i*10-'0'+c,isdigit(c=IO::getchar()));
	return i;
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
inline int f(const int l,const int r){
	const int m=l+r;
	int t=max(0,min(r-intv[m].r,T));
	assert(t<=vcnt[m]);
	return vlst[m][t];
}
Intv intlst[N*2*2],intst[N*2*2];
int bcnt[N];
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
	int ls=0;
	memset(bcnt,0,sizeof(bcnt));
	for(int l=1,r=1;l+r<=n*2;r<ext[l]?++r:++l){
		intv[l+r]=(Intv){l,r};
		vlst[l+r][vcnt[l+r]=0]=0;
		for(int j=1;j<=T&&l-j>=1&&r+j<=n;j++){
			intlst[++ls]=(Intv){l-j,r+j};
			++bcnt[r-l+j+j];
		}
	}
	for(int i=1;i<=n;i++){
		bcnt[i]+=bcnt[i-1];
	}
	for(int i=1;i<=ls;i++){
		intst[bcnt[intlst[i].r-intlst[i].l]--]=intlst[i];
	}
	for(int i=1;i<=ls;i++){
		const int l=intst[i].l,r=intst[i].r;
		const int m=l+r;
		vlst[m][vcnt[m]+1]=!f(l+1,r)||!f(l,r-1);
		++vcnt[m];
	}
	for(int i=1,tot=ni;i<=tot;i++){
		const int l=ni,r=ni;
		puts(f(l,r)?"se":"liulei");
	}
	return 0;
}
