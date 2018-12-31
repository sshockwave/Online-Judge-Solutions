#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long double db;
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
const int N=1010;
struct Pt{
	lint x,y;
	inline int quad()const{
		if(x>0&&y>=0)return 1;
		if(x<=0&&y>0)return 2;
		if(x<0&&y<=0)return 3;
		if(x>=0&&y<0)return 4;
		return 0;
	}
	inline friend bool polarcmp(const Pt &a,const Pt &b){
		const int qa=a.quad(),qb=b.quad();
		return qa!=qb?qa<qb:crs(a,b)>0;
	}
	inline friend db crs(const Pt &a,const Pt &b){return (db)a.x*b.y-(db)a.y*b.x;}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
}pt[N],base;
int lst[N];
inline bool cmp_lst(int a,int b){
	return polarcmp(pt[a]-base,pt[b]-base);
}
inline lint c2(lint n){
	return n*(n-1)/2;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		lst[i]=i;
	}
	lint ans=0;
	for(int x=1;x<=n;x++){
		base=pt[x],sort(lst+1,lst+n+1,cmp_lst);
		int cnt=0;
		for(int i=2,j=2;i<=n&&(pt[lst[i]]-base).quad()<=2;i++){
			for(;j<=n&&crs(pt[lst[i]]-base,pt[lst[j]]-base)>=0;j++){
				++cnt;
			}
			--cnt;
			ans+=c2(cnt)+c2(n-2-cnt);
		}
	}
	ans-=(lint)n*(n-1)*(n-2)*(n-3)/24*3;
	ans*=8;
	ans+=(lint)n*(n-1)*(n-2)*4;
	printf("%lld\n",ans);
	return 0;
}
