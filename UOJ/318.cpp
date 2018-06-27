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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,INF=0x7f7f7f7f;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,dt;
		inline void addv(const int v){
			mn+=v,dt+=v;
		}
		inline void up(){
			assert(dt==0);
			mn=min(lson->mn,rson->mn);
		}
		inline void dn(){
			if(dt){
				lson->addv(dt);
				rson->addv(dt);
				dt=0;
			}
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->mn=x->dt=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	int find_nxt(node x,int l,int r){//biggest [l,r]>0
		assert(x->l<=l&&l<=r&&r<=x->r);
		if(x->mn>0)return l;
		if(x->l==x->r)return r+1;
		x->dn();
		if(r<=x->m)return find_nxt(x->lson,l,r);
		int t=find_nxt(x->rson,max(x->m+1,l),r);
		return t==x->m+1&&l<=x->m?find_nxt(x->lson,l,x->m):t;
	}
	int ask(node x,int l,int r){//ask min
		if(l>r)return INF;
		if(x->l==l&&x->r==r)return x->mn;
		x->dn();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return min(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r));
	}
	void add(node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->addv(v);
		x->dn();
		if(r<=x->m){
			add(x->lson,l,r,v);
		}else if(l>x->m){
			add(x->rson,l,r,v);
		}else{
			add(x->lson,l,x->m,v);
			add(x->rson,x->m+1,r,v);
		}
		x->up();
	}
}
struct Item{
	int d,cur,rest,x,v;
	inline friend bool operator < (const Item &a,const Item &b){
		return a.v>b.v;
	}
}lst[N<<1];
lint ans[N];
const seg::node rt=seg::build(1,N-1);
int main(){
#ifndef ONLINE_JUDGE
	freopen("vegetable.in","r",stdin);
	freopen("vegetable.out","w",stdout);
#endif
	int ls=0;
	int tot1=ni;
	const int mx=ni;
	int tot2=ni;
	for(;tot1--;){
		const int a=ni,s=ni,c=ni,x=ni;
		const int lastday=x?min((c+x-1)/x,N-1):(N-1);
		if(x){
			lst[++ls]=(Item){0,0,c-1,x,a};
		}else{
			lst[++ls]=(Item){lastday,c-1,0,0,a};
		}
		lst[++ls]=(Item){lastday,1,0,x,a+s};
	}
	sort(lst+1,lst+ls+1);
	memset(ans,0,sizeof(ans));
	int d=1,r=mx;
	for(int i=1;i<=ls;i++){
		Item &it=lst[i];
		for(;;){
			if(r==0){
				++d,r=mx;
				if(d==N)break;
			}
			if(it.cur==0){
				++it.d,it.rest-=it.cur=min(it.rest,it.x);
				if(it.cur==0)break;
			}
			if(it.d<d){
				int p=seg::find_nxt(rt,it.d,d-1);
				if(it.d<p){
					if(it.rest<(lint)(p-it.d-1)*it.x)break;
					it.rest-=(p-it.d-1)*it.x;
					it.d=p,it.rest-=it.cur=min(it.rest,it.x);
					if(it.cur==0)break;
				}
			}
			int dt=r;
			apmin(dt,seg::ask(rt,it.d,d-1));
			apmin(dt,it.cur);
			assert(dt);
			ans[d]+=(lint)dt*it.v;
			r-=dt,it.cur-=dt;
			if(it.d<d){
				seg::add(rt,it.d,d-1,-dt);
			}else if(it.d>d){
				seg::add(rt,d,it.d-1,dt);
			}
		}
		if(d==N)break;
	}
	for(int i=1;i<N;i++){
		ans[i]+=ans[i-1];
	}
	for(;tot2--;printf("%lld\n",ans[ni]));
	return 0;
}
