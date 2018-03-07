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
const int N=1000010;
int pri[N],ps=0;
bool np[N];
int f[N];
inline void sieve(int n){
	f[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			pri[ps++]=i;
			f[i]=i%3==1?1:-1;
		}
		for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
			np[t]=true;
			f[t]=f[i]*f[p];
			if(i%p==0)break;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("function.in","r",stdin);
	freopen("function.out","w",stdout);
#endif
	int n=ni;
	sieve(n);
	for(int i=1;i<=n;i++){
		printf("%d ",f[i]);
	}
	putchar('\n');
	return 0;
}
