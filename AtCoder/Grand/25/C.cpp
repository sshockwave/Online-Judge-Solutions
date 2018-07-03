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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010;
int intvl[N],intvr[N];
int lst1[N],lst2[N];
template<int sat[]>inline bool sat_cmp(int a,int b){
	return sat[a]<sat[b];
}
bool vis[N];
inline lint walk(int n,bool r){
	int x=0;
	lint ans=0;
	int i=n,j=1;
	mset(vis+1,0,n);
	for(int tt=n;tt--;r^=1){
		int p;
		if(r){
			for(;vis[lst1[i]];i--);
			p=lst1[i];
		}else{
			for(;vis[lst2[j]];j++);
			p=lst2[j];
		}
		vis[p]=true;
		if(x<intvl[p]){
			ans+=intvl[p]-x;
			x=intvl[p];
		}else if(x>intvr[p]){
			ans+=x-intvr[p];
			x=intvr[p];
		}
	}
	if(x>=0){
		ans+=x;
	}else{
		ans+=0-x;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("intv.in","r",stdin);
	freopen("intv.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		intvl[i]=ni,intvr[i]=ni;
		lst1[i]=lst2[i]=i;
	}
	sort(lst1+1,lst1+n+1,sat_cmp<intvl>);
	sort(lst2+1,lst2+n+1,sat_cmp<intvr>);
	printf("%lld\n",max(walk(n,0),walk(n,1)));
	return 0;
}
