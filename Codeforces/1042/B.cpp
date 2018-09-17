#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <string>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(a[0]));}
const int N=3,INF=0x7f7f7f7f;
int f[1<<N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	memset(f,127,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		char s[10];
		const int c=ni;
		scanf("%s",s);
		int state=0;
		for(int j=0;s[j];j++){
			state|=1<<(s[j]-'A');
		}
		for(int j=7;j>=0;j--){
			if(f[j]<INF){
				apmin(f[j|state],f[j]+c);
			}
		}
	}
	printf("%d\n",f[7]==INF?-1:f[7]);
	return 0;
}
