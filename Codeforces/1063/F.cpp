#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=500010,O=5000009;
char s[N];
bool f[N],g[N];
int hs[N];
int tag[O],tim=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	const int n=ni; scanf("%s",s+1);
	int len=1;
	for(int mxp=n+1;mxp>=1;len++){
		tag[hs[mxp]]=++tim;
		mxp-=len;
		for(int i=mxp;i>=1;i--){
			f[i]=tag[hs[i]]==tim||tag[hs[i+1]]==tim;
			const int j=i+len-1;
			if(g[j]){
				tag[hs[j]]=tim;
			}
		}
		for(int i=1;i<=mxp;i++){
			g[i]=f[i];
			hs[i]=(hs[i+1]*127+s[i]-'a'+1)%O;
		}
		for(;mxp>=1&&!g[mxp];mxp--);
	}
	printf("%d\n",len-2);
	return 0;
}
