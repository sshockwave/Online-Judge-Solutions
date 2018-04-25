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
namespace seg{
	const int N=::N*2*2*2*2;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		bool tag;
		int sum;
		inline void dn(){
			if(tag){
				lson->tag=true,lson->sum=0;
				rson->tag=true,rson->sum=0;
				tag=false;
			}
		}
		inline void up(){
			assert(!tag);
			sum=(lson->sum+rson->sum)%O;
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		assert(n<pool+N);
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->tag=false,x->sum=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void cov(node x,int l,int r){
		if(x->tag)return;
		if(x->l==l&&x->r==r){
			x->tag=true,x->sum=0;
			return;
		}
		if(r<=x->m){
			cov(x->lson,l,r);
		}else if(l>x->m){
			cov(x->rson,l,r);
		}else{
			cov(x->lson,l,x->m);
			cov(x->rson,x->m+1,r);
		}
		x->up();
	}
	void add(node x,int p,int v){
		if(x->l==x->r){
			x->sum=(x->sum+v)%O;
		}else{
			x->dn();
			add(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	int ask(node x,int l,int r){
		if(x->tag)return 0;
		if(x->l==l&&x->r==r)return x->sum;
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return (ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r))%O;
	}
}
struct intv{
	int l,r;
}int1[N],int2[N];//1:work 2:rest
int *numlst[N<<2];
bool ncmp(int *a,int *b){
	return *a<*b;
}
int act[N<<2];//discreted len:act[r]-act[l]
int ban1[N<<2],ban2[N<<2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("you.in","r",stdin);
	freopen("you.out","w",stdout);
#endif
	int ls=0;
	int st=0,ed=ni;
	numlst[++ls]=&st,numlst[++ls]=&ed;
	int n=ni,m=ni;//n:work m:rest
	for(int i=1;i<=n;i++){
		int1[i]=(intv){ni-1,ni};
		numlst[++ls]=&int1[i].l,numlst[++ls]=&int1[i].r;
	}
	for(int i=1;i<=m;i++){
		int2[i]=(intv){ni-1,ni};
		numlst[++ls]=&int2[i].l,numlst[++ls]=&int2[i].r;
	}
	sort(numlst+1,numlst+ls+1,ncmp);
	act[0]=0;
	int len=0;
	for(int i=1,&j=len=0;i<=ls;i++){
		if(act[j]!=*numlst[i]){
			act[++j]=*numlst[i];
		}
		*numlst[i]=j;
	}
	mset(ban1+1,-1,len);
	mset(ban2+1,-1,len);
	for(int i=1;i<=n;i++){
		apmax(ban1[int1[i].r],int1[i].l);
	}
	for(int i=1;i<=m;i++){
		apmax(ban2[int2[i].r],int2[i].l);
	}
	seg::node rt1=seg::build(0,len),rt2=seg::build(0,len);
	seg::add(rt1,0,1),seg::add(rt2,0,1);
	int f3=1;
	for(int i=1;i<=len;i++){
		if(ban1[i]>=0){
			seg::cov(rt1,0,ban1[i]);
		}
		if(ban2[i]>=0){
			seg::cov(rt2,0,ban2[i]);
		}
		//Trans to next i
		int pw2=fpow(2,act[i]-act[i-1]);
		int val1=rt1->sum,val2=rt2->sum;
		int tmp=(lint)(pw2-2)*f3%O;
		seg::add(rt1,i,(tmp+val2)%O);
		seg::add(rt2,i,(tmp+val1)%O);
		f3=((lint)tmp+val1+val2)%O;
	}
	printf("%d\n",f3);
	return 0;
}
