#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline uint fpow(uint x,int n){
	uint a=1;
	for(;n;n>>=1,x*=x){
		if(n&1){
			a*=x;
		}
	}
	return a;
}
inline int Main(){
	uint a=ni;
	int n=ni,ans=0;
	if(a&1){
		return 1;
	}
	uint sed=1u<<n,sed1=sed-1,l=1;
	uint tb=min((uint)n,sed);
	for(uint b=1;b<=tb;b++){
		l*=a;
		ans+=(l&sed1)==(fpow(b,a)&sed1);
	}
	int tmp=1<<(n/a+(n%a!=0));
	return ans+sed/tmp-tb/tmp;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
