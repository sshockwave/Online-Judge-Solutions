#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=2e5+10;
int n;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,mx;
		bool istag;
		lint sum;
		inline void setv(int v){
			mn=mx=v;
			istag=true;
			sum=(lint)v*(r-l+1);
		}
		inline void dn(){
			if(istag){
				lson->setv(mn);
				rson->setv(mn);
				istag=false;
			}
		}
		inline void up(){
			assert(!istag);
			mn=lson->mn,mx=rson->mx;
			sum=lson->sum+rson->sum;
		}
	}pool[N];
	node rt;
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->istag=false;
		if(x->l==x->r){
			x->mn=x->mx=x->sum=::n+1;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	lint ask_sum(const node x,int l,int r){
		if(x->l==l&&x->r==r)return x->sum;
		if(x->mn==x->mx)return (lint)x->mn*(r-l+1);
		x->dn();
		if(r<=x->m)return ask_sum(x->lson,l,r);
		if(l>x->m)return ask_sum(x->rson,l,r);
		return ask_sum(x->lson,l,x->m)+ask_sum(x->rson,x->m+1,r);
	}
	inline lint ask_v(int p){
		if(p>n)return n+1;
		return ask_sum(rt,p,p);
	}
	int ask_last(const node x,int v){//last pos that is <= v!
		if(x->mx<=v)return x->r;
		if(x->mn>v)return x->l-1;
		x->dn();
		int ans=ask_last(x->rson,v);
		return ans>x->m?ans:ask_last(x->lson,v);
	}
	void alt_min(const node x,int r,int v){
		if(x->mx<=v)return;
		if(x->r==r&&x->mn>=v)return x->setv(v);
		x->dn();
		if(r<=x->m){
			alt_min(x->lson,r,v);
		}else{
			alt_min(x->lson,x->m,v);
			alt_min(x->rson,r,v);
		}
		x->up();
	}
	void alt_step(const node x){
		if(x->mn==n+1)return;
		if(x->mn==x->mx)return x->setv(ask_v(x->mn+1));
		x->dn();
		alt_step(x->lson),alt_step(x->rson);
		x->up();
	}
}
using seg::rt;
struct Query{
	int l,r;
	lint ans;
}qry[N];
vi pos[N],qlst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	n=ni;
	const int m=ni,q=ni;
	for(int i=1;i<=n;i++){
		pos[ni].push_back(i);
	}
	for(int i=1;i<=q;i++){
		qry[i]=(Query){ni,ni,0};
		qlst[ni].push_back(i);
	}
	rt=seg::build(1,n);
	for(int i=1;i<=m;i++){
		seg::alt_step(rt);
		for(vi::reverse_iterator it=pos[i].rbegin(),ti=pos[i].rend();it!=ti;++it){
			seg::alt_min(rt,*it,*it);
		}
		for(vi::iterator it=qlst[i].begin(),ti=qlst[i].end();it!=ti;++it){
			const int l=qry[*it].l,r=qry[*it].r;
			const int p=min(seg::ask_last(rt,r),r);
			qry[*it].ans=p>=l?(lint)(p-l+1)*(r+1)-seg::ask_sum(rt,l,p):0;
		}
	}
	for(int i=1;i<=q;i++){
		printf("%lld\n",qry[i].ans);
	}
	return 0;
}
