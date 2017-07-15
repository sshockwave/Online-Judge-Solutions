#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <set>
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
const int N=100010;
int rt,n=0,tim=0;
inline int getrt(int x){
	for(rt=0;rt*rt<x;rt++);
	return x;
}
struct Point{
	int id;
	lint x,v;
	inline lint pos(){
		return x+v*tim;
	}
	inline friend bool operator < (Point &a,Point &b){
		lint xa=a.pos(),xb=b.pos();
		return xa==xb?a.v<b.v:xa<xb;
	}
	inline friend int crs(const Point &a,const Point &b){
		assert(a.v!=b.v);
		lint dx=b.x-a.x,dv=a.v-b.v;
		lint ans=dx/dv+(dx%dv!=0);
		assert(ans>=0);
		if(ans>=N){
			return N-1;
		}
		return ans;
	}
	inline friend ostream & operator << (ostream & out,Point a){
		out<<"(x="<<a.pos()<<",v="<<a.v<<",id="<<a.id<<")";
		return out;
	}
}pt[N];
int pos[N];
inline void swp(int a,int b){
	assert(pt[pos[a]].id==a);
	assert(pt[pos[b]].id==b);
	swap(pt[pos[a]],pt[pos[b]]);
	swap(pos[a],pos[b]);
}
struct intcmp{
	inline bool operator () (int a,int b){
		return pos[a]>pos[b];
	}
};
inline void jmp(const set<int,intcmp>&vec){
	for(set<int,intcmp>::iterator it=vec.begin();it!=vec.end();it++){
		int x=*it;
		for(int i=pos[x],ti=min((i/rt+1)*rt-1,n-1);i<ti&&pt[i+1]<pt[i];swp(x,pt[i+1].id),i++){
		}
	}
}
inline int ask(int l,int r,int x){//mx <= x
	l--;
	while(l<r){
		int mid=((l+r)>>1)+1;
		if(pt[mid].pos()>x){
			r=mid-1;
		}else{
			l=mid;
		}
	}
	return l;
}
inline int ask(int x){
	if(n==0){
		return 0;
	}
	int ans=0;
	for(int i=0;i<n;i+=rt){
		ans+=ask(i,min(i+rt-1,n-1),x)-i+1;
	}
	return ans;
}
set<int,intcmp>op[N];
inline void ins(){
	lint tx=ni,tv=ni;
	tx-=tv*tim;
	pt[n]=(Point){n,tx,tv};
	pos[n]=n;
	int o=n/rt,s=o*rt,x=n;
	for(;x>s;x--){
		if(pt[x]<pt[x-1]){
			assert(pt[x].id==n);
			swp(n,pt[x-1].id);
			assert(pt[x-1].id==n);
		}else{
			break;
		}
	}
	for(int i=s;i<x;i++){
		if(pt[i].v>pt[x].v){
			op[crs(pt[i],pt[x])].insert(pt[i].id);
		}
	}
	for(int i=x+1;i<=n;i++){
		if(pt[i].v<pt[x].v){
			op[crs(pt[i],pt[x])].insert(n);
		}
	}
	n++;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flea.in","r",stdin);
	freopen("flea.out","w",stdout);
#endif
	for(int tot=getrt(ni);tot--;){
		switch(ni){
			case 1:
				ins();
				break;
			case 2:
				jmp(op[++tim]);
				break;
			case 3:
				{
					int l=ni,r=ni;
					printf("%d\n",ask(r)-ask(l-1));
					break;
				}
		}
	}
	return 0;
}
