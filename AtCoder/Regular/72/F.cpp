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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=500010;
struct water{
	double t;
	int v;
	inline friend water operator + (const water &a,const water &b){
		int sum=a.v+b.v;
		if(sum==0)return (water){0,0};
		return (water){a.t*((double)a.v/sum)+b.t*((double)b.v/sum),sum};
	}
	inline void operator += (const water &b){
		*this=*this+b;
	}
	inline void operator -= (const water &b){
		*this+=(water){b.t,-b.v};
	}
}que[N],cur;
int main(){
	int n=ni,v=ni;
	int qh=0,qt=0;
	for(int i=1;i<=n;i++){
		water a=(water){(double)ni,ni};
		for(;cur.v+a.v>v&&cur.v+a.v-que[qh].v>=v;cur-=que[qh++]);
		if(cur.v+a.v>v){
			que[qh].v-=cur.v+a.v-v;
			cur-=(water){que[qh].t,cur.v+a.v-v};
		}
		cur+=a;
		printf("%.10lf\n",cur.t);
		for(;qh<qt&&que[qt-1].t>a.t;a+=que[--qt]);
		que[qt++]=a;
	}
	return 0;
}
