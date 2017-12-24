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
const int N=(1<<16)+10,O=1000000007;
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
int fac[N],invfac[N];
inline int C(int n,int k){
	if(n<0||k<0||n<k)return 0;
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
struct BIT{
	int c[N+1],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int a=0;
		for(;x;a+=c[x],x^=x&-x);
		return a;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}b1,b2;
void putcont(int a1,int a2,int v){
	if(a1>a2)return putcont(a2,a1,v);
	b1.add(a1,v),b2.add(a2,v);
}
int n;
inline int query(int val,int val2,int to){
	const static int inv2=inv(2);
	lint ans=0;
	//val is in the front
	int a=b2.ask(1,val-1);
	int c=b1.ask(val+1,n);
	int b=(n>>1)-a-c-1;
	ans+=(lint)C(b,to-(a<<1))*fpow(inv2,b+1)%O;
	//val is in the back
	apmax(val,val2);
	a=b2.ask(1,val-1);
	c=b1.ask(val+1,n);
	b=(n>>1)-a-c-1;
	ans+=(lint)C(b,to-(a<<1)-1)*fpow(inv2,b+1)%O;
	return ans%O;
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
#endif
	n=ni;
	gmath(n);
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	b1.init(n),b2.init(n);
	for(int i=0;i<n;i+=2){
		putcont(a[i],a[i^1],1);
	}
	for(int tot=ni;tot--;){
		if(ni==1){
			int u=ni-1,v=ni-1;
			if(u==v)continue;
			if((u^v)==1){
				swap(a[u],a[v]);
				continue;
			}
			putcont(a[u],a[u^1],-1);
			putcont(a[v],a[v^1],-1);
			swap(a[u],a[v]);
			putcont(a[u],a[u^1],1);
			putcont(a[v],a[v^1],1);
		}else{
			int fr=ni-1,to=ni-1;
			putcont(a[fr],a[fr^1],-1);
			printf("%d\n",query(a[fr],a[fr^1],to));
			putcont(a[fr],a[fr^1],1);
		}
	}
	return 0;
}
