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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=200010,O=1000000007;
int x[N],v[N],lst[N],*vlst[N];
int f[N],stk[N],ss=0;
inline bool lcmp(int a,int b){
	return x[a]<x[b];
}
inline bool vcmp(int *a,int *b){
	return *a<*b;
}
struct intv{
	int l,r;
	inline friend bool operator < (const intv &a,const intv &b){
		return a.r!=b.r?a.r<b.r:a.l<b.l;
	}
}ints[N];
namespace B{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;(c[x]+=v)%=O,x+=x&-x);
	}
	inline int sum(int x){
		int ans=0;
		for(;x;(ans+=c[x])%=O,x^=x&-x);
		return ans;
	}
	inline int ask(int l,int r){
		return (sum(r)-sum(l-1)+O)%O;
	}
}
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		x[i]=ni,v[i]=ni,lst[i]=i,vlst[i]=v+i;
	}
	sort(lst+1,lst+n+1,lcmp);
	sort(vlst+1,vlst+n+1,vcmp);
	for(int i=1;i<=n;i++){
		*vlst[i]=i;
	}
	int val=v[lst[1]];
	for(int i=1;i<=n;i++){
		apmax(val,v[lst[i]]);
		ints[i].r=val;
	}
	val=v[lst[n]];
	for(int i=n;i>=1;i--){
		apmin(val,v[lst[i]]);
		ints[i].l=val;
	}
	sort(ints+1,ints+n+1);
	B::init(n+1);
	B::add(1,1);
	for(int i=1;i<=n;i++){
		B::add(ints[i].r+1,B::ask(ints[i].l,ints[i].r+1));
	}
	printf("%d\n",B::ask(n+1,n+1));
	return 0;
}
