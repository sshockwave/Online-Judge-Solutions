#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
#define cout cerr
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=1500010;
void solve(lint a[],int n){
	if(n==1){
		return;
	}
	int half=n>>1;
	lint s0=a[half-1],s1=a[n-1]-s0;
	for(int i=0;i<half;i++){
		a[i]=(a[i+half]+a[i]-s1)>>1;
		a[i+half]-=a[i];
	}
	solve(a,half),solve(a+half,half);
}
lint a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("spy.in","r",stdin);
	freopen("spy.out","w",stdout);
#endif
	int n=ni;
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	solve(a,n);
	for(int i=0;i<n;i++){
		printf("%lld ",a[i]);
	}
	putchar('\n');
}
