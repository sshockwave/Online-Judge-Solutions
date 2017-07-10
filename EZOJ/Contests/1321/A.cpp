#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define cout cerr
#define ni (next_num<int>())
#define nu (next_num<uint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=10000010;
const uint UINF=2147483647u;
uint num[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("minval.in","r",stdin);
	freopen("minval.out","w",stdout);
#endif
	int n=ni,m=ni;
	uint x0=nu,x1=nu,a=nu,b=nu,c=nu,x2=a*x0+b*x1+c,x3;
	x0=x1,x1=x2;
	for(int i=1;i<=n;i++){
		num[i]=UINF;
	}
	uint mn=UINF,mnp,pw=1,ans=0;
	for(int i=1;i<=m;i++){
		uint x=(x0>>2)%n,v=x1>>2;
		num[x]=v;
		if(v<=mn){
			mn=v,mnp=x;
		}else if(x==mnp){
			mn=UINF;
			for(int i=1;i<=n;i++){
				if(num[i]<mn){
					mn=num[i];
					mnp=i;
				}
			}
		}
		pw*=10099u,ans+=mn*pw;
		x2=a*x0+b*x1+c,x3=a*x1+b*x2+c;
		x0=x2,x1=x3;
	}
	printf("%u\n",ans);
}
