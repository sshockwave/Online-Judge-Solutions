#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
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
const int n=ni,N=500010,MOD=998244353;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
namespace B{
	int c[N];
	inline void init(){
		memset(c,0,sizeof(c));
	}
	inline int lowbit(const int &x){
		return x&(-x);
	}
	inline void add(int x,int v){
		for(;x<=n;apadd(c[x],v),x+=lowbit(x));
	}
	inline int sum(int x){
		int ans=0;
		for(;x;apadd(ans,c[x]),x^=lowbit(x));
		return ans;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
int *num[N],h[N],pre[N],nxt[N],val[N],_val[N];
inline bool numcmp(int* a,int* b){
	if((*a)==(*b)){
		return a<b;
	}
	return (*a)<(*b);
}
int f[N];
int main(){
	{//get f
		const int rev2=(MOD+1)>>1;
		int sum=0;
		for(int i=1;i<=n;i++){
			f[i]=sum;
			apadd(sum,mul(mul(i,i+1),rev2));
		}
	}
	{//get h
		for(int i=1;i<=n;i++){
			num[i]=&(h[i]=ni);
		}
		sort(num+1,num+n+1,numcmp);
		for(int i=1;i<=n;i++){
			*num[i]=i;
		}
	}
	{//get pre&&nxt
		h[0]=h[n+1]=0;
		for(int i=1;i<=n;i++){
			for(int &j=pre[i]=i-1;h[j]>h[i];j=pre[j]);
		}
		for(int i=n;i>=1;i--){
			for(int &j=nxt[i]=i+1;h[j]>h[i];j=nxt[j]);
		}
	}
	{//get _val
		_val[0]=0;
		for(int i=1;i<=n;i++){
			val[i]=mul(i-pre[i],nxt[i]-i);
			_val[i]=add(_val[i-1],val[i]);
		}
	}
	int ans=0;
	{//get ans
		B::init();
		for(int i=n;i>=1;i--){
			apadd(ans,mul(val[i],sub(B::ask(h[i],n),sub(_val[nxt[i]-1],_val[i]))));
			apadd(ans,mul(f[nxt[i]-i],i-pre[i]));
			B::add(h[i],val[i]);
		}
	}
	printf("%d\n",ans);
}
