#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
typedef long double db;
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
const int N=200010,INF=0x7f7f7f7f;
struct Pt{
	int x,y;
	inline lint d2()const{return sqr<lint>(x)+sqr<lint>(y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint dot(const Pt &a,const Pt &b){return (lint)a.x*b.x+(lint)a.y*b.y;}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
	inline friend ostream & operator << (ostream & out,const Pt &b){
		out<<"("<<b.x<<","<<b.y<<")";
		return out;
	}
	inline lint eval(lint p)const{
		return p*x+y;
	}
};
Pt stk1[N],stk2[N];
inline bool turn_left(Pt a,Pt b,Pt c){
	return crs(b-a,c-a)>0;
}
inline bool turn_right(Pt a,Pt b,Pt c){
	return crs(b-a,c-a)<0;
}
inline db itsect(Pt a,Pt b){
	assert(a.x!=b.x);
	return -(db)(a.y-b.y)/(a.x-b.x);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	int ss1=0,ss2=0;
	for(int i=1;i<=n;i++){
		{
			const Pt p={i,ni};
			for(;ss1>=2&&!turn_right(stk1[ss1-2],stk1[ss1-1],p);ss1--);
			stk1[ss1++]=p;
		}
		{
			const Pt p={i,ni};
			for(;ss2>=2&&!turn_left(stk2[ss2-2],stk2[ss2-1],p);ss2--);
			stk2[ss2++]=p;
		}
	}
	int st=-INF;
	lint ans=0;
	for(int i=0,j=ss2-1;i<ss1||j>=0;){
		const Pt &a=stk1[i],&b=stk2[j];
		int ed1=i+1<ss1?floor(itsect(a,stk1[i+1])):INF;
		int ed2=j-1>=0?floor(itsect(b,stk2[j-1])):INF;
		int ed=min(ed1,ed2);
		if(a.x<b.x){
			apmax(st,ceil(itsect(a,b)));
		}else if(a.x>b.x){
			apmin(ed,floor(itsect(a,b)));
		}
		if(st<=ed){
			ans+=(lint)(ed-st+1)*(b.eval(st)-a.eval(st)+1+b.eval(ed)-a.eval(ed)+1)/2;
		}
		ed=min(ed1,ed2);
		i+=ed1==ed;
		j-=ed2==ed;
		st=ed+1;
	}
	printf("%lld\n",ans);
	return 0;
}
