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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(b<a){
		a=b;
	}
}
const int N=40010;
int n,a[N],mx[N];
inline lint sqr(lint x){
	return x*x;
}
inline void inputa(int n){
	int x=ni,y=ni,z=ni,P=ni;
	a[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=a[i-1]+(sqr(i-x)+sqr(i-y)+sqr(i-z))%P;
	}
}
inline void inputk(int n){
	mx[1]=ni,mx[2]=ni;
	int x=ni,y=ni,z=ni,P=ni;
	for(int i=3;i<=n;i++){
		mx[i]=(x*mx[i-1]+y*mx[i-2]+z)%P;
	}
}
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	int f,g,df,dg;//max f,min g
	inline void up(){
		assert(lson&&rson);
		f=max(lson->f,rson->f);
		g=min(lson->g,rson->g);
	}
	inline void down(){
		assert(lson&&rson);
		if(df){
			lson->f+=df,lson->df+=df;
			rson->f+=df,rson->df+=df;
			df=0;
		}
		if(dg){
			lson->g+=dg,lson->dg+=dg;
			rson->g+=dg,rson->dg+=dg;
			dg=0;
		}
	}
	void build(int l,int r){
		static node n=new SegmentTree[N*2];
		lend=l,rend=r,mid=(l+r)>>1;
		df=dg=0;
		if(l==r){
			f=g=a[l];
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			up();
		}
	}
	int maxf(int l,int r){
		if(lend==l&&rend==r){
			return f;
		}
		down();
		if(r<=mid){
			return lson->maxf(l,r);
		}
		if(l>mid){
			return rson->maxf(l,r);
		}
		return max(lson->maxf(l,mid),rson->maxf(mid+1,r));
	}
	int ming(int l,int r){
		if(lend==l&&rend==r){
			return g;
		}
		down();
		if(r<=mid){
			return lson->ming(l,r);
		}
		if(l>mid){
			return rson->ming(l,r);
		}
		return min(lson->ming(l,mid),rson->ming(mid+1,r));
	}
	void addf(int l,int r,int d){
		if(lend==l&&rend==r){
			f+=d,df+=d;
			return;
		}
		down();
		if(r<=mid){
			lson->addf(l,r,d);
		}else if(l>mid){
			rson->addf(l,r,d);
		}else{
			lson->addf(l,mid,d);
			rson->addf(mid+1,r,d);
		}
		up();
	}
	void addg(int l,int r,int d){
		if(lend==l&&rend==r){
			g+=d,dg+=d;
			return;
		}
		down();
		if(r<=mid){
			lson->addg(l,r,d);
		}else if(l>mid){
			rson->addg(l,r,d);
		}else{
			lson->addg(l,mid,d);
			rson->addg(mid+1,r,d);
		}
		up();
	}
}seg;
int f[N],g[N];
inline int work(int mx){
	int l=ni,r=ni;
	int t=seg.ming(r,n);
	if(l>1){
		t-=max(seg.maxf(1,l-1),0);
	}
	assert(t>=0);
	apmin(t,mx);
	seg.addf(l,n,-t);
	seg.addg(r,n,-t);
	return t;
}
int main(){
	inputa(n=ni);
	int tot=ni;
	inputk(tot);
	seg.build(1,n);
	for(int i=1;i<=tot;i++){
		printf("%d\n",work(mx[i]));
	}
}
