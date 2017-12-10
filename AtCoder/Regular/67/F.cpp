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
const int N=5010,M=210;
int nxt[N][M];
lint x[N],a[N][M],dt[N];
int main(){
	int n=ni,m=ni;
	for(int i=2;i<=n;i++){
		x[i]=x[i-1]+ni;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=ni;
		}
	}
	memset(dt,0,sizeof(dt));
	lint ans=0;
	for(int i=n;i>=1;i--){
		lint cur=0;
		for(int j=1;j<=m;j++){
			cur+=a[i][j];
			dt[i+1]+=a[i+1][j]-a[i][j];
			for(int &k=nxt[i][j]=i+1;k<=n&&a[i][j]>=a[k][j];k=nxt[k][j]){
				dt[k]-=a[k][j]-a[i][j];
				dt[nxt[k][j]]+=a[k][j]-a[i][j];
			}
		}
		for(int j=i;j<=n;j++){
			cur+=dt[j];
			apmax(ans,cur-(x[j]-x[i]));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
