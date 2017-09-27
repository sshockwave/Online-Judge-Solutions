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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=510;
int f[N][N];
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("palindrome.in","r",stdin);
	freopen("palindrome.out","w",stdout);
#endif
	memset(f,127,sizeof(f));
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		f[i][i]=1;
	}
	for(int i=1;i<n;i++){
		f[i][i+1]=(a[i]!=a[i+1])+1;
	}
	for(int i=3;i<=n;i++){
		for(int l=1,r=i;r<=n;l++,r++){
			for(int k=l;k<r;k++){
				apmin(f[l][r],f[l][k]+f[k+1][r]);
			}
			if(a[l]==a[r]){
				apmin(f[l][r],f[l+1][r-1]);
			}
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}
