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
const int N=26,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
char s[N+1];
bool vis[N];
int f[N][N][N*N];//f[i][used][sum]
inline int fac(int n){
	int ret=1;
	for(;n;n--){
		apmul(ret,n);
	}
	return ret;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	int n=ni,k=ni;
	scanf("%s",s);
	int slen=strlen(s);
	int ans=0;
	int cnt2=s[0]-'a';
	for(int i=1;s[i];i++){
		if(s[i]<s[0]){
			cnt2--;
		}
	}
	for(int l=0,r=slen;r<=n;l++,r++){//[l,r)
		int cnt=k-slen;
		for(int i=1;s[i];i++){
			if(s[i]<s[0]){
				cnt-=n-(l+i);
			}
		}
		memset(f,0,sizeof(f));
		f[0][0][0]=1;
		if(l>0){
			f[0][1][n]=1;
		}
		for(int i=1;i<n;i++){
			for(int j=0,tj=min(i+1,cnt2);j<=tj;j++){
				for(int k=0,tk=min(((((n<<1)|1)-j)*j)>>1,cnt);k<=tk;k++){
					f[i][j][k]=f[i-1][j][k];
					if((i<l||i>=r)&&j&&k>=n-i){
						apadd(f[i][j][k],f[i-1][j-1][k-(n-i)]);
					}
				}
			}
		}
		apadd(ans,f[n-1][cnt2][cnt]);
	}
	printf("%d\n",mul(ans,mul(fac(cnt2),fac(n-slen-cnt2))));
	return 0;
}
