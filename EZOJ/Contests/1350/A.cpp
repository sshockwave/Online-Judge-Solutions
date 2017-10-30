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
const int N=500010;
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("pick.in","r",stdin);
	freopen("pick.out","w",stdout);
#endif
	int n=ni,R=ni,C=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	sort(a+1,a+n+1);
	int l=0,r=a[n]-a[1];
	while(l<r){
		int m=(l+r)>>1;
		int cnt=0;
		for(int i=1,ti=n-C+1;i<=ti;){
			i+=a[i+C-1]-a[i]<=m?(++cnt,C):1;
		}
		if(cnt>=R){
			r=m;
		}else{
			l=m+1;
		}
	}
	printf("%d\n",l);
	return 0;
}
