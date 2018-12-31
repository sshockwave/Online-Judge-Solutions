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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=500010,INF=0x7f7f7f7f;
int a[N],lst[N];
inline bool cmp_a(int x,int y){
	return a[x]<a[y];
}
int dtsum[N];
inline bool inc(int l,int r){
	return dtsum[r]-dtsum[l]==r-l;
}
inline bool dec(int l,int r){
	return dtsum[r]-dtsum[l]==l-r;
}
inline bool betw(int a,int b,int c){
	return a<=b&&b<=c;
}
inline int Main(){
	const int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni,lst[i]=i;
		dtsum[i]=dtsum[i-1]+(a[i]>a[i-1]?1:-1);
	}
	if(n==0)return 1;
	sort(lst+1,lst+n+1,cmp_a);
	a[0]=INF,a[n+1]=INF;
	int mn_l=-INF,mn_r=-INF;
	int l=1,r=n;
	for(int tt=1;tt<=n;tt++){
		const int i=lst[tt];
		if(!betw(l,i,r))continue;
		bool as_inc=(l==i||a[l-1]>a[l])&&dec(l,i)&&betw(mn_l,a[i],a[r+1]);
		bool as_dec=(r==i||a[r]<a[r+1])&&inc(i,r)&&betw(mn_r,a[i],a[l-1]);
		if(as_inc&&as_dec){
			int ans=0;
			//as_inc
			++ans;
			for(int j=i+1;j<=r&&a[j]<a[i-1];j++){
				++ans;
			}
			//as_dec
			++ans;
			for(int j=i-1;j>=l&&a[j]<a[i+1];j--){
				++ans;
			}
			return ans;
		}else if(as_inc){
			mn_l=a[i];
			a[i]=a[i-1];
			l=i+1;
		}else if(as_dec){
			mn_r=a[i];
			a[i]=a[i+1];
			r=i-1;
		}else return 0;
	}
	return 1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
