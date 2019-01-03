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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=2010;
int a[N],b[N],c[N];
lint calc1(int a1,int a2,int b1,int b2,int c1,int c2){
	int take1=(b1+1)/2/a1;
	int reststep=max(b1-(take1*a1+a1-1),0);
	b2-=reststep;
	int take2=(b2+1)/2/a2;
	return take1*c1+take2*c2;
}
inline int calc1x(int b1,int b2){
	return max(calc1(a[1],a[2],b1,b2,c[1],c[2]),calc1(a[2],a[1],b2,b1,c[2],c[1]));
}
lint calc2(int a1,int a2,int b1,int b2,int c1,int c2){
	int take1=b1/2/a1;
	int reststep=max(b1-(take1*a1+a1-1),0);
	b2-=reststep;
	int take2=(b2+1)/2/a2;
	return take1*c1+take2*c2;
}
inline int calc2x(int b1,int b2){
	return max(calc2(a[1],a[2],b1,b2,c[1],c[2]),calc2(a[2],a[1],b2,b1,c[2],c[1]));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni,b[i]=ni,c[i]=ni;
	}
	if(n==1){
		lint ans=0;
		int tb=b[1]/2;
		int take1=(tb+1)/2/a[1];
		int take2=tb/2/a[1];
		ans=(take1+take2)*c[1];
		printf("%lld\n",ans);
		return 0;
	}
	lint ans=0;
	int B=(b[1]+b[2])/2;
	for(int t=0;t<=b[1];t++){
		if(B-t<=b[2]&&B-(b[1]-t)<=b[2]){
			apmax(ans,calc1x(t,B-t)+calc2x(b[1]-t,B-(b[1]-t)));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
