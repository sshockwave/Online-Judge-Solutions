#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,MOD=998244353;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return add(a,MOD-b);
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
inline int pxor(int a,int b){
	return add(mul(a,sub(1,b)),mul(sub(1,a),b));
}
int n;
struct BIT{
	int c[N];
	BIT(){
		memset(c,0,sizeof(c));
	}
	inline int lowbit(int x){
		return x&(-x);
	}
};
struct AC:BIT{
	inline int add(int x,int p){
		for(;x<=n;x+=lowbit(x)){
			c[x]=pxor(c[x],p);
		}
	}
	inline int sum(int x){
		int sum=0;
		for(;x;x-=lowbit(x)){
			sum=pxor(sum,c[x]);
		}
	}
}bit;
struct WA:BIT{
	inline int add(int x,int p){
		for(;x;x-=lowbit(x)){
			c[x]=pxor(c[x],p);
		}
	}
	inline int sum(int x){
		int sum=0;
		for(;x<=n;x+=lowbit(x)){
			sum=pxor(sum,c[x]);
		}
	}
}wbit;
int main(){
	n=ni;
	for(int tot=ni;tot--;){
		if(ni==1){
			int l=ni,r=ni;
			int p=fpow(r-l+1,MOD-2);
			for(int i=l;i<=r;i++){
				bit.add(i,p);
				wbit.add(i,p);
			}
		}else{
			int l=ni,r=ni;
			int p1=pxor(bit.sum(r),bit.sum(l-1));
			int p2=pxor(wbit.sum(r),wbit.sum(l-1));
			printf("%d\n",sub(1,pxor(p1,p2)));
		}
	}
}
