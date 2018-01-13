#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef double db;
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
const int N=310;
const db EPS=1e-8;
inline int sgn(db x){
	return x>EPS?1:x<EPS?-1:0;
}
struct Pt{
	int x,y;
	inline db d2()const{
		return x*x+y*y;
	}
	inline friend Pt operator + (const Pt &a,const Pt &b){
		return (Pt){a.x+b.x,a.y+b.y};
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){
		return (Pt){a.x-b.x,a.y-b.y};
	}
	inline friend lint crs(const Pt &a,const Pt &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
	inline friend bool polarcmp(const Pt &a,const Pt &b){
		assert(a.x>0&&b.x>0);
		return crs(a,b)>0;
	}
}pt[N];
struct Vec{
	Pt x,d;
	inline friend bool operator < (const Vec &a,const Vec &b){
		return polarcmp(a.d,b.d);
	}
	inline db lam(const Vec &b){
		return (db)((lint)(x.y-b.x.y)*b.d.x-(lint)(x.x-b.x.x)*b.d.y)/((lint)d.x*b.d.y-(lint)d.y*b.d.x);
	}
	inline db pval(db p){
		return x.y+(db)d.y/d.x*(p-x.x);
	}
}vec[N],que[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		pt[i].x=ni;
	}
	for(int i=1;i<=n;i++){
		pt[i].y=ni;
	}
	for(int i=1;i<n;i++){
		vec[i]=(Vec){pt[i],pt[i+1]-pt[i]};
	}
	sort(vec+1,vec+n);
	int qh=0,qt=0;
	for(int i=1;i<n;i++){
		for(;qt-qh>=2&&que[qt-2].lam(vec[i])<que[qt-2].lam(que[qt-1]);qt--);
		if(qt>qh&&crs(que[qt-1].d,vec[i].d)==0)continue;
		que[qt++]=vec[i];
	}
	assert(qh<qt);
	db ans=1/0.0;
	for(int i=1,j=qh;i<n;i++){//[i,i+1]
		apmin(ans,que[j].pval(pt[i].x)-pt[i].y);
		for(;j+1<qt;j++){
			db lam=que[j].lam(que[j+1]);
			db x=que[j].x.x+que[j].d.x*lam;
			if(x>pt[i+1].x)break;
			db y=que[j].x.y+que[j].d.y*lam;
			apmin(ans,y-((Vec){pt[i],pt[i+1]-pt[i]}).pval(x));
		}
		apmin(ans,que[j].pval(pt[i+1].x)-pt[i+1].y);
	}
	printf("%.3lf\n",ans);
	return 0;
}
