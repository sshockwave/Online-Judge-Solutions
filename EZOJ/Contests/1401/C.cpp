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
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace seg{
	struct Info{
		lint mn,mx,tmn;
		inline friend Info operator + (const Info &a,const Info &b){
			Info tmp=(Info){min(a.mn,b.mn),max(a.mx,b.mx),min(a.tmn,b.tmn)};
			if(a.mn<b.mx){
				apmin(tmp.tmn,a.mn);
			}
			return tmp;
		}
	};
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		lint dt,mval;
		Info info;
		inline void addv(int v){
			dt+=v,mval=mval!=LINF?mval+v:LINF;
			info.mn+=v,info.mx+=v,info.tmn+=v;
		}
		inline void apmn(int v){
			apmin(mval,v);
			apmin(info.mn,v);
			apmin(info.mx,v);
			if(v<=info.tmn){
				info.tmn=LINF;
			}
		}
		inline void up(){
			assert(dt==0&&mval==LINF);
			info=lson->info+rson->info;
		}
		inline void dn(){
			if(dt){
				lson->addv(dt);
				rson->addv(dt);
				dt=0;
			}
			if(mval<LINF){
				lson->apmn(mval);
				rson->apmn(mval);
				mval=LINF;
			}
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->dt=0,x->mval=LINF;
		if(l==r){
			x->info.mn=x->info.mx=ni;
			x->info.tmn=LINF;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void addv(node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->addv(v);
		x->dn();
		if(r<=x->m){
			addv(x->lson,l,r,v);
		}else if(l>x->m){
			addv(x->rson,l,r,v);
		}else{
			addv(x->lson,l,x->m,v);
			addv(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	void apmn(node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->apmn(v);
		x->dn();
		if(r<=x->m){
			apmn(x->lson,l,r,v);
		}else if(l>x->m){
			apmn(x->rson,l,r,v);
		}else{
			apmn(x->lson,l,x->m,v);
			apmn(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	Info ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->info;
		x->dn();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	int n=ni,tot=ni;
	seg::node rt=seg::build(1,n);
	while(tot--){
		int op=ni,l=ni,r=ni;
		if(op==1){
			seg::addv(rt,l,r,ni);
		}else if(op==2){
			seg::apmn(rt,l,r,ni);
		}else{
			printf("%d\n",seg::ask(rt,l,r).tmn<LINF?r-l+1:1);
		}
	}
	return 0;
}
