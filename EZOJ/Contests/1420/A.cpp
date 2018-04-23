#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int>vi;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=300010;
struct Pt{
	int x,y;
}pt[N];
int cnt1[N],cnt2[N];
vi vec[N];
namespace bit{
	inline void add(int c[],int n,int x,int v){
		if(x==0)return;
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int c[],int x){
		int a=0;
		for(;x;a+=c[x],x^=x&-x);
		return a;
	}
	inline int ask(int c[],int l,int r){
		return sum(c,r)-sum(c,l-1);
	}
}
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mx,allmx,*c;
		inline void up(){
			mx=max(lson->mx,rson->mx);
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->mx=0;
		if(l==r){
			x->allmx=cnt2[l]>>1;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->allmx=max(x->lson->allmx,x->rson->allmx);
		}
		x->c=new int[x->allmx]-1;
		mset(x->c+1,0,x->allmx);
		return x;
	}
	void alt(node x,int p,int v1,int v2){
		assert(v1<=x->allmx);
		assert(v2<=x->allmx);
		bit::add(x->c,x->allmx,v1,-1);
		bit::add(x->c,x->allmx,v2,1);
		if(x->l==x->r){
			x->mx=v2;
		}else if(x->l!=x->r){
			alt(p<=x->m?x->lson:x->rson,p,v1,v2);
			x->up();
		}
	}
	int ask_mx(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mx;
		if(r<=x->m)return ask_mx(x->lson,l,r);
		if(l>x->m)return ask_mx(x->rson,l,r);
		return max(ask_mx(x->lson,l,x->m),ask_mx(x->rson,x->m+1,r));
	}
	int ask_cnt(node x,int l,int r,int v){
		if(v>x->allmx)return 0;
		if(x->l==l&&x->r==r)return bit::ask(x->c,v,x->allmx);
		if(r<=x->m)return ask_cnt(x->lson,l,r,v);
		if(l>x->m)return ask_cnt(x->rson,l,r,v);
		return ask_cnt(x->lson,l,x->m,v)+ask_cnt(x->rson,x->m+1,r,v);
	}
}
int *num[N];
inline bool ncmp(int *a,int *b){
	return *a<*b;
}
inline int worknum(int n){
	sort(num+1,num+n+1,ncmp);
	int j=0;
	for(int i=1,v=-1;i<=n;i++){
		*num[i]=v!=*num[i]?v=*num[i],++j:j;
	}
	return j;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ypku.in","r",stdin);
	freopen("ypku.out","w",stdout);
#endif
	int n=ni,q=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	for(int i=1;i<=n;i++){
		num[i]=&pt[i].x;
	}
	int mxx=worknum(n);
	for(int i=1;i<=n;i++){
		num[i]=&pt[i].y;
	}
	int mxy=worknum(n);
	mset(cnt1+1,0,mxx),mset(cnt2+1,0,mxx);
	for(int i=1;i<=n;i++){
		++cnt2[pt[i].x];
		vec[pt[i].y].push_back(pt[i].x);
	}
	seg::node rt=seg::build(1,mxx);
	int ans=1,anscnt=0;
	for(int i=1;i<=mxy;i++){
		vi::iterator it=vec[i].begin(),ti=vec[i].end();
		sort(it,ti);
		int c1=0,c2=vec[i].size();
		for(;it!=ti;++it){
			int x=*it;
			int pv=min(cnt1[x],cnt2[x]);
			++c1,--c2;
			++cnt1[x],--cnt2[x];
			seg::alt(rt,x,pv,min(cnt1[x],cnt2[x]));
			if(min(c1,c2)>=ans){
				int l=x+1,r=*(it+1)-1;
				if(l<=r){
					int nans=min(min(c1,c2),seg::ask_mx(rt,l,r));
					if(nans>ans){
						ans=nans,anscnt=0;
					}
					if(nans==ans){
						anscnt+=seg::ask_cnt(rt,l,r,ans);
					}
				}
			}
		}
	}
	assert(anscnt);
	printf("%d\n",q==1?ans:anscnt);
	return 0;
}
