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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010,O=1000000007;
namespace fw{
	int c[N],n;
	inline void init(int _n){
		mset(c+1,0,n=_n);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]=(c[x]+v)%O,x+=x&-x);
	}
	inline int sum(int x){
		lint a=0;
		for(;x;a+=c[x],x^=x&-x);
		return a%O;
	}
	inline int ask(int l,int r){
		return (sum(r)+O-sum(l-1))%O;
	}
}
namespace disc{
	int *num[N];
	inline bool ncmp(int *a,int *b){
		return *a<*b;
	}
	inline void main(int n){
		sort(num+1,num+n+1,ncmp);
		for(int i=1;i<=n;i++){
			*num[i]=i;
		}
	}
}
int tmpx[N],tmpv[N];
int v[N];
struct Intv{
	int l,r;
	inline friend bool operator < (const Intv &a,const Intv &b){
		return a.r!=b.r?a.r<b.r:a.l<b.l;
	}
}intv[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("infection.in","r",stdin);
	freopen("infection.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		tmpx[i]=ni,tmpv[i]=ni;
		disc::num[i]=tmpx+i;
	}
	disc::main(n);
	for(int i=1;i<=n;i++){
		v[tmpx[i]]=tmpv[i];
		disc::num[i]=v+i;
	}
	disc::main(n);
	int premx=v[1];
	for(int i=1;i<=n;i++){
		apmax(premx,v[i]);
		intv[i].r=premx;
	}
	int sufmn=v[n];
	for(int i=n;i>=1;i--){
		apmin(sufmn,v[i]);
		intv[i].l=sufmn;
	}
	sort(intv+1,intv+n+1);
	fw::init(n+1);
	fw::add(1,1);
	for(int i=1;i<=n;i++){
		fw::add(intv[i].r+1,fw::ask(intv[i].l,intv[i].r+1));
	}
	printf("%d\n",fw::ask(n+1,n+1));
	return 0;
}
