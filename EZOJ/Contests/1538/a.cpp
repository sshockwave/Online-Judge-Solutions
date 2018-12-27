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
const int N=200010;
const db EPS=1e-7;
inline bool isint(db x){
	return cabs(x-round(x))<=EPS;
}
inline db cfloor(db x){
	return floor(x+EPS);
}
inline db cceil(db x){
	return ceil(x-EPS);
}
inline lint ex_euclid(lint a,lint b,lint c,lint n){
	lint ans=0;
	ans+=(lint)a/c*n*(n+1)/2,a%=c;
	ans+=(lint)b/c*n,b%=c;
	if(a==0)return ans;
	lint m=(a*n+b)/c;
	ans+=m*n-ex_euclid(c,-b-1,a,m);
	return ans;
}
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
};
struct Line{
	Pt a,vec;
	inline lint getval(int l,int r){
		lint ans=0;
		ans+=ex_euclid(vec.y,-(lint)a.x*vec.y,vec.x,r);
		if(l){
			ans-=ex_euclid(vec.y,-(lint)a.x*vec.y,vec.x,l-1);
		}
		ans+=(lint)a.y*(r-l+1);
		return ans;
	}
	inline friend ostream & operator << (ostream & out,const Line &b){
		out<<"["<<b.a<<">>"<<b.vec<<"]";
		return out;
	}
}segm[N<<1],que[N<<1];
inline db getsect(Line a,Line b){
	Pt u=b.a-a.a;
	db v1=(db)dot(u,a.vec)/a.vec.d2();
	db v2=(db)crs(a.vec,u)/a.vec.d2()/((db)crs(b.vec,a.vec)/dot(b.vec,a.vec));
	return v1+v2;
}
inline void itsect(Line a,Line b,db &x,db &y){
	db r=getsect(a,b);
	x=a.a.x+a.vec.x*r;
	y=a.a.y+a.vec.y*r;
}
inline bool hid_down(Line a,Line b,Line c){
	return getsect(b,a)>=getsect(b,c);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		const int l=ni,r=ni;
		segm[i]=(Line){(Pt){l,l},(Pt){i-1,i-2}};
		segm[i+n]=(Line){(Pt){r,r},(Pt){-(i-1),-(i-2)}};
	}
	int qh=0,qt=0;
	for(int i=1;i<=n*2;i++){
		for(;qt-qh>=2&&hid_down(que[qt-2],que[qt-1],segm[i]);qt--);
		que[qt++]=segm[i];
	}
	for(;qt-qh>3;){
		if(hid_down(que[qt-1],que[qh],que[qh+1])){
			qh++;
		}else if(hid_down(que[qt-2],que[qt-1],que[qh])){
			qt--;
		}else break;
	}
	lint ans=0;
	for(int i=qh;i<qt;i++){
		const int pr=i>qh?i-1:(qt-1),nx=i+1<qt?i+1:qh;
		db p1x,p1y,p2x,p2y;
		itsect(que[i],que[pr],p1x,p1y);
		itsect(que[i],que[nx],p2x,p2y);
		const Pt &vec=que[i].vec;
		if(i==qh){
			if(vec.x==0){
				ans+=cfloor(p1y)-cceil(p2y)+1;
			}else if(isint(p1x)&&isint(p1y)){
				ans+=1;
			}
		}
		if(vec.x>0){
			int x1=cceil(p1x)+isint(p1x),x2=cfloor(p2x);
			if(x1>x2)continue;
			ans-=que[i].getval(x1,x2);
			x1=cceil((db)(x1-que[i].a.x)/que[i].vec.x);
			x2=cceil((db)(x2-que[i].a.x)/que[i].vec.x);
			ans+=x2-x1+1;
		}else if(vec.x<0){
			int x1=cceil(p2x)+isint(p2x),x2=cfloor(p1x);
			if(x1>x2)continue;
			ans+=que[i].getval(x1,x2);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
