#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
template<class T>inline lint lcm(const T &a,const T &b){return (lint)a/gcd(a,b)*b;}
const int N=510,O=232792561;
inline void apadd(int &a,const int &b){
	a=(a+b)%O;
}
lint n;
int k;
namespace brute1{
	int f[N][N][20];
	int lst[N];
	inline int main(){
		int ls=0;
		for(int i=1;i<=n;i++){
			if(n%i==0){
				lst[++ls]=i;
			}
		}
		memset(f,0,sizeof(f));
		f[0][1][0]=1;
		for(int i=1;i<=ls;i++){
			int x=lst[i];
			for(int j=1;j<=ls;j++){
				int y=lst[j];
				for(int t=0;t<k;t++){
					apadd(f[i][lcm(x,y)][(t+x)%k],f[i-1][y][t]);
				}
			}
			for(int j=1;j<=ls;j++){
				int y=lst[j];
				for(int t=0;t<k;t++){
					apadd(f[i][y][t],f[i-1][y][t]);
				}
			}
		}
		return f[ls][n][0];
	}
}
inline int Main(){
	n=next_num<lint>(),k=ni;
	if(n<=1000)return brute1::main();
	srand(time(0));
	return rand()%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("lcm.in","r",stdin);
	freopen("lcm.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
