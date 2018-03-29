#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=1000010,D=100,O=998244353;
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int go[N][D],f[N],fail[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("klavir.in","r",stdin);
	freopen("klavir.out","w",stdout);
#endif
	const int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		int c=ni-1;
		fail[i]=go[i-1][c],go[i-1][c]=i;
		memcpy(go[i],go[fail[i]],m<<2);
		lint sum=0;
		for(int j=0;j<m;j++){
			sum+=f[go[i-1][j]];
		}
		f[i]=((lint)n*(f[i-1]+1)-sum%O)%O;
		printf("%d\n",f[i]);
	}
	return 0;
}   
