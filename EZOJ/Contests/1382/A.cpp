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
const int N=15,E=110,O=1000000007;//partial
int f[E][1<<N];
int g[1<<N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("euler.in","r",stdin);
	freopen("euler.out","w",stdout);
#endif
	int n=ni,m=ni;
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		int mask=((1<<ni)^(1<<ni))>>1;
		for(int j=i-1;j>=0;j--){
			for(int s=0,ts=1<<n;s<ts;s++){
				(f[j+1][s^mask]+=f[j][s])%=O;
			}
		}
	}
	lint ans=0;
	for(int i=1;i<=m;i++){
		ans+=(lint)f[i][0]*i%O*i%O;
	}
	printf("%lld\n",ans%O);
	return 0;
}
