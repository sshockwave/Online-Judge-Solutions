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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("prob.in","r",stdin);
	freopen("prob.out","w",stdout);
#endif
	double n=ni;
	printf("%.9lf\n",n*(n+1)/(2*(2*n-1)));
	return 0;
}
