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
const int N=3010,O=1000000007;
int f[N][N][2];
int main(){
	int n=ni,m=ni;
	memset(f,0,sizeof(f));
	for(int i=0;i<=n;i++){
		f[0][i][i==0]=1;
	}
	for(int i=1;i<=m;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<2;k++){
				int F=f[i-1][j][k];
				if(F==0)continue;
				int cnt1=j,cnt2=n-j;
				for(int a=0;a<=1;a++){
					if(cnt1-a<0)continue;
					if(cnt2-(!a)<0)continue;
					for(int b=0;b<=1;b++){
						(f[i][cnt1-a+1-b][k||cnt1-a==0||cnt1-a+1-b==0]+=F)%=O;
					}
				}
			}
		}
	}
	lint ans=0;
	for(int i=0;i<=n;i++){
		ans+=f[m][i][1];
	}
	printf("%lld\n",ans%O);
	return 0;
}
