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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T cabs(T x){return x>=0?x:-x;}
const int N=200010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
lint val[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		lint val[2];
		inline void up(){
			val[0]=min(lson->val[0],rson->val[0]);
			val[1]=min(lson->val[1],rson->val[1]);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		memset(x->val,127,sizeof(x->val));
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	lint ask(node x,int l,int r,int d){
		if(x->l==l&&x->r==r)return x->val[d];
		if(r<=x->m)return ask(x->lson,l,r,d);
		if(l>x->m)return ask(x->rson,l,r,d);
		return min(ask(x->lson,l,x->m,d),ask(x->rson,x->m+1,r,d));
	}
	void set(node x,int p,lint v){
		if(x->l==x->r){
			val[p]=v;
			x->val[0]=v+p;
			x->val[1]=v-p;
		}else{
			set(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
}
int main(){
	int n=ni,tot=ni,last=ni;
	lint delta=0;
	memset(val,127,sizeof(val));
	seg::set(seg::rt=seg::build(1,n),ni,0);
	while(tot--){
		using namespace seg;
		int cur=ni;
		lint val=min(ask(rt,1,cur,1)+cur,ask(rt,cur,n,0)-cur)+delta;
		delta+=cabs(cur-last);
		if(val<(::val[cur]+delta)){
			set(rt,last,val-delta);
		}
		last=cur;
	}
	lint ans=LINF;
	for(int i=1;i<=n;i++){
		apmin(ans,val[i]);
	}
	printf("%lld\n",ans+delta);
	return 0;
}
