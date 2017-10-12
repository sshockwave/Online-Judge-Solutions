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
char str[N][L];
lint dfi[1<<L];
int dficnt[1<<L];
double f[1<<L];
int cnt[128],tag[128],tim=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("memory.in","r",stdin);
	freopen("memory.out","w",stdout);
#endif
	int n=ni,l;
	for(int i=0;i<n;i++){
		scanf("%s",str[i]);
	}
	l=strlen(str[0]);
	dfi[0]=0;
	dficnt[0]=0;
	memset(tag,0,sizeof(tag));
	for(int s=1,ts=1<<l;s<ts;s++){
		int x=s&-s,sh=0;
		lint last=dfi[s^x];
		for(;(1<<sh)<x;sh++);
		tim++;
		for(int i=0;i<n;i++){
			if(((last>>i)&1)==0){
				if(tag[str[i][sh]]<tim){
					tag[str[i][sh]]=tim;
					cnt[str[i][sh]]=0;
				}
				cnt[str[i][sh]]++;
			}
		}
		dfi[s]=last;
		dficnt[s]=dficnt[s^x];
		for(int i=0;i<n;i++){
			if(((last>>i)&1)==0){
				if(cnt[str[i][sh]]==1){
					dfi[s]|=1ll<<i;
					dficnt[s]++;
				}
			}
		}
	}
	for(int s=(1<<l)-1;s>=0;s--){
		f[s]=0;
		if(dficnt[s]!=n){
			int totunvis=0;
			for(int i=0;i<l;i++){
				if(((s>>i)&1)==0){
					totunvis++;
					int toS=s|(1<<i);
					if(dficnt[toS]<n){
						f[s]+=(double)(n-dficnt[toS])/(n-dficnt[s])*f[toS];
					}
				}
			}
			f[s]=f[s]/totunvis+1;
		}
	}
	printf("%.10lf\n",f[0]);
	return 0;
}
