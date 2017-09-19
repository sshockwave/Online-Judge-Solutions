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
const int N=55;
lint f[N][N*N];
inline int ints(int n){
	return (n*(n+1))>>1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("exp.in","r",stdin);
	freopen("exp.out","w",stdout);
#endif
	int n=ni;
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1,ti=n+1;i<=ti;i++){
		for(int j=0,tj=ints(i-1);j<=tj;j++){
			for(int k=i-1,l;(l=ints(i-k-1))<=j;k--){
				f[i][j]-=f[k][j-l];
			}
		}
	}
	double ans=0;
	for(int i=0,ti=ints(n),tn=n+1;i<ti;i++){
		ans+=(double)f[tn][i]/(ti-i);
	}
	printf("%.10lf\n",ans*ints(n));
	return 0;
}
