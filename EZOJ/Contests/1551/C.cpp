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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(a));}
const int N=500010;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int m,r;
		int orsum;
		int ans;
		inline void up(){
			orsum=lson->orsum|rson->orsum;
			if(lson->orsum&m){
				ans=m;
			}else{
				ans=max(lson->ans,rson->ans);
			}
		}
	}pool[N];
	node build(int r){
		static node n=pool;
		const node x=n++;
		x->r=r;
		if(r==1){
			x->m=0;
			x->orsum=0;
			x->ans=0;
		}else{
			for(int &j=x->m=1;(j<<1)<x->r;j<<=1);
			x->lson=build(x->m);
			x->rson=build(r-x->m);
			x->up();
		}
		return x;
	}
	void alt_set(node x,int p,int v){
		if(x->r==1){
			x->orsum=v;
		}else{
			if(p<x->m){
				alt_set(x->lson,p,v);
			}else{
				alt_set(x->rson,p^x->m,v);
			}
			x->up();
		}
	}
}
int perm[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	const int n=ni;
	int tot=ni;
	const seg::node rt=seg::build(n);
	for(int i=0;i<n;i++){
		perm[i]=ni;
		seg::alt_set(rt,i,perm[i]);
	}
	for(;tot--;){
		const int i=ni-1,j=ni-1;
		swap(perm[i],perm[j]);
		seg::alt_set(rt,i,perm[i]);
		seg::alt_set(rt,j,perm[j]);
		printf("%d\n",rt->ans);
	}
	return 0;
}
