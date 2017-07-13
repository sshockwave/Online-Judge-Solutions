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
const int N=50010,X=1000010;
namespace BIT{
	int c[X];
	inline int bit(int x){
		return x&(-x);
	}
	inline void add(int x,int v){
		for(;x<X;c[x]+=v,x+=bit(x));
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=bit(x));
		return ans;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
int ans[N];
struct Q{
	int id,x,l,r;
	bool end;
	inline void work(){
		if(end){
			ans[id]+=BIT::ask(l,r);
		}else{
			ans[id]-=BIT::ask(l,r);
		}
	}
	inline friend bool operator < (const Q &a,const Q &b){
		return a.x<b.x;
	}
}q[N<<1];
struct Point{
	int x,y;
	inline friend bool operator < (const Point &a,const Point &b){
		return a.y<b.y;
	}
}pt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("square.in","r",stdin);
	freopen("square.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Point){ni+1,ni+1};
	}
	int tot=ni,qs=0;
	for(int i=1;i<=tot;i++){
		int x1=ni+1,y1=ni+1,x2=ni+1,y2=ni+1;
		q[qs++]=(Q){i,y1-1,x1,x2,0};
		q[qs++]=(Q){i,y2,x1,x2,1};
	}
	sort(pt+1,pt+n+1);
	sort(q,q+qs);
	for(int i=0,j=1;i<qs;i++){
		for(;j<=n&&pt[j].y<=q[i].x;BIT::add(pt[j++].x,1));
		q[i].work();
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
}
