#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <cmath>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T>inline T sqr(T x){
	return x*x;
}
const int N=100010,MOD=1000000007;
const double EPS=1e-5;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
struct Int{
	int l,r;
	inline bool empty(){
		return l>r;
	}
	inline friend bool operator < (const Int &a,const Int &b){
		return a.l!=b.l?a.l<b.l:a.r<b.r;
	}
};
struct Pt{
	int x,y;
	inline friend Pt operator - (const Pt &a,const Pt &b){
		return (Pt){a.x-b.x,a.y-b.y};
	}
	inline friend int dot(const Pt &a,const Pt &b){
		return a.x*b.x+a.y*b.y;
	}
	inline friend int crs(const Pt &a,const Pt &b){
		return a.x*b.y-a.y*b.x;
	}
	inline int d2(){
		return sqr(x)+sqr(y);
	}
}pt[N];
inline double dist(int u,int v){
	return sqrt((pt[u]-pt[v]).d2());
}
struct Circle{
	int a,b,c;
	Circle(set<int>s){
		a=b=c=0;
		int *p=&a;
		for(;p<=(&c)&&!s.empty();(*p++)=*s.begin(),s.erase(s.begin()));
		if(c&&crs(pt[b]-pt[c],pt[a]-pt[c])>0){
			swap(b,c);
		}
	}
	inline double R(){
		if(b==0){
			return 0;
		}
		if(c==0){
			return dist(a,b)/2;
		}
		return dist(a,b)/(sqrt(1-sqr(dot(pt[a]-pt[c],pt[b]-pt[c])/(dist(a,c)*dist(b,c))))*2);
	}
	inline bool has(int d){
		if(b==0){
			return a==d;
		}
		if(c==0){
			return dot(pt[d]-pt[a],pt[d]-pt[b])<=0;
		}
		double t=R()*(dot(pt[b]-pt[a],pt[c]-pt[a])/(dist(a,b)*dist(a,c)))/dist(b,c);
		double cx=-(pt[c].y-pt[b].y)*t+(pt[b].x+pt[c].x)/2.0;
		double cy=(pt[c].x-pt[b].x)*t+(pt[b].y+pt[c].y)/2.0;
		return sqr(pt[d].x-cx)+sqr(pt[d].y-cy)<=sqr(R());
	}
};
Circle solve(Int S,set<int>Q){
	Circle ans(Q);
	if(S.empty()){
		return ans;
	}
	Int P=(Int){S.l,S.l};
	for(int &i=P.r;i<=S.r;i++){
		if(!ans.has(i)){
			assert(Q.find(i)==Q.end());
			Q.insert(i);
			ans=solve((Int){S.l,i-1},Q);
			Q.erase(i);
		}
	}
	return ans;
}
set<Int>ints;
int r[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	int ans=1;
	for(int i=1,tot=ni;i<=tot;i++){
		Int S=(Int){ni,ni};
		if(ans==0){
			printf("%lld\n",(lint)S.l*S.r);
			continue;
		}
		r[i]=solve(S,set<int>()).R()+EPS;
		for(int j=1;j<i;j++){
			apmul(ans,sub(r[i],r[j]));
		}
		printf("%lld\n",ans+(lint)S.l*S.r);
	}
	return 0;
}
