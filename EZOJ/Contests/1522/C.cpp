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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=40010;
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
	int dfn[N],dfe[N],tim=0;
	void dfs(int x,int fa){
		dfn[x]=++tim;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dfs(v,x);
		}
		dfe[x]=tim;
	}
}
int ans[N];
struct Path{
	int u,v,w,idx;
}rut[N],qry[N];
inline bool w_cmp(const Path &a,const Path &b){
	return a.w<b.w;
}
inline bool v_cmp(const Path &a,const Path &b){
	return T::dfn[a.v]<T::dfn[b.v];
}
namespace B{
	int c[N],n;
	int tag[N],tim=0;
	inline void init(int _n){
		n=_n;
		++tim;
	}
	inline void upd(int x){
		if(tag[x]<tim){
			c[x]=0,tag[x]=tim;
		}
	}
	inline void add(int x,int v){
		for(;x<=n;upd(x),c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int a=0;
		for(;x;upd(x),a+=c[x],x^=x&-x);
		return a;
	}
}
struct Event{
	int y,l,r,dt;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.y<b.y;
	}
}ev[N<<2];
Path lst1[N],lst2[N];
inline void addsq(int x1,int x2,int y1,int y2,int &es){
	ev[++es]=(Event){y1,x1,x2,1};
	ev[++es]=(Event){y2+1,x1,x2,-1};
}
void solve(int p1,int p2,int q1,int q2){
	if(q1>q2)return;
	if(p1==p2){
		for(int i=q1;i<=q2;i++){
			ans[qry[i].idx]=rut[p1].w;
		}
		return;
	}
	using T::dfn;
	using T::dfe;
	int pm=(p1+p2)>>1;
	int es=0;
	for(int i=p1;i<=pm;i++){
		const int u=rut[i].u,v=rut[i].v;
		assert(dfn[u]<=dfn[v]);
		if(dfn[v]<=dfe[u]){
			addsq(1,dfn[u],dfn[v],dfe[v],es);
			addsq(dfn[v],dfe[v],dfe[u],T::tim,es);
		}else{
			addsq(dfn[u],dfe[u],dfn[v],dfe[v],es);
		}
	}
	ev[++es]=(Event){T::tim+1,1,1,0};
	sort(ev+1,ev+es+1);
	B::init(T::tim);
	int ls1=0,ls2=0;
	int j=q1;
	for(int i=1;i<=es;i++){
		for(;j<=q2&&dfn[qry[j].v]<ev[i].y;j++){
			int t=B::sum(dfn[qry[j].u]);
			if(qry[j].w<=t){
				lst1[++ls1]=qry[j];
			}else{
				(lst2[++ls2]=qry[j]).w-=t;
			}
		}
		B::add(ev[i].l,ev[i].dt);
		B::add(ev[i].r+1,-ev[i].dt);
	}
	assert(ls1+ls2==q2-q1+1);
	mcpy(qry+q1,lst1+1,ls1);
	mcpy(qry+q1+ls1,lst2+1,ls2);
	solve(p1,pm,q1,q1+ls1-1);
	solve(pm+1,p2,q1+ls1,q2);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	const int n=ni,tot1=ni,tot2=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(1,0);
	using T::dfn;
	for(int i=1;i<=tot1;i++){
		rut[i]=(Path){ni,ni,ni,i};
		if(dfn[rut[i].u]>dfn[rut[i].v]){
			swap(rut[i].u,rut[i].v);
		}
	}
	sort(rut+1,rut+tot1+1,w_cmp);
	for(int i=1;i<=tot2;i++){
		qry[i]=(Path){ni,ni,ni,i};
		if(dfn[qry[i].u]>dfn[qry[i].v]){
			swap(qry[i].u,qry[i].v);
		}
	}
	sort(qry+1,qry+tot2+1,v_cmp);
	solve(1,tot1,1,tot2);
	for(int i=1;i<=tot2;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
