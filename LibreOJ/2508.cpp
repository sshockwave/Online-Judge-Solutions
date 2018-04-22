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
const int N=1000010,INF=0x7f7f7f7f;
int vala[N],valb[N];//a:mn b:mx
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,mx;
		inline void up(){
			mn=min(lson->mn,rson->mn);
			mx=max(lson->mx,rson->mx);
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->mn=vala[x->l],x->mx=valb[x->l];
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	int ask_mn(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mn;
		if(r<=x->m)return ask_mn(x->lson,l,r);
		if(l>x->m)return ask_mn(x->rson,l,r);
		return min(ask_mn(x->lson,l,x->m),ask_mn(x->rson,x->m+1,r));
	}
	int ask_mx(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mx;
		if(r<=x->m)return ask_mx(x->lson,l,r);
		if(l>x->m)return ask_mx(x->rson,l,r);
		return max(ask_mx(x->lson,l,x->m),ask_mx(x->rson,x->m+1,r));
	}
}
namespace pre_work{
	int *a,n,nowpos,nxt[N];
	int gnxt(int x){
		if(x==n)return n;
		if(nxt[x]==x&&(a[x]==0||(a[x]>x&&a[x]<=nowpos))){
			nxt[x]=x+1;
		}
		return nxt[x]!=x?nxt[x]=gnxt(nxt[x]):x;
	}
	int ans[N];
	inline const int* main(int _a[],int _n){//a:stores where the keys are
		a=_a,n=_n;
		for(int i=1;i<=n;i++){
			nxt[i]=i;
		}
		for(int &i=nowpos=1;i<n;i++){
			ans[i]=a[i]==0?i:a[i]>i?0:gnxt(a[i]);
		}
		return ans;
	}
}
seg::node rt;
inline bool ask(){
	int s=ni,t=ni;
	if(s<t)return seg::ask_mn(rt,s,t-1)>=s;
	else if(s>t)return seg::ask_mx(rt,t,s-1)<=s;
	else return true;
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	int n=ni,m=ni,p=ni;
	memset(a,0,sizeof(a));
	for(int i=1;i<=m;i++){
		int x=ni;
		a[x]=ni;
	}
	memcpy(vala+1,pre_work::main(a,n)+1,(n-1)*sizeof(vala[0]));
	{
		reverse(a+1,a+n);
		for(int i=1;i<n;i++){
			if(a[i]){
				a[i]=n+1-a[i];
			}
		}
		const int* tmp=pre_work::main(a,n);
		for(int i=1;i<n;i++){
			valb[n-i]=n-tmp[i]+1;
		}
	}
	if(n==1){
		for(int i=1;i<=p;i++){
			puts("YES");
		}
		return 0;
	}
	rt=seg::build(1,n-1);
	for(int i=1;i<=p;i++){
		puts(ask()?"YES":"NO");
	}
	return 0;
}
