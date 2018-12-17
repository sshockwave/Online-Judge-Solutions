#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1000010;
int a[N];
int cnt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	const int n=ni;
	int tot=ni;
	mset(cnt+1,0,n);
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(;tot--;){
		int p=ni;
		for(int i=1;i<=p;i++){
			++cnt[a[i]];
		}
		int mxp=n;
		bool r=false;
		int tmpmx=-1;
		lint ans=0;
		for(int tt=n;tt--;){
			if(tmpmx==-1){
				for(;cnt[mxp]==0;mxp--);
				--cnt[mxp],tmpmx=mxp;
			}
			if(r){
				ans-=tmpmx;
			}else{
				ans+=tmpmx;
			}
			r^=1;
			tmpmx=-1;
			if(p<n){
				++p;
				if(a[p]<=mxp){
					++cnt[a[p]];
				}else{
					tmpmx=a[p];
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
