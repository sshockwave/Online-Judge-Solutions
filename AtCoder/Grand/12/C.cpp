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
const int N=50;
int a[N],b[N],as=0,bs=0;
inline void solve(lint n){
	if(n==1){
		return;
	}
	solve(n>>1);
	a[as]=as+bs+1,as++;
	if(n&1){
		b[bs]=as+bs+1,bs++;
	}
}
int main(){
	lint n=next_num<lint>();
	solve(n+1);
	printf("%d\n",(as+bs)<<1);
	for(int i=bs-1;i>=0;i--){
		printf("%d ",b[i]);
	}
	for(int i=0;i<as;i++){
		printf("%d ",a[i]);
	}
	for(int i=1,ti=as+bs;i<=ti;i++){
		printf("%d ",i);
	}
	putchar('\n');
	return 0;
}
