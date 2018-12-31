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
inline char gc(){
	const static int N=2000000;
	static char buf[N],*h=buf,*t=buf;
	if(h==t){
		t=buf+fread(h=buf,1,N,stdin);
		if(h==t)return EOF;
	}
	return *h++;
}
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=gc())&&c!='-');
	bool neg=c=='-';
	neg?c=gc():0;
	while(i=i*10-'0'+c,isdigit(c=gc()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		lint mx,dt;
		inline void addv(int v){
			mx+=v,dt+=v;
		}
		inline void up(){
			mx=max(lson->mx,rson->mx)+dt;
		}
	}pool[N];
	node n;
	node build(int l,int r){
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->mx=-INF,x->dt=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void alt_add(const node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->addv(v);
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
}
struct Pt{
	int x,y;
}pt[N];
inline bool cmp_x(const Pt &a,const Pt &b){
	return a.x<b.x;
}
int n,k;
struct Ev{
	lint y;
	int l,r,v;
	inline friend bool operator < (const Ev &a,const Ev &b){
		return a.y!=b.y?a.y<b.y:a.v<b.v;
	}
}ev[N<<1];
inline bool jdg(lint t){
	int es=0;
	for(int i=1,j=1;i<=n;i++){
		const lint l=pt[i].y,r=pt[i].y+t+1;
		for(;j<=n&&(lint)pt[j].x-pt[i].x<=t;j++);
		ev[++es]=(Ev){l,i,j-1,1};
		ev[++es]=(Ev){r,i,j-1,-1};
	}
	seg::n=seg::pool;
	const seg::node rt=seg::build(1,n);
	sort(ev+1,ev+es+1);
	for(int i=1;i<=es;i++){
		seg::alt_add(rt,ev[i].l,ev[i].l,ev[i].v*INF);
		seg::alt_add(rt,ev[i].l,ev[i].r,ev[i].v);
		if(rt->mx>=k)return true;
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	n=ni,k=ni;
	int xmn=INF,xmx=-INF;
	int ymn=INF,ymx=-INF;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		apmin(xmn,pt[i].x);
		apmax(xmx,pt[i].x);
		apmin(ymn,pt[i].y);
		apmax(ymx,pt[i].y);
	}
	sort(pt+1,pt+n+1,cmp_x);
	lint l=0,r=max((lint)xmx-xmn,(lint)ymx-ymn);
	for(;l<r;){
		const lint m=(l+r)>>1;
		if(jdg(m)){
			r=m;
		}else{
			l=m+1;
		}
	}
	printf("%lld\n",l);
	return 0;
}
