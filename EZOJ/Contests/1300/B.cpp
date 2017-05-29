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
int k,m,d,a,n,t[N],b[N];
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
			if(l<=t[0]){
				val=(lint)k/d*a;
			}else{
				val=((lint)k/d-1)*a;
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
	void set(int x,lint v){
		if(lend==rend){
			assert(x==lend);
			val=v;
		}else{
			(x<=mid?lson:rson)->set(x,v);
			up();
		}
	}
}seg;
int r[N];
inline bool rcmp(const int &a,const int &b){
	return t[a]<t[b];
}
int main(){
	k=ni,m=ni,d=ni,a=ni,n=ni+1;
	b[0]=b[n]=0;
	t[0]=k%d,t[n]=m%d;
	for(int i=1;i<n;i++){
		t[i]=ni%d,b[i]=ni,r[i]=i;
	}
	r[0]=0,r[n]=n;
	sort(r,r+n+1,rcmp);
	int last=-1,top=0;
	for(int i=0;i<=n;i++){
		if(last!=t[r[i]]){
			last=t[r[i]];
			top++;
		}
		t[r[i]]=top;
	}
	assert(top>=1);
	seg.build(1,top);
	lint cur;
	for(int i=1;i<=n;i++){
		cur=seg.ask(t[i],top);
		if(t[i]!=1){
			apmax(cur,seg.ask(1,t[i]-1)-a);
		}
		seg.set(t[i],cur+b[i]);
	}
	printf("%lld\n",cur-(lint)m/d*a);
}
