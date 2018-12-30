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
const int N=120010;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,mncnt;
		int dt,hitcnt;
		lint sum;
		inline void addv(int d,int h){
			mn+=d;
			dt+=d,hitcnt+=h;
			sum+=(lint)mncnt*h;
		}
		inline void dn(){
			if(dt||hitcnt){
				int v=min(lson->mn,rson->mn);
				lson->addv(dt,lson->mn==v?hitcnt:0);
				rson->addv(dt,rson->mn==v?hitcnt:0);
				dt=hitcnt=0;
			}
		}
		inline void up(){
			assert(dt==0&&hitcnt==0);
			mn=min(lson->mn,rson->mn);
			mncnt=(lson->mn==mn?lson->mncnt:0)+(rson->mn==mn?rson->mncnt:0);
			sum=lson->sum+rson->sum;
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->mn=x->dt=x->hitcnt=0;
		x->mncnt=r-l+1;
		x->sum=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void alt_add(const node x,int l,int r,int v){
		if(l>r)return;
		if(x->l==l&&x->r==r)return x->addv(v,0);
		x->dn();
		if(r<=x->m){
			alt_add(x->lson,l,r,v);
		}else if(l>x->m){
			alt_add(x->rson,l,r,v);
		}else{
			alt_add(x->lson,l,x->m,v);
			alt_add(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	void alt_hit(const node x,int l,int r){
		if(x->mn>0)return;
		if(x->l==l&&x->r==r)return x->addv(0,1);
		x->dn();
		if(r<=x->m){
			alt_hit(x->lson,l,r);
		}else if(l>x->m){
			alt_hit(x->rson,l,r);
		}else{
			alt_hit(x->lson,l,x->m);
			alt_hit(x->rson,x->m+1,r);
		}
		x->up();
	}
	lint ask(const node x,int l,int r){
		if(x->l==l&&x->r==r)return x->sum;
		x->dn();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
struct Query{
	int l;
	lint ans;
}qry[N];
vi q[N];
int perm[N];
int stk1[N],ss1=0;
int stk2[N],ss2=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		perm[i]=ni;
	}
	int tot=ni;
	for(int i=1;i<=tot;i++){
		qry[i]=(Query){ni,0};
		q[ni].push_back(i);
	}
	const seg::node rt=seg::build(1,n);
	stk1[0]=stk2[0]=0;
	for(int i=1;i<=n;i++){
		for(;ss1&&perm[stk1[ss1]]>perm[i];ss1--){
			seg::alt_add(rt,stk1[ss1-1]+1,stk1[ss1],perm[stk1[ss1]]-perm[i]);
		}
		stk1[++ss1]=i;
		for(;ss2&&perm[stk2[ss2]]<perm[i];ss2--){
			seg::alt_add(rt,stk2[ss2-1]+1,stk2[ss2],perm[i]-perm[stk2[ss2]]);
		}
		stk2[++ss2]=i;
		seg::alt_add(rt,1,i-1,-1);
		seg::alt_hit(rt,1,i);
		for(vi::iterator it=q[i].begin(),ti=q[i].end();it!=ti;++it){
			qry[*it].ans=seg::ask(rt,qry[*it].l,i);
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%lld\n",qry[i].ans);
	}
	return 0;
}
