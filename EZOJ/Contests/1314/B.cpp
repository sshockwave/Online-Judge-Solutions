#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=510,MOD=998244353;
int f[N][N][2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	memset(f,0,sizeof(f));
	f[1][0][0]=f[1][1][1]=1;
	for(int i=1;i<n;i++){//max subtree size
		for(int j=i+1;j<=n;j++){
			for(int k=0;k<j;k++){
				for(int l=0;l<=k;l++){
					apadd(f[j][k][0],add(add(f[j-i][k-l][0],f[i][l][0]),f[i][l][1]));
					apadd(f[j][k][1],add(f[j-i][k-l][0],f[i][l][0]));
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			printf("%d ",f[i][j][0]+f[i][j][1]);
		}
		putchar('\n');
	}
}
