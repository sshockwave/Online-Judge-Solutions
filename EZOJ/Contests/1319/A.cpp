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
const int N=200010;
int n;
namespace B{
	int c[N];
#define lowbit(x) (x&(-x))
	inline void init(int n){
		memset(c+1,0,n<<2);
	}
	inline void set(int x){
		for(;x<=n;c[x]++,x+=lowbit(x));
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=lowbit(x));
		return ans;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	int sum;
	void build(int l,int r){
		static node n=new SegmentTree[N*2];
		lend=l,rend=r,mid=(l+r)>>1;
		sum=0;
		if(l!=r){
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	void set(int x){
		sum++;
		if(lend!=rend){
			(x<=mid?lson:rson)->set(x);
		}
	}
	int find(int x){//rank
		if(lend==rend){
			assert(x==1);
			assert(sum);
			return lend;
		}else{
			return x<=lson->sum?lson->find(x):rson->find(x-lson->sum);
		}
	}
}seg;
int a[N],b[N];
int ls[N],mp[N],cnt[N];
inline bool lscmp(const int &x,const int &y){
	return a[x]==a[y]?x<y:a[x]<a[y];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fable.in","r",stdin);
	freopen("fable.out","w",stdout);
#endif
	n=ni;
	int k=ni;
	for(int i=1;i<=n;i++){
		a[ls[i]=i]=ni;
	}
	sort(ls+1,ls+n+1,lscmp);
	for(int i=1;i<=n;i++){
		mp[i]=a[ls[i]];
		a[ls[i]]=i;
	}
	B::init(n);
	for(int i=1;i<=n;i++){
		cnt[i]=B::ask(a[i],n);
		B::set(a[i]);
	}
	seg.build(1,n);
	for(int i=0;i<k;i++){
		b[n-i]=n-i;
		seg.set(ls[n-i]);
	}
	for(int i=n-k;i>=1;i--){
		int x=ls[i];
		seg.set(x);
		if(cnt[x]>=k){
			b[x-k]=i;
		}else{
			b[seg.find(k+1)-k]=i;
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",mp[b[i]]);
	}
}
