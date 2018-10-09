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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=6,M=10010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int n,m;
int a[N][M],b[N][M],c1[N][M],c2[N][M];
lint f[M][1<<N];
inline lint solve(const int sh){
	const int sn=1<<n;
	for(int j=1;j<=m;j++){
		for(int s=0;s<sn;s++){
			f[j][s]=0;
			for(int i=1;i<=n;i++){
				f[j][s]+=(((a[i][j]>>sh)^(s>>(i-1)))&1)*b[i][j];
				if(i<n){
					f[j][s]+=(((s>>(i-1))^(s>>i))&1)*c2[i][j];
				}
			}
			f[j][s]+=(((s>>(n-1))^s)&1)*c2[n][j];
			lint ans=LINF;
			for(int ts=0;ts<sn;ts++){
				lint cur=f[j-1][ts];
				for(int i=1;i<=n;i++){
					cur+=(((s^ts)>>(i-1))&1)*c1[i][j-1];
				}
				apmin(ans,cur);
			}
			f[j][s]+=ans;
		}
	}
	lint ans=LINF;
	for(int s=0;s<sn;s++){
		apmin(ans,f[m][s]);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chessboard.in","r",stdin);
	freopen("chessboard.out","w",stdout);
#endif
	n=ni,m=ni;
	memset(f[0],0,sizeof(f[0]));
	int mx_a=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=ni;
			apmax(mx_a,a[i][j]);
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[i][j]=ni;
	for(int i=1;i<=n;i++)for(int j=1;j<m;j++)c1[i][j]=ni;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c2[i][j]=ni;
	lint ans=0;
	for(int i=0;(1<<i)<=mx_a;i++){
		ans+=solve(i)<<i;
	}
	printf("%lld\n",ans);
	return 0;
}
