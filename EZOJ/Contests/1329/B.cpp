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
const int N=100010,INF=0x7f7f7f7f;
int a[N],f[N],lst[N],ls=0,sa[N];
inline int bchop(int v){
	int l=0,r=ls;
	while(l<r){
		int mid=((l+r)>>1)+1;
		if(a[mid]>v){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	return l;
}
inline bool asort(int x,int y){
	return a[x]==a[y]?x<y:a[x]<a[y];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
#endif
	lst[0]=INF;
	int n=ni,l=ni;
	for(int i=1;i<=n;i++){
		sa[i]=i;
		a[i]=ni;
	}
	for(int i=n;i>=1;i--){
		lst[f[i]=bchop(a[i])+1]=a[i];
		if(f[i]>ls){
			ls=f[i];
		}
	}
	if(ls<l){
		puts("impossible");
		return 0;
	}
	sort(sa+1,sa+n+1,asort);
	for(int i=1,j=0;l;l--,i++){
		for(;assert(i<=n),sa[i]<j||f[sa[i]]<l;i++);
		printf("%d ",a[j=sa[i]]);
	}
	putchar('\n');
	return 0;
}
