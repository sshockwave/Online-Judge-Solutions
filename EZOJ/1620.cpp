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
int d;
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
}pt[N];
int id[N],qid;
struct Result{
	int x;
	lint val;
	Result(int _x):x(_x),val((pt[qid]-pt[x]).d2()){}
	inline friend bool operator < (const Result &a,const Result &b){
		return a.val==b.val?a.x<b.x:a.val<b.val;
	}
};
namespace T{
#define lson(x) son[x][0]
#define rson(x) son[x][1]
	int son[N][2],dim[N];
	inline void init(){
		memset(son,0,sizeof(son));
	}
	inline bool idcmp(int a,int b){
		return pt[a]<pt[b];
	}
	int build(int l,int r,int _d){
		int mid=(l+r)>>1;
		d=_d;
		nth_element(id+l,id+mid,id+r+1,idcmp);
		int x=id[mid];
		dim[x]=_d;
		if(l<mid){
			lson(x)=build(l,mid-1,_d^1);
		}
		if(mid<r){
			rson(x)=build(mid+1,r,_d^1);
		}
		return x;
	}
	Result ans(0);
	void ask(int x){
		if(x!=qid){
			apmin(ans,Result(x));
		}
		bool d=pt[qid].x[dim[x]]>pt[x].x[dim[x]];
		if(son[x][d]){
			ask(son[x][d]);
		}
		if(son[x][!d]&&ans.val>=sqr(pt[x].x[dim[x]]-pt[qid].x[dim[x]])){
			ask(son[x][!d]);
		}
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
		id[i]=i;
	}
	int root=T::build(1,n,0);
	for(int i=1;i<=n;i++){
		qid=i;
		T::ans.val=0x7f7f7f7f7f7f7f7fll;
		T::ask(root);
		printf("%d\n",T::ans.x);
	}
}
