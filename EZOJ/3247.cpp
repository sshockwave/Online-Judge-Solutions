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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
int ans=0;
int a[N],m;
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int mx[2];
		inline void up(){
			mx[0]=max(lson->mx[0],rson->mx[0]);
			mx[1]=max(lson->mx[1],rson->mx[1]);
		}
	}pool[N*20],Null;
	node null;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
	}
	inline node nn(){
		static node n=pool;
		return *n=Null,n++;
	}
	void upd(node &x,int p,int v1,int v2,int l=1,int r=m){
		if(x==null){
			x=nn();
		}
		if(l==r){
			apmax(x->mx[0],v1);
			apmax(x->mx[1],v2);
			return;
		}
		const int m=(l+r)>>1;
		if(p<=m){
			upd(x->lson,p,v1,v2,l,m);
		}else{
			upd(x->rson,p,v1,v2,m+1,r);
		}
		x->up();
	}
	node mg(node u,node v,int _mx1,int mx_1,int _mx2,int mx_2,int l=1,int r=m){
		apmax(ans,_mx1+max(v->mx[1],mx_2));
		apmax(ans,_mx2+max(u->mx[1],mx_1));
		apmax(ans,max(_mx2,v->mx[0])+mx_1);
		apmax(ans,max(_mx1,u->mx[0])+mx_2);
		if(u==null||v==null)return u!=null?u:v;
		if(l==r){
			apmax(u->mx[0],v->mx[0]);
			apmax(u->mx[1],v->mx[1]);
			return u;
		}
		const int m=(l+r)>>1;
		const int u0=u->lson->mx[0],u1=u->rson->mx[1];
		const int v0=v->lson->mx[0],v1=v->rson->mx[1];
		u->lson=mg(u->lson,v->lson,_mx1,max(u1,mx_1),_mx2,max(v1,mx_2),l,m);
		u->rson=mg(u->rson,v->rson,max(_mx1,u0),mx_1,max(_mx2,v0),mx_2,m+1,r);
		u->up();
		return u;
	}
	int ask(node x,int a,int b,int t,int l=1,int r=m){
		if(a>b||x==null)return 0;
		if(l==a&&r==b)return x->mx[t];
		const int m=(l+r)>>1;
		if(b<=m)return ask(x->lson,a,b,t,l,m);
		if(a>m)return ask(x->rson,a,b,t,m+1,r);
		return max(ask(x->lson,a,m,t,l,m),ask(x->rson,m+1,b,t,m+1,r));
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	seg::node rt[N];
	void dfs(const int x,const int fa){
		seg::upd(rt[x]=seg::null,a[x],1,1);
		//0:up 1:down
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dfs(v,x);
			rt[x]=seg::mg(rt[x],rt[v],0,0,0,0);
			const int ans1=seg::ask(rt[x],1,a[x]-1,0)+1;
			const int ans2=seg::ask(rt[x],a[x]+1,m,1)+1;
			seg::upd(rt[x],a[x],ans1,ans2);
		}
	}
}
namespace disc{
	int *pt[N];
	inline bool pt_cmp(int* a,int* b){
		return *a<*b;
	}
	inline void main(const int n){
		for(int i=1;i<=n;i++){
			pt[i]=a+i;
		}
		sort(pt+1,pt+n+1,pt_cmp);
		m=0;
		for(int i=1,v=-1;i<=n;i++){
			*pt[i]=v!=*pt[i]?v=*pt[i],++m:m;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	disc::main(n);
	T::init(n);
	seg::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(1,0);
	apmax(ans,T::rt[1]->mx[0]);
	apmax(ans,T::rt[1]->mx[1]);
	printf("%d\n",ans);
	return 0;
}
