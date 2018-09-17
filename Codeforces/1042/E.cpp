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
const int N=1010,N2=1000010,O=998244353;
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
struct Item{
	int x,y,v;
	inline friend bool operator < (const Item &a,const Item &b){
		return a.v<b.v;
	}
}pt[N2];
int f[N2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
#endif
	int ps=0;
	const int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			pt[++ps]=(Item){i,j,ni};
		}
	}
	sort(pt+1,pt+ps+1);
	lint sumx=0,sumy=0;
	int sumf=0;
	for(int i=1,j=1;i<=ps;i++){
		for(;pt[j].v<pt[i].v;j++){
			sumf=(sumf+f[j]+(lint)pt[j].x*pt[j].x+(lint)pt[j].y*pt[j].y)%O;
			sumx+=pt[j].x;
			sumy+=pt[j].y;
		}
		if(j==1){
			f[i]=0;
		}else{
			lint ans=0;
			ans+=((sumx%O*pt[i].x+sumy%O*pt[i].y)%O*(O-2)+sumf)%O*inv_pow(j-1)%O;
			ans+=((lint)pt[i].x*pt[i].x+(lint)pt[i].y*pt[i].y)%O;
			f[i]=ans%O;
		}
	}
	const int r=ni,c=ni;
	for(int i=1;i<=ps;i++){
		if(pt[i].x==r&&pt[i].y==c){
			printf("%d\n",f[i]);
			break;
		}
	}
	return 0;
}
