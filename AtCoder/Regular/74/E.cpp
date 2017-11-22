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
const int N=310,O=1000000007,INF=0x7f7f7f7f;
int mxlim[N][4],mnlim[N][4];
int f[N][N][N];
int main(){
	int n=ni+3;
	memset(mnlim,127,sizeof(mnlim));
	memset(mxlim,0,sizeof(mxlim));
	for(int tot=ni;tot--;){
		int l=ni+3,r=ni+3,t=ni;
		apmin(mnlim[r][t],l);
		apmax(mxlim[r][t],l);
	}
	memset(f,0,sizeof(f));
	f[1][2][3]=1;
	for(int k=3;k<=n;k++){
		for(int i=1,ti=k-2;i<=ti;i++){
			for(int j=i+1;j<k;j++){
				bool flag1=j<mnlim[k][1];
				bool flag2=i<mnlim[k][2]&&j>=mxlim[k][2];
				bool flag3=i>=mxlim[k][3];
				int &F=f[i][j][k];
				if(!(flag1&&flag2&&flag3)){
					F=0;
				}
				if(F==0)continue;
				(f[i][j][k+1]+=F)%=O;//color 1
				(f[i][k][k+1]+=F)%=O;//color 2
				(f[j][k][k+1]+=F)%=O;//color 3
			 }
		}
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ans+=f[i][j][n];
		}
	}
	printf("%lld\n",ans%O);
	return 0;
}
