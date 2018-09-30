#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,INF=0x7f7f7f7f;
int a[N<<1];
inline void work(int n,int ans[]){
	multiset<int>st;
	for(int i=1;i<n-1;i++){
		st.insert(2*a[i]+(n-a[i+1]));
	}
	int qh=1,qt=n;
	for(int i=0;i<n;i++){
		ans[i]=n;
		for(;a[qh]-i<0;){
			st.erase(st.find(2*a[qh]+(n-a[qh+1])));
			a[qt++]=a[qh++]+n;
			st.insert(2*a[qt-2]+(n-a[qt-1]));
		}
		apmin(ans[i],a[qt-1]-i);
		apmin(ans[i],*st.begin()-i);
	}
}
int ans1[N],ans2[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.in","r",stdin);
	freopen("i.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<n;i++){
		a[i]=(ni-1+n-i)%n;
	}
	if(n==2){
		if(a[1]){
			puts("1");
			puts("1");
		}else{
			puts("0");
			puts("2");
		}
		return 0;
	}
	sort(a+1,a+n);
	work(n,ans1);
	{
		int j=1;
		for(;j<n&&a[j]==0;j++);
		reverse(a+j,a+n);
		for(int i=j;i<n;i++){
			a[i]=n-a[i];
		}
	}
	work(n,ans2);
	reverse(ans2+1,ans2+n);
	for(int i=0;i<n;i++){
		printf("%d\n",min(i,n-i)+min(ans1[i],ans2[i]));
	}
	return 0;
}
