#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int MOD=1000000007,QP=31623,N=10000007;
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
int val[N],pt[N],tag[N],tim=1;
inline void store(int v,int to){
	int x=v%N;
	for(;tag[x]==tim;x++);
	val[x]=v;
	tag[x]=tim;
	pt[x]=to;
}
inline int dlog(int a,int b){
	a%=MOD,b%=MOD;
	if(a==0||b==0){
		if(a||b){
			return -1;
		}else{
			return 0;
		}
	}
	int t=1;
	for(int i=0;i<QP;i++,t=mul(t,a)){
		store(mul(b,t),i);
	}
	for(int j=0,f=1;j<=QP;j++,f=mul(f,t)){
		for(int x=f%N;tag[x]==tim;x++){
			if(val[x]==f){
				return (j*QP+MOD-1-pt[x])%(MOD-1);
			}
		}
	}
	return -1;
}
int main(){
	for(int tot=ni();tim<=tot;tim++){
		int a=ni(),b=ni();
		printf("%d\n",dlog(a,b));
	}
}
