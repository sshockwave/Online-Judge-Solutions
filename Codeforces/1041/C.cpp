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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(a[0]));}
const int N=200010;
int a[N];
int perm[N];
int ans[N];
int que[N],qh=0,qt=0;
inline bool pcmp(int x,int y){
	return a[x]<a[y];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	const int n=ni,m=ni,d=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		perm[i]=i;
	}
	sort(perm+1,perm+n+1,pcmp);
	for(int i=1;i<=n;i++){
		const int x=perm[i];
		if(qh<qt&&a[x]-a[que[qh]]-1>=d){
			ans[x]=ans[que[qh]];
			qh++;
		}else{
			ans[x]=qt-qh+1;
		}
		que[qt++]=x;
	}
	printf("%d\n",qt-qh);
	for(int i=1;i<=n;i++){
		printf("%d%c",ans[i]," \n"[i==n]);
	}
	return 0;
}
