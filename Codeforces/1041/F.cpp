#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=100010;
int n,m;
int x[N],y[N];
inline int work(lint gap){
	map<int,int>cnt;
	for(int i=1;i<=n;i++){
		++cnt[x[i]%(gap<<1)];
	}
	for(int i=1;i<=m;i++){
		++cnt[(y[i]+gap)%(gap<<1)];
	}
	int ans=0;
	for(map<int,int>::iterator it=cnt.begin(),ti=cnt.end();it!=ti;++it){
		apmax(ans,it->second);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
#endif
	n=ni,ni;
	for(int i=1;i<=n;i++){
		x[i]=ni;
	}
	m=ni,ni;
	for(int i=1;i<=m;i++){
		y[i]=ni;
	}
	int ans=2;
	for(int i=0;i<=30;i++){
		apmax(ans,work(1ll<<i));
	}
	printf("%d\n",ans);
	return 0;
}
