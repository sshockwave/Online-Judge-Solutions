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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=210,O=998244353;
template<class T>inline T sqr(T x){return x*x;}
struct Pt{
	int x,y;
}pt[N],pt2[N],base;
inline bool ycmp(const Pt &a,const Pt &b){
	return a.y!=b.y?a.y<b.y:a.x<b.x;
}
inline int cross(const Pt &a,const Pt &b){
	return (a.x-base.x)*(b.y-base.y)-(a.y-base.y)*(b.x-base.x);
}
inline bool polarcmp(const Pt &a,const Pt &b){
	int crs=cross(a,b);
	return crs?crs>0:sqr(a.x-base.x)<sqr(b.x-base.x);
}
int pw2[N];
inline void gmath(int n){
	pw2[0]=1;
	for(int i=1;i<=n;i++){
		pw2[i]=(lint)pw2[i-1]*2%O;
	}
}
int main(){
	int n=ni;
	gmath(n);
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	sort(pt+1,pt+n+1,ycmp);
	lint sum=1;
	for(int i=1;i<=n;i++){
		base=pt[i];
		memcpy(pt2+i+1,pt+i+1,(n-i)*sizeof(Pt));
		sort(pt2+i+1,pt2+n+1,polarcmp);
		for(int j=i+1,k=j;j<=n;j=k){
			for(;k<=n&&cross(pt2[j],pt2[k])==0;k++);
			sum+=pw2[k-j]-1;
		}
		sum++;//single
	}
	printf("%lld\n",((pw2[n]-sum%O)%O+O)%O);
	return 0;
}
