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
const int N=3010;
int O;
int inv[N];
inline void gmath(int n){
	inv[1]=1;
	for(int i=2;i<=n;i++){
		inv[i]=(lint)(O-O/i)*inv[O%i]%O;
		assert((lint)inv[i]*i%O==1);
	}
}
int f[N],g[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
#endif
	int n=ni;
	O=ni;
	gmath(n);
	memset(g,0,sizeof(g));
	f[1]=1;
	for(int i=1;i<=n;i++){
		g[i]++;
	}
	for(int i=2;i<=n;i++){
		lint ans=0;
		for(int j=1;j<i;j++){
			ans+=(lint)f[j]*g[i-j]%O;
		}
		f[i]=ans%O*inv[i-1]%O;
		int tmp=(lint)f[i]*i%O;
		for(int j=i;j<=n;j+=i){
			g[j]=(g[j]+tmp)%O;
		}
	}
	printf("%d\n",f[n]);
	puts("0");
	puts("0");
	return 0;
}
