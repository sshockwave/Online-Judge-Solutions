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
const int SH=17,N=1<<SH,O=1000000007;
inline void subset_walsh(int (*a)[SH+1],int sh,int d=1){
	int n=1<<sh;
	for(int i=0;i<sh;i++){
		int half=1<<i,full=half<<1;
		for(int j=0;j<half;j++){
			for(int k=j;k<n;k+=full){
				for(int t=0;t<=sh;t++){
					(a[k+half][t]+=d==1?a[k][t]:O-a[k][t])%=O;
				}
			}
		}
	}
}
int a[N][SH+1],b[N][SH+1],c[N][SH+1];
int bitcnt[N]={0};
int main(){
#ifndef ONLINE_JUDGE
	freopen("conv.in","r",stdin);
	freopen("conv.out","w",stdout);
#endif
	int sh=ni,n=1<<sh;
	for(int i=1;i<n;i++){
		bitcnt[i]=bitcnt[i^(i&-i)]+1;
	}
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++){
		a[i][bitcnt[i]]=ni;
	}
	memset(b,0,sizeof(b));
	for(int i=0;i<n;i++){
		b[i][bitcnt[i]]=ni;
	}
	subset_walsh(a,sh);
	subset_walsh(b,sh);
	memset(c,0,sizeof(c));
	for(int i=0;i<n;i++){
		for(int j=0;j<=sh;j++){
			for(int k=j;k<=sh;k++){
				(c[i][k]+=(lint)a[i][j]*b[i][k-j]%O)%=O;
			}
		}
	}
	subset_walsh(c,sh,-1);
	for(int i=0;i<n;i++){
		printf("%d ",c[i][bitcnt[i]]);
	}
	putchar('\n');
	return 0;
}
