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
const int N=100010,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
struct Pt{
	int x,y;
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
}pt[N];
int c[N];
namespace hull{
	int idx[N],lst[N],stk[N];
	inline bool lst_cmp(const int a,const int b){
		return pt[a].x!=pt[b].x?pt[a].x<pt[b].x:pt[a].y<pt[b].y;
	}
	inline int hull_half(const int n){
		int ss=0;
		for(int i=1;i<=n;i++){
			const int x=lst[i];
			for(;ss>=2&&crs(pt[stk[ss-1]]-pt[stk[ss-2]],pt[x]-pt[stk[ss-2]])>=0;ss--);
			stk[ss++]=x;
		}
		return ss;
	}
	inline int main(int n){
		for(int i=1;i<=n;i++){
			lst[i]=i;
		}
		sort(lst+1,lst+n+1,lst_cmp);
		int m=hull_half(n);
		mcpy(idx+1,stk,m);
		reverse(lst+1,lst+n+1);
		int m2=hull_half(n);
		assert(stk[0]==idx[m]);
		assert(stk[m2-1]==idx[1]);
		mcpy(idx+m+1,stk+1,m2-2);
		m+=m2-2;
		return m;
	}
}
inline void getnxt(int &x,int n){
	x=x<n?x+1:1;
}
inline int work(int n){
	static int val[N];
	int cnta=0,cntb=0;
	using hull::idx;
	for(int i=1;i<=n;i++){
		val[i]=c[idx[i]];
		if(val[i]==1){
			++cnta;
		}else if(val[i]==2){
			++cntb;
		}
	}
	if(cnta==0&&cntb==0){
		return ((lint)(n-1)*n+2)%O;
	}
	if(cnta==0||cntb==0){
		int j=1;
		for(;val[j]==0;j++);
		int ans=0;
		for(int i=j;;i=j){
			int cnt=0;
			for(getnxt(j,n);val[j]==0;getnxt(j,n),++cnt);
			ans=(ans+(lint)cnt*(cnt+1))%O;
			if(j<=i)break;
		}
		return ((lint)ans*inv_pow(2)+1)%O;
	}
	int j=1;
	for(;val[j]==0;j++);
	int ans=1,scnt=0;
	for(int i=j;;i=j){
		int cnt=0;
		for(getnxt(j,n);val[j]==0;getnxt(j,n),++cnt);
		if(val[i]!=val[j]){
			ans=(lint)ans*(cnt+1)%O,++scnt;
			if(scnt>2)return 0;
		}
		assert(i!=j);
		if(j<=i)break;
	}
	assert(scnt==2);
	return ans;
}
inline int Main(){
	const int n=ni;
	int cnta=0,cntb=0;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		c[i]=ni;
		if(c[i]==1){
			++cnta;
		}else if(c[i]==2){
			++cntb;
		}
	}
	const int m=hull::main(n);
	int cntt=n-cnta-cntb-m;
	for(int i=1;i<=m;i++){
		cntt+=c[hull::idx[i]]!=0;
	}
	return ((lint)work(m)*fpow(2,cntt)+O-(cnta==0)-(cntb==0))%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
