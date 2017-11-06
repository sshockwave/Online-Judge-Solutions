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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=17,INF=0x7f7f7f7f;
char tp[N];
int r[N],b[N];
int f[1<<16][16*16/2],bitcnt[1<<N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("chip.in","r",stdin);
	freopen("chip.out","w",stdout);
#endif
	int n=ni,ans=INF;
	int rmask=0,bmask=0;
	int rsum=0,bsum=0;
	for(int i=1;i<=n;i++){
		tp[i]=nc(),r[i]=ni,b[i]=ni;
		rsum+=r[i],bsum+=b[i];
		(tp[i]=='R'?rmask:bmask)|=1<<(i-1);
	}
	bitcnt[0]=0;
	memset(f,-1,sizeof(f));
	f[0][0]=0;
	for(int s=0,ts=1<<n;s<ts;s++){
		bitcnt[s]=s?bitcnt[s^(s&-s)]+1:0;
		int rcnt=bitcnt[s&rmask],bcnt=bitcnt[s&bmask];
		int tj=rcnt*bcnt+((rcnt*(rcnt-1))>>1);
		for(int i=0;i<n;i++){
			if(!((s>>i)&1)){
				int tmp=s|(1<<i),ta=min(rcnt,r[i+1]),tb=min(bcnt,b[i+1]);
				for(int j=0;j<=tj;j++){
					if(f[s][j]>=0){
						apmax(f[tmp][j+ta],f[s][j]+tb);
					}
				}
			}
		}
	}
	for(int i=0,s=(1<<n)-1,rcnt=bitcnt[s&rmask],bcnt=bitcnt[s&bmask],ti=rcnt*bcnt+((rcnt*(rcnt-1))>>1);i<=ti;i++){
		apmin(ans,max(rsum-i,bsum-f[s][i]));
	}
	printf("%d\n",ans+n);
	return 0;
}
