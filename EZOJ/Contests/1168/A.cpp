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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=1010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7f;
int a[N],b[N];
lint f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("farm.in","r",stdin);
	freopen("farm.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b[i]=ni;
	}
	f[0]=a[0]=0;
	for(int i=1;i<=n;i++){
		f[i]=LINF;
		lint sum=0;
		for(int j=i-1;j>=0;j--){
			apmin(f[i],f[j]+sum);
			sum+=b[j]*(i-j);
		}
		f[i]+=a[i];
	}
	printf("%lld\n",f[n]);
	return 0;
}
