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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
int n;
struct Intv{
	int l,r;
	inline int len()const{
		return r-l+1;
	}
};
namespace heap{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		//set
		node lson,rson;
		int rw,rend;
		//upd
		int rdis;
		inline void up(){
			if(rson->rdis>lson->rdis){
				swap(lson,rson);
			}
			rdis=rson->rdis+1;
		}
	}pool[N],Null;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
	}
	node mg(node,node);
	void apmg(node &a,node b){
		a=mg(a,b);
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(u->rend>v->rend)return mg(v,u);
		return apmg(u->rson,v),u->up(),u;
	}
}
heap::node nd[N],rwnd[N];
inline int gauss(const Intv intv[]){
	using heap::mg;
	using heap::apmg;
	using heap::null;
	for(int i=1;i<=n+1;i++){
		nd[i]=null;
	}
	for(int i=1;i<=n;i++){
		heap::node x=rwnd[i]=heap::pool+i;
		*x=*null;
		x->rw=i,x->rend=intv[i].r;
		x->up();
		apmg(nd[intv[i].l],x);
	}
	int ans=1;
	for(int i=1;i<=n;i++){
		if(nd[i]==null)return 0;
		if(nd[i]!=rwnd[i]){
			heap::node a=nd[i],b=rwnd[i];
			assert(a->rw!=b->rw);
			swap(rwnd[a->rw],rwnd[b->rw]);
			swap(a->rw,b->rw);
			ans=O-ans;
		}
		const heap::node x=mg(nd[i]->lson,nd[i]->rson);
		if(x!=null){
			if(x->rend==nd[i]->rend)return 0;
			assert(x->rend>nd[i]->rend);
			apmg(nd[nd[i]->rend+1],x);
		}
	}
	return ans;
}
Intv int_x[N],int_y[N];
inline int Main(){
	n=ni;
	int ans=1;
	for(int i=1;i<=n;i++){
		int_x[i]=(Intv){ni,ni};
		int_y[i]=(Intv){ni,ni};
		ans=(lint)ans*inv_pow((lint)int_x[i].len()*int_y[i].len()%O)%O;
	}
	return (lint)ans*gauss(int_x)%O*gauss(int_y)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
#endif
	heap::init();
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
