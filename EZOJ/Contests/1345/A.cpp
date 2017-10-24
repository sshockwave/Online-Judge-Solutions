#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=200010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7f;
int a[N],b[N],lst[N];
inline bool lcmp(int x,int y){
	return a[x]<a[y];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
#endif
	int n=ni,mx=1,mn=1,mxcnt;
	for(int i=1;i<=n;i++){
		a[i]=ni,b[i]=ni;
		if(a[i]>b[i]){
			swap(a[i],b[i]);
		}
		if(a[i]<a[mn]){
			mn=i;
		}
		if(b[i]>b[mx]){
			mx=i,mxcnt=1;
		}else if(b[i]==b[mx]){
			mxcnt++;
		}
		lst[i]=i;
	}
	lint ans;
	{
		int lmx=mn,rmn=mx;
		for(int i=1;i<=n;i++){
			if(a[i]>a[lmx]){
				lmx=i;
			}
			if(b[i]<b[rmn]){
				rmn=i;
			}
		}
		ans=(lint)(a[lmx]-a[mn])*(b[mx]-b[rmn]);
	}
	if(mn!=mx){
		sort(lst+1,lst+n+1,lcmp);
		int rmn=INF,rmx=0,cans=INF;
		for(int i=1;;i++){
			int x=lst[i];
			if(b[x]==b[mx]&&--mxcnt==0){
				break;
			}
			assert(i<n);
			apmin(rmn,b[x]);
			apmax(rmx,b[x]);
			apmin(cans,max(rmx,a[lst[n]])-min(rmn,a[lst[i+1]]));
		}
		apmin(ans,(lint)(b[mx]-a[mn])*cans);
	}
	printf("%lld\n",ans);
	return 0;
}
