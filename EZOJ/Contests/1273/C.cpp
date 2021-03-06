#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#define assert
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=100010,D=N*2;
int n,mxVal,segroot;
struct Operation{
	int i,d,t;
}op[N];
inline bool opcmp(const Operation &a,const Operation &b){
	return a.t>b.t;
}
inline int cut(int val){
	apmin(val,mxVal);
	apmax(val,0);
	return val;
}
struct Info{
	int high,low,delta;//low<=x<=high will accept delta
	inline void init(){
		assert(delta!=0);
		high=cut(mxVal+delta)-delta;
		low=cut(delta)-delta;
	}
	inline friend int operator + (int a,Info b){
		apmax(a,b.low);
		apmin(a,b.high);
		return a+b.delta;
	}
	inline friend Info operator + (Info a,Info b){
		Info c;
		c.delta=a.delta+b.delta;
		c.high=min(a.high,b.high-a.delta);
		c.low=max(a.low,b.low-a.delta);
		if(c.high<c.low){
			c.high=c.low=0;
			assert(a.low+a.delta+b==a.high+a.delta+b);
			c.delta=a.low+a.delta+b;
		}
		return c;
	}
	inline bool contain(int x){
		return high+delta>=x&&low+delta<=x;
	}
};
struct Segtree{
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int lend[D],rend[D],mid[D],son[D][2],ntop;
	Info info[D];
	Segtree(){
		ntop=1;
	}
	int build(int l=1,int r=n){
		int x=ntop++;
		lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
		if(l==r){
			info[x].delta=op[l].d;
			info[x].init();
		}else{
			lson(x)=build(l,mid[x]);
			rson(x)=build(mid[x]+1,r);
			info[x]=info[lson(x)]+info[rson(x)];
		}
		return x;
	}
	void reset(int x,int p){
		if(lend[x]==rend[x]){
			assert(p==lend[x]);
			info[x]=(Info){mxVal,0,0};
		}else{
			reset(son[x][p>mid[x]],p);
			info[x]=info[lson(x)]+info[rson(x)];
		}
	}
}seg;
inline int cal(int v2){
	Info &F=seg.info[segroot];
	assert(F.contain(v2));
	v2-=F.delta;
	if(v2==F.high){
		return mxVal;
	}
	return v2;
}
int main(){
	n=ni(),mxVal=ni();
	int goal=ni();
	op[0].t=0;
	for(int i=1;i<=n;i++){
		char c;
		while(c=getchar(),c!='+'&&c!='-');
		op[i]=(Operation){i,c=='+'?1:-1,ni()};
	}
	for(int i=n;i>0;i--){
		op[i].t-=op[i-1].t;
	}
	segroot=seg.build();
	sort(op+1,op+n+1,opcmp);
	Info &F=seg.info[segroot];
	if(F.contain(goal)){
		puts("infinity");
		return 0;
	}
	for(int i=1,t;i<=n;){
		for(t=op[i].t;i<=n&&t==op[i].t;i++){
			seg.reset(segroot,op[i].i);
		}
		if(F.contain(goal)){
			printf("%d %d",t-1,cal(goal));
			return 0;
		}
	}
}
