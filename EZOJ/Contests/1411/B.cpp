#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=500010;
lint f[N<<1],fs=0;
lint lend[N<<1],rend[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("pxp.in","r",stdin);
	freopen("pxp.out","w",stdout);
#endif
	lint n=next_num<lint>();
	int rt=sqrtl(n)+1e-5;
	for(lint l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		fs++,f[fs]=r-1,lend[fs]=l,rend[fs]=r;
	}
	for(int i=2;i<=rt;i++){
		if(f[i]==f[i-1])continue;
		lint i2=(lint)i*i;
		for(int j=fs;rend[j]>=i2;j--){
			lint id=rend[j]/i;
			f[j]-=f[id>rt?fs-n/id+1:id]-f[i-1];
		}
	}
	lint ans=0;
	for(int i=1;i<=rt;i++){
		if(f[i]!=f[i-1]){
			ans+=f[fs-n/(n/i)+1]-f[i];
		}
	}
	printf("%lld\n",(ans<<1)+f[rt]);
	return 0;
}
