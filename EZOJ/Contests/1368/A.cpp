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
inline lint Main(){
	lint n=ni;
	lint m=next_num<lint>();
	lint s=next_num<lint>();
	m-=(n-1)*(n-2)/2;
	if(m<=1)return (s-(n-2))+(m+(n-1)*(n-2)/2-1);
	if(m*2<=n-1)return (n-1)*(n-2)/2+(s-(n-2))*m;
	lint x=s/(n-1);
	lint ans=(n-1)*(n-2)/2*x+(s-(n-2)*x)*m;
	if(x+1<=s-(n-2)*x-1){
		lint t=s-(n-2)*x-(x+1);
		apmin(ans,ans+(2*n-3-t)*t/2-m*t);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
