#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=2010;
int f[N][N];
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	sort(a+1,a+n+1);
	memset(f,-1,sizeof(f));
	for(int i=a[n],k=n;i>=0;i--){
		for(;k&&a[k]>i;k--);
		f[i][n-k]=true;
		for(int j=n-k-1;j>=0;j--){
			f[i][j]=!f[i][j+1];
			if(~f[i+1][j]){
				f[i][j]|=!f[i+1][j];
			}
		}
	}
	puts(f[0][0]?"First":"Second");
	return 0;
}
