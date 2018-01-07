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
const int N=110;
lint LINF=0x7f7f7f7f7f7f7f7f;
lint g[N][N][2];
int _a[N]={0};
inline void dp(int a[],lint b[],int n){
	for(int i=1;i<=n;i++){
		_a[i]=_a[i-1]+a[i];
	}
	for(int len=n-1;len>=1;len--){
		for(int l=1,r=len;r<=n;l++,r++){
			for(int p=0;p<2;p++){
				lint &ans=g[l][r][p]=LINF;
				int pos=p==0?l:r;
				if(l>1){//go left
					lint tmp=a[l-1]+b[l-1];//let go
					if(len+1!=n){
						apmax(tmp,g[l-1][r][0]);//block
					}
					apmin(ans,(_a[pos]-_a[l-1])+tmp);
				}
				if(r<n){//go right
					lint tmp=a[r+1]+b[r+1];//let go
					if(len+1!=n){
						apmax(tmp,g[l][r+1][1]);//block
					}
					apmin(ans,(_a[r]-_a[pos-1])+tmp);
				}
			}
		}
	}
}
int a[N][N];
lint f[N][N];
inline lint Main(){
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=ni;
		}
	}
	//to be better
	for(int j=1;j<=m;j++){
		f[n][j]=a[n][j];
	}
	for(int i=n-1;i>=1;i--){
		dp(a[i],f[i+1],m);
		for(int j=1;j<=m;j++){
			f[i][j]=min(g[j][j][0],g[j][j][1]);
		}
	}
	lint ans=LINF;
	for(int j=1;j<=m;j++){
		apmin(ans,f[1][j]);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fan.in","r",stdin);
	freopen("fan.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%lld\n",Main());
	}
	return 0;
}
