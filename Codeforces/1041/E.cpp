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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(a[0]));}
const int N=1010;
int cnt[N];
int que[N],qh=0,qt=0;
struct Edge{
	int u,v;
}edg[N];
int es=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
#endif
	int n=ni;
	mset(cnt+1,0,n);
	for(int i=1;i<n;i++){
		const int a=ni;
		if(ni!=n){
			puts("NO");
			return 0;
		}
		++cnt[a];
	}
	for(int i=1;i<n;i++){
		if(cnt[i]==0){
			que[qt++]=i;
			continue;
		}
		--cnt[i];
		int last=i;
		for(;cnt[i];--cnt[i]){
			if(qh==qt){
				puts("NO");
				return 0;
			}
			int x=que[qh++];
			edg[++es]=(Edge){last,x};
			last=x;
		}
		edg[++es]=(Edge){last,n};
	}
	if(qh<qt){
		puts("NO");
		return 0;
	}
	puts("YES");
	assert(es==n-1);
	for(int i=1;i<n;i++){
		printf("%d %d\n",edg[i].u,edg[i].v);
	}
	return 0;
}
