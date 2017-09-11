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
	freopen("ellipsoid.in","r",stdin);
	freopen("ellipsoid.out","w",stdout);
#endif
	double a,b,c,d,e,f;
	while(scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f)!=EOF){
		printf("%.10lf\n",min(1/a,min(1/b,1/c)));
	}
	return 0;
}
