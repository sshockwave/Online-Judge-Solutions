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
const int N=100010;
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	int n=ni,tot=ni,k=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	while(tot--){
		int l=ni,r=ni;
		lint cnt=0;
		for(int i=l;i<=r;i++){
			int sum=0;
			for(int j=i;j<=r;j++){
				sum^=a[j];
				cnt+=sum==k;
			}
		}
		printf("%lld\n",cnt);
	}
	return 0;
}
