#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=100010;
int a,d;
int act[N];
int t[N],b[N],f[N];
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid;
	lint val;
	node *lson,*rson;
	inline void up(){
		assert(lend!=rend);
		val=max(lson->val,rson->val);
	}
	void build(int l,int r){
		static node *n=new node[N*2];
		lend=l,rend=r,mid=(l+r)>>1;
		if(l==r){
			if(act[l]<=t[0]%d){
				val=(lint)t[0]/d*a;
			}else{
				val=((lint)t[0]/d-1)*a;
			}
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			up();
		}
	}
	inline lint ask(int l,int r){
		assert(lend<=l&&r<=rend);
		assert(l<=r);
		if(lend==l&&rend==r){
			return val;
		}
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return max(lson->ask(l,mid),rson->ask(mid+1,r));
	}
	void set(int x,int v){
		if(lend==rend){
			assert(x==lend);
			val=v;
		}else{
			(x<=mid?lson:rson)->set(x,v);
			up();
		}
	}
}seg;
int main(){
	t[0]=ni;
	int m=ni;
	d=ni,a=ni;
	int n=ni;
	t[n+1]=m;
	act[0]=t[0]%d;
	for(int i=1;i<=n;i++){
		t[i]=ni,b[i]=ni;
		act[i]=t[i]%d;
	}
	act[n+1]=t[n+1]%d;
	sort(act,act+n+2);
	int last=-1,dcnt=0;
	for(int i=0;i<=n+1;i++){
		if(act[i]!=last){
			last=act[i];
			act[++dcnt]=act[i];
		}
	}
	seg.build(1,dcnt);
	lint cur;
	for(int i=1,top=n+1;i<=top;i++){
		int pos=*upper_bound(act,act+dcnt,t[i]%d);
		cur=seg.ask(pos,dcnt);
		if(1<pos){
			apmax(cur,seg.ask(1,pos-1)-a);
		}
		seg.set(pos,cur+b[i]);
	}
	printf("%lld\n",cur+b[i]-(lint)m/d*a);
}