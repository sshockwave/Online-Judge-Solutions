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
const int N=1010,O=998244353;
int f[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("comb.in","r",stdin);
	freopen("comb.out","w",stdout);
#endif
	int ldep=ni-2,n=ni;
	if(ldep<0){
		for(int i=1;i<=n;i++){
			puts("0");
		}
		return 0;
	}
	for(int i=0;i<=ldep;i++){
		f[i][1]=1;
		if(i){
			for(int j=2;j<=n;j++){
				lint tmp=0;
				for(int k=1;k<j;k++){
					tmp+=(lint)f[i-1][k]*f[i][j-k]%O;
				}
				f[i][j]=tmp%O;
				cout<<"f["<<i<<"]["<<j<<"]="<<f[i][j]<<endl;
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",f[ldep][i]);
	}
	return 0;
}
