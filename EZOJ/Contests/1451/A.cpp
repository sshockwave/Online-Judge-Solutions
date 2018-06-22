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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,O=1000000007;
int f[N],_f[N];
int g[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("split.in","r",stdin);
	freopen("split.out","w",stdout);
#endif
	const int n=ni,m=ni;
	f[0]=_f[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=_f[i/m];
		_f[i]=(_f[i-1]+f[i])%O;
	}
	memset(g,0,sizeof(g));
	g[0]=1;
	for(int tot=ni;tot--;){
		for(int i=n;i>=0;i--){
			int ans=0;
			for(int j=0;j<=i;j++){
				ans=(ans+(lint)g[j]*f[i-j])%O;
			}
			g[i]=ans;
		}
	}
	lint ans=0;
	for(int i=0;i<=n;i++){
		ans+=g[i];
	}
	printf("%lld\n",ans%O);
	return 0;
}
