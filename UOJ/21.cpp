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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=1000010;
int c[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tab.in","r",stdin);
	freopen("tab.out","w",stdout);
#endif
	memset(c,0,sizeof(c));
	lint sum=0,ans=0;
	int mx=0;
	for(int tot=ni;tot--;){
		int x=ni;
		c[x]++,sum+=x,apmax(mx,x);
	}
	for(int i=1;i<=mx;i++){
		c[i]+=c[i-1];
	}
	for(int x=1;x<=mx;x++){
		lint cur=0;
		for(int t=1,tt=mx/x;t<=tt;t++){
			cur+=(lint)(c[min((t+1)*x-1,mx)]-c[t*x-1])*t;
		}
		apmax(ans,cur*(x-1));
	}
	printf("%lld\n",sum-ans);
	return 0;
}
