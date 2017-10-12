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
const int N=55,L=20;
char str[N][L+1];
lint dfi[1<<L];
int dficnt[1<<L];
double f[1<<L];
int bcnt[1<<L];
inline int bitcnt(lint x){
	static const int A=(1<<L)-1,L2=L<<1;
	return bcnt[x&A]+bcnt[(x>>L)&A]+bcnt[(x>>L2)&A];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("memory.in","r",stdin);
	freopen("memory.out","w",stdout);
#endif
	int n=ni;
	for(int i=0;i<n;i++){
		scanf("%s",str[i]);
	}
	int m=strlen(str[0]),shm=1<<m;
	memset(dfi,0,sizeof(dfi));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i==j){
				continue;
			}
			int tmp=0;
			for(int k=0;k<m;k++){
				tmp|=(str[i][k]==str[j][k])<<k;
			}
			dfi[tmp]|=1ll<<i;
		}
	}
	bcnt[0]=0;
	for(int s=1,ts=1<<L;s<ts;s++){
		bcnt[s]=bcnt[s^(s&-s)]+1;
	}
	for(int s=shm-1;s>=0;s--){
		for(int t=s;t;t^=t&-t){
			dfi[s^(t&-t)]|=dfi[s];
		}
		dfi[s]^=(1ll<<n)-1;
		dficnt[s]=bitcnt(dfi[s]);
	}
	for(int s=shm-1;s>=0;s--){
		f[s]=0;
		if(dficnt[s]<n){
			for(int t=s,x;t<shm;t|=x){
				x=(t+1)&-(t+1);
				if(dficnt[s|x]<n){
					f[s]+=(double)(n-dficnt[s|x])/(n-dficnt[s])*f[s|x];
				}
			}
			f[s]=f[s]/bcnt[s^(shm-1)]+1;
		}
	}
	printf("%.10lf\n",f[0]);
	return 0;
}
