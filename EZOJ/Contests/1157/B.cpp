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
const int N=500010;
namespace seg{
	struct Node{
		Node *lson,*rson;
		int cnt;
	}pool[N*20];
	typedef Node* node;
	inline void init(){
		pool[0]=(Node){pool,pool,0};
	}
	inline node renew(node x){
		static node n=pool;
		*(++n)=*x;
		return n;
	}
	inline node alt(node x,int l,int r,int p){
		x=renew(x);
		x->cnt++;
		if(l!=r){
			int mid=(l+r)>>1;
			if(p<=mid){
				x->lson=alt(x->lson,l,mid,p);
			}else{
				x->rson=alt(x->rson,mid+1,r,p);
			}
		}
		return x;
	}
	inline int sub(node x,node y,int l,int r,int v){
		if(l==r){
			return y->cnt-x->cnt>v?l:0;
		}
		int mid=(l+r)>>1;
		if(y->lson->cnt-x->lson->cnt>v){
			return sub(x->lson,y->lson,l,mid,v);
		}
		if(y->rson->cnt-x->rson->cnt>v){
			return sub(x->rson,y->rson,mid+1,r,v);
		}
		return 0;
	}
}
seg::node rt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("kur.in","r",stdin);
	freopen("kur.out","w",stdout);
#endif
	int n=ni,tot=ni;
	seg::init();
	rt[0]=seg::pool;
	for(int i=1;i<=n;i++){
		rt[i]=seg::alt(rt[i-1],1,n,ni);
	}
	while(tot--){
		int l=ni,r=ni;
		printf("%d\n",seg::sub(rt[l-1],rt[r],1,n,(r-l+1)>>1));
	}
	return 0;
}
