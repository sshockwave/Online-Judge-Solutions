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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=11,M=13,SN=1<<10,NM=10*12+10;
int f[NM][SN],g[SN];
int n,m,sn;
int bitcnt[SN];
inline void dp_bitcnt(){
	for(int i=0;i<sn;i++){
		bitcnt[i]=i?bitcnt[i^(i&-i)]+1:0;
	}
}
inline void dp_g(){
	for(int s=0;s<sn;s++){
		if(bitcnt[s]&1)continue;
		int las=-1;
		int &ans=g[s]=0;
		for(int i=0;i<n;i++){
			if((s>>i)&1){
				if(las==-1){
					las=i;
				}else{
					ans+=i-las+1;
					las=-1;
				}
			}
		}
		assert(las==-1);
	}
}
inline void dp_f(const int bmask,const int wcnt){
	for(int i=wcnt;i>=0;i--){
		for(int s=0;s<sn;s++){
			const int F=f[i][s];
			if(F<0)continue;
			for(int t=bmask;;t=(t-1)&bmask){
				if(bitcnt[t]&1)continue;
				apmax(f[i+bitcnt[t]][s^t],F+g[t]+bitcnt[s^(s&t)]);
				if(t==0)break;
			}
		}
	}
}
char s[N][M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("mirror.in","r",stdin);
	freopen("mirror.out","w",stdout);
#endif
	n=ni,m=ni,sn=1<<n;
	dp_bitcnt();
	dp_g();
	for(int i=0;i<n;i++){
		scanf("%s",s[i]);
	}
	memset(f,-1,sizeof(f));
	f[0][0]=0;
	int wcnt=0;
	for(int j=0;j<m;j++){
		int bmask=0;
		for(int i=0;i<n;i++){
			bmask|=(s[i][j]=='1')<<i;
		}
		dp_f(bmask,wcnt);
		wcnt+=bitcnt[bmask]>>1<<1;
	}
	int mx=0;
	for(int i=0;i<=n*m;i++){
		apmax(mx,f[i][0]);
		printf("%d\n",4*n*m-mx*2);
	}
	return 0;
}
