#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=5010,O=998244353,INF=0x7f7f7f7f;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
inline void input(int s[],int &n){
	static char t[N];
	scanf("%s",t+1);
	n=strlen(t+1);
	for(int i=1;i<=n;i++){
		s[i]=t[i]=='P'?-1:t[i]=='V'?1:0;
	}
}
inline void dp(int s[],int n,int (*f)[2],int &mn,int &mx){
	static int tf[N<<1][2];
	mn=mx=N;
	f[N][0]=0,f[N][1]=1;
	for(int i=n;i>=1;i--){
		mcpy(tf+mn,f+mn,mx-mn+1);
		const int tmn=mn-(s[i]<=0);
		const int tmx=mx+(s[i]>=0);
		mset(f+tmn,0,tmx-tmn+1);
		for(int j=mn;j<=mx;j++){
			for(int k=0;k<2;k++){
				const int F=tf[j][k];
				if(F==0)continue;
				if(s[i]>=0){
					apadd(f[j+1][k],F);
				}
				if(s[i]<=0){
					apadd(f[min(j,N)-1][i==n?true:N<j?false:k],F);
				}
			}
		}
		mn=tmn,mx=tmx;
	}
}
int f1[N<<1][2],f2[N<<1][2];
int s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int n,mn1,mx1;
	input(s,n),dp(s,n,f1,mn1,mx1);
	int m,mn2,mx2;
	input(s,m),dp(s,m,f2,mn2,mx2);
	f1[mx1+1][0]=f1[mx1+1][1]=0;
	for(int i=mx1;i>=mn1;i--){
		apadd(f1[i][0],f1[i+1][0]);
		apadd(f1[i][1],f1[i+1][1]);
	}
	int ans=0;
	for(int i=mn2;i<=mx2;i++){
		int ti=i-N;
		{
			int cur=0;
			{
				int j=(-ti-1)+N;
				apmax(j,mn1),apmin(j,mx1+1);
				apadd(cur,f1[j][0]);
			}
			{
				int j=(-ti)+N;
				apmax(j,mn1),apmin(j,mx1+1);
				apadd(cur,f1[j][1]);
			}
			apadd(ans,(lint)cur*f2[i][0]);
		}
		{
			int j=(-ti)+N;
			apmax(j,mn1),apmin(j,mx1+1);
			apadd(ans,(lint)(f1[j][0]+f1[j][1])*f2[i][1]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
