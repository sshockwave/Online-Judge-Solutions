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
const int N=15,SN=1<<N,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int to[N];
int bitcnt[SN];
int f[SN];
inline int Main(){
	int n=ni,m=ni;
	for(int i=1;i<=m;i++){
		int u=ni,v=ni;
		to[u]|=1<<(v-1);
	}
	bitcnt[0]=0;
	for(int s=1,ts=1<<n;s<ts;s++){
		bitcnt[s]=bitcnt[s^(s&-s)]+1;
	}
	memset(f,0,sizeof(f));
	for(int s=0,ts=1<<n;s<ts;s++){
		if((s&1)!=((s>>1)&1))continue;
		lint ans=1;
		for(int t=s;t=s&(t-1),t;){
			if((t&1)!=((t>>1)&1))continue;
			lint tmp=1;
			for(int i=1;i<=n;i++){
				if((s>>(i-1))&1){
					if((t>>(i-1))&1){
						tmp*=(1<<bitcnt[to[i]&(((t>>(i-1))&1)?s^t:t)])-1;
					}else{
						tmp*=(1<<bitcnt[to[i]&t]);
					}
				}
			}
			ans+=tmp%O*f[t]%O;
		}
		f[s]=ans%O;
	}
	return (fpow(2,m)-f[(1<<n)-1]+O)%O;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
