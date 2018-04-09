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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=500010,INF=0x7f7f7f7f;
int a[N],b[N];
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int cap,sum,exc;
		inline void up(){
			cap=lson->cap+rson->cap;
			sum=lson->sum+rson->sum;
			exc=max(lson->exc+rson->sum,lson->cap+rson->exc);
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->cap=b[l];
			x->sum=x->exc=0;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void add_cap(node x,int p,int v){
		if(x->l==x->r){
			x->cap+=v;
		}else{
			add_cap(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	void add_sum(node x,int p,int v){
		if(x->l==x->r){
			x->sum+=v,x->exc+=v;
		}else{
			add_sum(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	int ask(node x,int exc,int cnt,int cap){
		assert(exc+x->sum+cnt<=x->cap+cap);
		if(x->l==x->r)return x->l;
		int lexc=max(max(x->lson->exc,exc+x->lson->sum)-x->lson->cap,0);
		if(lexc+x->rson->sum+cnt<=x->rson->cap+cap)return ask(x->rson,lexc,cnt,cap);
		return ask(x->lson,exc,cnt,cap+x->rson->cap-x->rson->sum);
	}
}
int fa[N],cnt[N];
int pos[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("iiidx.in","r",stdin);
	freopen("iiidx.out","w",stdout);
#endif
	int n=ni;
	double k;
	scanf("%lf",&k);
	for(int i=1;i<=n;i++){
		a[i]=ni,fa[i]=i/k;
	}
	sort(a+1,a+n+1);
	for(int i=n;i>=1;i--){
		cnt[fa[i]]+=++cnt[i];
	}
	int m=0;
	a[0]=-1;
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++){
		if(a[i]!=a[m]){
			a[++m]=a[i];
		}
		b[m]++;
	}
	seg::node rt=seg::build(1,m);
	seg::add_sum(rt,pos[0]=1,cnt[0]);
	for(int i=1;i<=n;i++){
		seg::add_sum(rt,pos[fa[i]],-cnt[fa[i]]);
		pos[i]=seg::ask(rt,0,cnt[i],0);
		seg::add_cap(rt,pos[i],-1);
		seg::add_sum(rt,pos[fa[i]],cnt[fa[i]]-=cnt[i]);
		seg::add_sum(rt,pos[i],--cnt[i]);
		printf("%d ",a[pos[i]]);
	}
	putchar('\n');
	return 0;
}
