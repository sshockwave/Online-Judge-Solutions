#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=110,O=1000000009;
int c[N][N];
inline void gmath(int n){
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%O;
		}
	}
}
lint f[N][N];
char s[N],t[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	int n=ni,tot=ni,m=ni;
	gmath(n);
	scanf("%s%s",s,t);
	int cnt=0;
	for(int i=0;s[i];i++){
		cnt+=s[i]!=t[i];
	}
	memset(f,0,sizeof(f));
	f[0][cnt]=1;
	for(int i=0;i<tot;i++){
		for(int j=0;j<=n;j++){//j differs
			lint tmp=f[i][j]%=O;
			for(int k=max(0,m-n+j),tk=min(m,j);k<=tk;k++){//from j has k
				f[i+1][j-k+m-k]+=tmp*c[j][k]%O*c[n-j][m-k]%O;
			}
		}
	}
	printf("%lld\n",f[tot][0]%O);
	return 0;
}
