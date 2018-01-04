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
const int N=210,K=16;
int f[N][1<<K];
int a[N][2];
int n,k,p,q;
int bitcnt[1<<K];
inline bool valid(int s){
	return bitcnt[s]>=q&&k-bitcnt[s]>=p;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("prince.in","r",stdin);
	freopen("prince.out","w",stdout);
#endif
	n=ni,k=ni,p=ni,q=ni;
	for(int i=1;i<=n;i++){
		a[i][0]=ni;
		a[i][1]=ni;
	}
	bitcnt[0]=0;
	for(int s=1,ts=1<<k;s<ts;s++){
		bitcnt[s]=bitcnt[s^(s&-s)]+1;
	}
	memset(f,-1,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int s=0,ts=1<<k;s<ts;s++){
			if(~f[i-1][s]){
				for(int j=0;j<2;j++){
					int t=(s>>1)|(j<<(k-1));
					if(i<k||valid(t)){
						apmax(f[i][t],f[i-1][s]+a[i][j]);
					}
				}
			}
		}
	}
	int ans=0;
	for(int s=0,ts=1<<k;s<ts;s++){
		apmax(ans,f[n][s]);
	}
	printf("%d\n",ans);
	return 0;
}
