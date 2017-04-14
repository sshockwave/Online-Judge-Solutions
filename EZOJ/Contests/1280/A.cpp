#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=300010,INF=0x7f7f7f7f;
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid,mn,mn2,mnc,mnc2,delta;
	node *lson,*rson;
	inline void up(){
		assert(lend!=rend);
		mn=lson->mn,mn2=lson->mn2,mnc=lson->mnc,mnc2=lson->mnc2;
		if(rson->mn<mn){
			mn2=mn,mnc2=mnc;
			mn=rson->mn,mnc=rson->mnc;
		}else if(rson->mn==mn){
			mnc+=rson->mnc;
		}else if(rson->mn<mn2){
			mn2=rson->mn,mnc2=rson->mnc;
		}else if(rson->mn==mn2){
			mnc2+=rson->mnc;
		}
		if(rson->mn2<mn2){
			mn2=rson->mn2,mnc2=rson->mnc2;
		}else if(rson->mn2==mn2){
			mnc2+=rson->mnc2;
		}
	}
	inline void down(){
		if(delta){
			lson->add(lend,mid,delta);
			rson->add(mid+1,rend,delta);
			delta=0;
		}
	}
	void build(int l,int r){
		static node *n=new node[N*2];
		lend=l,rend=r,mid=(l+r)>>1;
		delta=0,mn=mn2=INF,mnc=mnc2=1;
		if(l!=r){
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			up();
		}
	}
	void set(int x,int v){
		assert(lend<=x&&x<=rend);
		if(lend==rend){
			mn=v;
			delta=0;
		}else{
			down();
			(x<=mid?lson:rson)->set(x,v);
			up();
		}
	}
	void add(int l,int r,int v){
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			delta+=v,mn+=v,mn2+=v;
			return;
		}
		down();
		if(r<=mid){
			lson->add(l,r,v);
		}else if(l>mid){
			rson->add(l,r,v);
		}else{
			lson->add(l,mid,v);
			rson->add(mid+1,r,v);
		}
		up();
	}
}seg;
inline int ask(){
	int ans=0;
	if(seg.mn<=2){
		ans+=seg.mnc;
		if(seg.mn2<=2){
			ans+=seg.mnc2;
		}
	}
	return ans;
}
int perm[N],pos[N];
int main(){
	int n=ni();
	if(n==1){
		puts("0");
		return 0;
	}
	memset(perm,0,sizeof(perm));
	memset(pos,0,sizeof(pos));
	for(int i=1;i<=n;i++){
		pos[perm[i]=ni()]=i;
	}
	lint ans=0;
	seg.build(1,n);
	for(int i=n;i>=1;i--){
		seg.set(i,0);
		int p1=perm[pos[i]-1],p2=perm[pos[i]+1];
		if(p1>p2){
			swap(p1,p2);
		}
		if(p1==0){
			assert(p2!=0);
			if(p2<i){
				seg.add(i,n,1);
			}else{
				seg.add(i,p2-1,1);
			}
		}else if(p1<i){
			if(p2<i){
				seg.add(i,n,1);
			}else{
				seg.add(i,p2-1,1);
			}
		}else{
			seg.add(i,p1-1,1);
			seg.add(p2,n,-1);
		}
		ans+=ask();
	}
	printf("%d\n",ans-n);
}
