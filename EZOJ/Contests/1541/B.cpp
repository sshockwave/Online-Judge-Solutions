#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
struct Pt{
	int x,y;
}pt[N];
inline bool cmp_x(const Pt &a,const Pt &b){
	return a.x<b.x;
}
inline bool cmp_y(const Pt &a,const Pt &b){
	return a.y<b.y;
}
Pt lst[N];
int k;
int stk1[N],stk2[N];
inline lint get_ans(int n){
	int ss1=0,ss2=0;
	for(int i=1;i<=k;i++){
	}
	lint ans=mx-mn;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	k=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	sort(pt+1,pt+n+1,cmp_x);
	lint ans=LINF;
	for(int i=1;i+k-1<=n;i++){
		int ls=0;
		int j=i;
		for(;j<=i+k-1;j++){
			lst[++ls]=pt[j];
		}
		sort(lst+1,lst+ls+1,cmp_y);
		for(;j<=n;j++){
		}
	}
	printf("%lld\n",ans);
	return 0;
}
