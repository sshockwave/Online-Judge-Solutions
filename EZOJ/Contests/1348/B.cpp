#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
const int N=1010,T=3010;
int a[N],b[N],c[N],f[T];
int lst[N];
inline bool lcmp(int x,int y){
	return (lint)b[x]*c[y]>(lint)b[y]*c[x];
}
inline int Main(){
	int n=ni,t=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni,b[i]=ni,c[i]=ni,lst[i]=i;
	}
	memset(f,0,(t+1)<<2);
	sort(lst+1,lst+n+1,lcmp);
	for(int x=1;x<=n;x++){
		for(int i=lst[x],j=t;j>=c[i];j--){
			apmax(f[j],f[j-c[i]]+a[i]-b[i]*j);
		}
	}
	int ans=0;
	for(int i=0;i<=t;i++){
		apmax(ans,f[i]);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("crazy.in","r",stdin);
	freopen("crazy.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
