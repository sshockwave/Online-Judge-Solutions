#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline long long next_long(){
	long long i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
long long num[N];
int ntop=0,stk[N],stop=0;
inline long long query(int x){
	int l=0,r=stop-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(stk[mid]<x){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return num[stk[l]];
}
int main(){
	char op;
	for(long long tot=next_int(),MOD=next_long(),last=0;tot--;){
		while(op=getchar(),op!='A'&&op!='Q');
		if(op=='Q'){
			printf("%lld\n",last=query(ntop-next_int()));
		}else{
			num[ntop]=(next_long()+last)%MOD;
			while(stop--,stop>=0&&num[stk[stop]]<=num[ntop]);
			stk[++stop]=ntop;
			stop++,ntop++;
		}
	}
}
