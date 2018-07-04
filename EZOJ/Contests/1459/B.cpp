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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=210,O=1000000007;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
struct Pt{
	int x,y;
	inline friend int manhatt(const Pt &a,const Pt &b){return cabs(a.x-b.x)+cabs(a.y-b.y);}
}pt[N];
int a[N];
inline void Main(){
	const int r=ni,c=ni,n=ni,d=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]>a[j]+(lint)manhatt(pt[i],pt[j])*d){
				puts("IMPOSSIBLE");
				return;
			}
		}
	}
	lint ans=0;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			lint cur=LINF;
			lint mx=-1;//cout
			for(int k=1;k<=n;k++){
				apmin(cur,a[k]+(lint)manhatt(pt[k],(Pt){i,j})*d);
				apmax(mx,a[k]-(lint)manhatt(pt[k],(Pt){i,j})*d);
			}
			assert(mx<=cur);
			ans+=cur;
		}
	}
	printf("%lld\n",ans%O);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("geographer.in","r",stdin);
	freopen("geographer.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
