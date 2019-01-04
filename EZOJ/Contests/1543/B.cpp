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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace dj{
	int fa[N];
	inline void init(int n){
		mset(fa+1,0,n);
	}
	inline int rt(int x){
		return fa[x]?fa[x]=rt(fa[x]):x;
	}
}
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Info{
		int x;
		lint w;
		inline friend bool operator != (const Info &a,const Info &b){
			return dj::rt(a.x)!=dj::rt(b.x);
		}
		inline friend bool operator < (const Info &a,const Info &b){
			return a.w<b.w;
		}
	};
	const Info null=(Info){0,LINF};
	struct Node{
		node lson,rson;
		int l,m,r;
		Info v1,v2;
		lint dt;
		inline void addv(lint v){
			dt+=v;
			v1.w+=v;
			if(v2.w<LINF){
				v2.w+=v;
			}
		}
		inline void up(){
			v1=min(lson->v1,rson->v1);
			const Info v_l=lson->v1!=v1?lson->v1:lson->v2!=v1?lson->v2:null;
			const Info v_r=rson->v1!=v1?rson->v1:rson->v2!=v1?rson->v2:null;
			v2=min(v_l,v_r);
			int t=dt;
			dt=0;
			addv(t);
		}
	}pool[N];
	node n;
	node build(int l,int r){
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->dt=0;
		if(l==r){
			x->v1=(Info){x->m,0},x->v2=null;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void alt_add(const node x,int l,int r,lint w){
		if(x->l==l&&x->r==r)return x->addv(w);
		if(r<=x->m){
			alt_add(x->lson,l,r,w);
		}else if(l>x->m){
			alt_add(x->rson,l,r,w);
		}else{
			alt_add(x->lson,l,x->m,w);
			alt_add(x->rson,x->m+1,r,w);
		}
		x->up();
	}
}
struct Event{
	int y,l,r,w;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.y<b.y;
	}
}ev[N<<2];
struct Edge{
	int u,v;
	lint w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}edg[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
#endif
	const int n=ni;
	int es=0;
	for(int tot=ni;tot--;){
		const int x1=ni,x2=ni,y1=ni,y2=ni,w=ni;
		ev[++es]=(Event){y1,x1,x2,w};
		ev[++es]=(Event){y2+1,x1,x2,-w};
		ev[++es]=(Event){x1,y1,y2,w};
		ev[++es]=(Event){x2+1,y1,y2,-w};
	}
	sort(ev+1,ev+es+1);
	int ccnt=n;
	dj::init(n);
	lint ans=0;
	for(;ccnt>1;){
		seg::n=seg::pool;
		const seg::node rt=seg::build(1,n);
		for(int i=1;i<=n;i++){
			edg[i].w=LINF;
		}
		for(int i=1,j=1;i<=n;i++){
			for(;j<=es&&ev[j].y<=i;j++){
				seg::alt_add(rt,ev[j].l,ev[j].r,ev[j].w);
			}
			seg::Info v=dj::rt(rt->v1.x)!=dj::rt(i)?rt->v1:rt->v2;
			apmin(edg[dj::rt(i)],(Edge){i,v.x,v.w});
		}
		int es=0;
		for(int i=1;i<=n;i++){
			if(dj::fa[i]==0){
				edg[++es]=edg[i];
			}
		}
		sort(edg+1,edg+es+1);
		for(int i=1;i<=es;i++){
			int u=dj::rt(edg[i].u),v=dj::rt(edg[i].v);
			if(u!=v){
				--ccnt;
				ans+=edg[i].w;
				dj::fa[u]=v;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
