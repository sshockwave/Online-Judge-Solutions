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
const int N=30010;
int philst[200];
int phils=0;
const int &O=philst[0];
inline int care_mod(int x,int i){
	return i==0?x%O:x>philst[i]?x%philst[i]+philst[i]:x;
}
inline int care_fpow(int x,int n,const int i){
	int a=1;
	for(;n;n>>=1,x=care_mod(x*x,i)){
		if(n&1){
			a=care_mod(a*x,i);
		}
	}
	return a;
}
inline void get_phi(int x){
	for(philst[0]=x,phils=1;x!=1;x=philst[phils++]){
		int &phi=philst[phils]=1;
		for(int i=2;i*i<=x;i++){
			if(x%i)continue;
			phi*=i-1,x/=i;
			for(;x%i==0;x/=i,phi*=i);
		}
		if(x!=1){
			phi*=x-1;
		}
	}
}
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		bool unifi;
		int *pval,sum;
		inline void alt(int c){
			assert(unifi);
			for(int i=0;i+1<phils;i++){
				pval[i]=care_fpow(care_mod(c,i),pval[i+1],i);
			}
			pval[phils-1]=c>0;
			sum=pval[0]*(r-l+1)%O;
		}
		inline void up(){
			assert(!unifi);
			sum=(lson->sum+rson->sum)%O;
			if(lson->unifi&&rson->unifi){
				unifi=true;
				for(int i=0;i<phils;i++){
					if(lson->pval[i]!=rson->pval[i]){
						unifi=false;
						break;
					}
					pval[i]=lson->pval[i];
				}
			}
		}
		inline void dn(){
			if(unifi){
				memcpy(lson->pval,pval,phils*sizeof(pval[0]));
				memcpy(rson->pval,pval,phils*sizeof(pval[0]));
				unifi=false;
			}
		}
	}pool[N];
	node rt;
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->pval=new int[phils];
		if(l==r){
			x->unifi=true;
			const int v=x->sum=ni;
			for(int i=0;i<phils;i++){
				x->pval[i]=care_mod(v,i);
			}
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	lint ask(node x,int l,int r){//cout check precision
		if(x->unifi)return x->pval[0]*(r-l+1);
		if(x->l==l&&x->r==r)return x->sum;
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
	inline int ask(int l,int r){
		return ask(rt,l,r)%O;
	}
	void alt(node x,int l,int r,int c){
		if(x->l==l&&x->r==r&&x->unifi)return x->alt(c);
		x->dn();
		if(r<=x->m){
			alt(x->lson,l,r,c);
		}else if(l>x->m){
			alt(x->rson,l,r,c);
		}else{
			alt(x->lson,l,x->m,c);
			alt(x->rson,x->m+1,r,c);
		}
		x->up();
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("rough.in","r",stdin);
	freopen("rough.out","w",stdout);
#endif
	int n=ni,tot=ni;
	get_phi(ni);
	seg::rt=seg::build(1,n);
	for(int tt=1;tt<=tot;tt++){
		const int op=ni,l=ni,r=ni;
		if(op){//ask
			printf("%d\n",seg::ask(l,r));
		}else{//alt
			seg::alt(seg::rt,l,r,ni);
		}
	}
	return 0;
}
