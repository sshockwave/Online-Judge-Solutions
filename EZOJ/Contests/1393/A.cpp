#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
const int N=100010,SH=30;
struct trf{
	uint a,b;//0->a,1->b
	inline void clr(){
		a=0,b=-1;
	}
	inline uint operator () (uint x)const{
		return ((~x)&a)|(x&b);
	}
	inline void tr(const trf &f){
		a=f(a),b=f(b);
	}
};
struct lb{
	uint a[SH];
	lb(){
		memset(a,0,sizeof(a));
	}
	inline bool ins(uint x){
		for(int i=SH-1;i>=0;i--){
			if((x>>i)&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					return true;
				}
			}
		}
		return false;
	}
};
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		trf tag;
		inline void dn(){
			lson->tag.tr(tag);
			rson->tag.tr(tag);
			tag.clr();
		}
	}pool[N];
	node rt;
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->tag.a=x->tag.b=next_num<uint>();
		}else{
			x->tag.clr();
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void tr(node x,int l,int r,const trf &f){
		if(x->l==l&&x->r==r)return x->tag.tr(f);
		x->dn();
		if(r<=x->m)return tr(x->lson,l,r,f);
		if(l>x->m)return tr(x->rson,l,r,f);
		tr(x->lson,l,x->m,f);
		tr(x->rson,x->m+1,r,f);
	}
	bool putnum(node x,int l,int r,lb &b){
		if(x->l==x->r)return !b.ins(x->tag.a);
		x->dn();
		if(r<=x->m)return putnum(x->lson,l,r,b);
		else if(l>x->m)return putnum(x->rson,l,r,b);
		if(putnum(x->lson,l,x->m,b))return true;
		return putnum(x->rson,x->m+1,r,b);
	}
}
inline bool ask(int l,int r){
	if(r-l+1>30)return true;
	lb b;
	return seg::putnum(seg::rt,l,r,b);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
#endif
	int n=ni;
	seg::rt=seg::build(1,n);
	for(int tot=ni;tot--;){
		int op=ni,l=ni,r=ni;
		if(op==0){
			puts(ask(l,r)?"Yes":"No");
		}else{
			uint x=next_num<uint>();
			trf f;
			if(op==1){
				f.a=0,f.b=x;
			}else if(op==2){
				f.a=x,f.b=-1;
			}else{
				f.a=x,f.b=~x;
			}
			seg::tr(seg::rt,l,r,f);
		}
	}
	return 0;
}
