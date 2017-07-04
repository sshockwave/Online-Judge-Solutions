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
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=100010,logN=20;
struct BIT{
	int *c,n;
	inline void build(int _n){
		static int *pool=new int[N*logN];
		c=pool-1,n=_n,pool+=n;
	}
	static inline int lowbit(int x){
		return x&(-x);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=lowbit(x));
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=lowbit(x));
		return ans;
	}
};
int a[N],b[N],t[N];
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	BIT cnt;
	int *id;
	void build(int l,int r,int _t[]){
		lend=l,rend=r,mid=(l+r)>>1;
		cnt.build(r-l+1),id=_t;
		if(lend!=rend){
			static int *pool=new int[N*logN];
			static node n=new SegmentTree[N<<1];
			int *id1=pool,*id2=pool+=mid-l+1;
			id1--,id2--,pool+=r-mid;
			int *pt1=id1,*pt2=id2;
			for(int i=1,n=r-l+1;i<=n;i++){
				*(id[i]<=mid?++pt1:++pt2)=id[i];
				if(i>1){//debug
					assert(t[id[i-1]]>=t[id[i]]);
				}
			}
			(lson=n++)->build(l,mid,id1);
			(rson=n++)->build(mid+1,r,id2);
		}
	}
	inline int find(int x){//find pos of x
		int l=1,r=cnt.n,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(t[id[mid]]<t[x]){
				r=mid-1;
			}else if(t[id[mid]]>t[x]){
				l=mid+1;
			}else if(id[mid]<x){
				l=mid+1;
			}else if(id[mid]>x){
				r=mid-1;
			}else{
				l=r=mid;
			}
		}
		assert(id[l]==x);
		return l;
	}
	inline int cal(int x){//t>=x times cnt
		int l=0,r=cnt.n,mid;
		while(l<r){
			mid=((l+r)>>1)+1;
			if(t[id[mid]]<x){
				r=mid-1;
			}else{
				l=mid;
			}
		}
		return cnt.sum(l);
	}
	void add(int x,int v){
		cnt.add(find(x),v);
		if(lend!=rend){
			(x<=mid?lson:rson)->add(x,v);
		}
	}
	int findlast(int a,int b){//t in [a,b)
		if(cal(a)==cal(b)){
			return -1;
		}
		if(lend==rend){
			return lend;
		}
		int res=rson->findlast(a,b);
		return res==-1?lson->findlast(a,b):res;
	}
	int ask(int l,int v){//in [l,rend] ask all t>=v
		if(l==lend){
			return cal(v);
		}
		if(l<=mid){
			return lson->ask(l,v)+rson->cal(v);
		}else{
			return rson->ask(l,v);
		}
	}
}seg;
struct Event{
	int x,id,op;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.x<b.x;
	}
}eve[N*2];
int id[N];
inline bool idcmp(const int &a,const int &b){
	return t[a]==t[b]?a<b:t[a]>t[b];
}
int work(int a,int b){
	if(a>b){
		if(seg.cal(a)==0){
			return a;
		}
		int x=seg.findlast(b,a);
		if(x==-1){
			return (seg.cal(a)&1)?b:a;
		}
		if(x==seg.rend){
			return a;
		}
		return (seg.ask(x+1,a)&1)?b:a;
	}else{
		int x=seg.findlast(a,b);
		if(x==-1){
			return (seg.cal(b)&1)?b:a;
		}
		if(x==seg.rend){
			return b;
		}
		return (seg.ask(x+1,b)&1)?a:b;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b[i]=ni;
	}
	int m=ni,es=0;
	for(int i=1;i<=m;i++){
		int l=ni,r=ni;
		t[i]=ni,id[i]=i;
		eve[es++]=(Event){l,i,1};
		eve[es++]=(Event){r+1,i,-1};
	}
	sort(eve,eve+es),sort(id+1,id+m+1,idcmp);
	seg.build(1,m,id);
	lint ans=0;
	for(int i=1,j=0;i<=n;i++){
		for(;j<es&&eve[j].x==i;seg.add(eve[j].id,eve[j].op),j++);
		ans+=work(a[i],b[i]);
	}
	printf("%lld\n",ans);
}
