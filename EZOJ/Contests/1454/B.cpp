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
const int N=500010;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int dt;
		lint sum;
		inline void addv(int v){
			sum+=(lint)(r-l+1)*v,dt+=v;
		}
		inline void up(){
			assert(dt==0);
			sum=lson->sum+rson->sum;
		}
		inline void dn(){
			if(dt){
				lson->addv(dt);
				rson->addv(dt);
				dt=0;
			}
		}
	}pool[N];
	node build(const int l,const int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->sum=x->dt=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
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
	void dfsclr(node x){
		x->sum=x->dt=0;
		if(x->l!=x->r){
			dfsclr(x->lson);
			dfsclr(x->rson);
		}
	}
	lint ask(node x,int l,int r){
		if(l>r)return 0;
		if(x->l==l&&x->r==r)return x->sum;
		x->dn();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
namespace manacher{
	int a[N<<1],n;
	inline void init(){
		a[n=0]=-2;
		a[++n]=-1;
	}
	inline void fixup(){
		a[n+1]=-3;
	}
	inline void psh(int x){
		a[++n]=x,a[++n]=-1;
	}
	int rad[N<<1];
	inline void main(){
		rad[0]=0;
		for(int i=1,j=0;i<=n;i++){
			rad[i]=i<=rad[j]+j?min(rad[j*2-i],rad[j]+j-i):0;
			for(int &k=rad[i];a[i-k-1]==a[i+k+1];k++);
			if(i+rad[i]>j+rad[j]){
				j=i;
			}
		}
	}
}
char s[N];
struct Query{
	int id,ql,qr,l,r;
}q[N];
struct Event{
	int l,r;
}ev[N<<1];
lint finans[N];
template<class T>inline bool cmp_l(const T &a,const T &b){
	return a.l<b.l;
}
template<class T>inline bool cmp_r(const T &a,const T &b){
	return a.r<b.r;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("palindrome.in","r",stdin);
	freopen("palindrome.out","w",stdout);
#endif
	scanf("%s",s+1);
	const int n=strlen(s+1);
	manacher::init();
	for(int i=1;i<=n;i++){
		manacher::psh(s[i]-'a');
	}
	manacher::fixup();
	manacher::main();
	const seg::node rt=seg::build(1,n);
	const int tot=ni;
	for(int i=1;i<=tot;i++){
		q[i]=(Query){i,ni,ni,0,0};
		finans[i]=0;
	}
	{//deal left half
		for(int i=1;i<=tot;i++){
			q[i].l=q[i].ql;
			q[i].r=(q[i].ql+q[i].qr-1)>>1;
		}
		sort(q+1,q+tot+1,cmp_r<Query>);
		int es=0;
		for(int i=1;i<=manacher::n;i++){
			using manacher::rad;
			int l,r;
			if(i&1){
				assert((rad[i]&1)==0);
				r=(i-1)>>1;
				l=r-(rad[i]>>1)+1;
			}else{
				assert(rad[i]&1);
				l=(i-rad[i]+1)>>1,r=i>>1;
			}
			if(l<=r){
				ev[++es]=(Event){l,r};
			}
		}
		sort(ev+1,ev+es+1,cmp_r<Event>);
		for(int i=1,jq=1,je=1;i<=n;i++){
			for(;je<=es&&ev[je].r==i;je++){
				seg::add(rt,ev[je].l,ev[je].r,1);
			}
			for(;jq<=tot&&q[jq].r<i;jq++);
			for(;jq<=tot&&q[jq].r==i;jq++){
				finans[q[jq].id]+=seg::ask(rt,q[jq].l,q[jq].r);
			}
		}
	}
	seg::dfsclr(rt);
	{//deal right half
		for(int i=1;i<=tot;i++){
			q[i].l=((q[i].ql+q[i].qr)>>1)+1;
			q[i].r=q[i].qr;
		}
		sort(q+1,q+tot+1,cmp_l<Query>);
		int es=0;
		for(int i=1;i<=manacher::n;i++){
			using manacher::rad;
			int l,r;
			if(i&1){
				assert((rad[i]&1)==0);
				l=(i+1)>>1;
				r=l+(rad[i]>>1)-1;
			}else{
				assert(rad[i]&1);
				l=i>>1,r=(i+rad[i]-1)>>1;
			}
			if(l<=r){
				ev[++es]=(Event){l,r};
			}
		}
		sort(ev+1,ev+es+1,cmp_l<Event>);
		for(int i=n,jq=tot,je=es;i>=1;i--){
			for(;je>=1&&ev[je].l==i;je--){
				seg::add(rt,ev[je].l,ev[je].r,1);
			}
			for(;jq>=1&&q[jq].l>i;jq--);
			for(;jq>=1&&q[jq].l==i;jq--){
				finans[q[jq].id]+=seg::ask(rt,q[jq].l,q[jq].r);
			}
		}
	}
	{//substract same
		for(int i=1;i<=tot;i++){
			const int l=q[i].ql,r=q[i].qr;
			const int t=min(r-l+1,manacher::rad[l+r]);
			if((r-l+1)&1){
				finans[q[i].id]+=(t+1)>>1;
			}else{
				assert((t&1)==0);
				finans[q[i].id]-=t>>1;
			}
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%lld\n",finans[i]);
	}
	return 0;
}
