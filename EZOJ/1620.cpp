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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T>inline void apmin(T &a,const T &b){
	if(b<a){
		a=b;
	}
}
const int N=100010,D=2;
inline lint sqr(int x){
	return (lint)x*x;
}
int d=0;
struct Point{
	int x[D];
	inline friend Point operator - (const Point &a,const Point &b){
		return (Point){a.x[0]-b.x[0],a.x[1]-b.x[1]};
	}
	inline friend bool operator < (const Point &a,const Point &b){
		return a.x[d]<b.x[d];
	}
	inline lint d2(){
		return sqr(x[0])+sqr(x[1]);
	}
}pt[N],qpt;
struct Result{
	int x;
	lint val;
	Result(int _x):x(_x),val((qpt-pt[x]).d2()){}
	inline friend bool operator < (const Result &a,const Result &b){
		return a.val<b.val;
	}
};
namespace T{
#define lson(x) son[x][0]
#define rson(x) son[x][1]
	int son[N][2],dim[N],root;
	inline void init(){
		memset(son,0,sizeof(son));
	}
	int build(int l,int r,int t){
		d=t;
		int mid=(l+r)>>1;
		dim[mid]=t;
		nth_element(pt+l,pt+mid,pt+r+1);
		if(l<mid){
			lson(mid)=build(l,mid-1,t^1);
		}
		if(mid<r){
			rson(mid)=build(mid+1,r,t^1);
		}
		return mid;
	}
	Result ask(int x){
		d=dim[x];
		bool d=qpt<pt[x];
		Result ans(x);
		if(son[x][d]){
			apmin(ans,ask(son[x][d]));
		}
		if(son[x][!d]&&ans.val>sqr(pt[x].x[dim[x]]-qpt.x[dim[x]])){
			apmin(ans,ask(son[x][!d]));
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("plane.in","r",stdin);
	freopen("plane.out","w",stdout);
#endif
	T::init();
	int n=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Point){ni,ni};
	}
	T::root=T::build(1,n,0);
	for(int i=1;i<=n;i++){
		qpt=pt[i];
		printf("%d\n",T::ask(T::root).x);
	}
}
