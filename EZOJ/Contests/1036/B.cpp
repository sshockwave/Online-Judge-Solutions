#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef long double ld;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T>inline T sqr(T x){
	return x*x;
}
const int N=66000;
inline bool isz(ld x){
	const static double EPS=1e-4;
	return x>=-EPS&&x<=EPS;
}
ld faca,facb,ans=0.1;
inline double nd(){
	double x;
	scanf("%lf",&x);
	return x;
}
inline double parse_nd(){
	double in=nd(),l=-N,r=N;
	const static double EPS=1e-8;
	while(r-l>EPS){
		double m=(l+r)/2,v=m*ans+1;
		if(faca*v-facb*sin(v)<in){
			l=m;
		}else{
			r=m;
		}
	}
	return l;
}
namespace T{
	struct Node;
	typedef Node* node;
	struct Node{
		ld x[3],mn[3],mx[3];
		node lson,rson;
		int d,size,id;
		inline void up(){
			size=lson->size+rson->size+1;
			for(int i=0;i<3;i++){
				mn[i]=min(x[i],min(lson->mn[i],rson->mn[i]));
				mx[i]=max(x[i],max(lson->mx[i],rson->mx[i]));
			}
		}
		inline bool bal(){
			return lson->size*10<=size*7&&rson->size*10<=size*7;
		}
		inline ld d2(){
			return sqr(x[0])+sqr(x[1])+sqr(x[2]);
		}
		inline friend Node operator - (const Node &a,const Node &b){
			return (Node){a.x[0]-b.x[0],a.x[1]-b.x[1],a.x[2]-b.x[2]};
		}
	}*rt,null=(Node){0,0,0,N,N,N,-N,-N,-N};
	inline node nn(){
		static node n=new Node[N<<1];
		return n++;
	}
	node lst[N<<1];
	int dir,ls;
	inline bool ncmp(node a,node b){
		return a->x[dir]<b->x[dir];
	}
	int nxt[3]={1,2,0};
	void dfs(node x){
		if(x==&null){
			return;
		}
		dfs(x->lson);
		if(x->id){
			lst[++ls]=x;
		}
		dfs(x->rson);
	}
	node build(int l,int r,int d){
		if(l>r){
			return &null;
		}
		int m=(l+r)>>1;
		dir=d,nth_element(lst+l,lst+m,lst+r+1,ncmp);
		node x=lst[m];
		x->d=d;
		x->lson=build(l,m-1,nxt[d]);
		x->rson=build(m+1,r,nxt[d]);
		x->up();
		return x;
	}
	node *pt;
	inline void ins(node &x,node n,int d){
		if(x==&null){
			n->d=d;
			n->lson=n->rson=&null;
			n->up();
			x=n;
			return;
		}
		if(n->x[d]<x->x[d]){
			ins(x->lson,n,nxt[d]);
		}else{
			ins(x->rson,n,nxt[d]);
		}
		if(!x->bal()){
			pt=&x;
		}
		x->up();
	}
	inline void ins(node x){
		pt=0;
		ins(rt,x,0);
		if(pt){//rebuild
			int old=(*pt)->d;
			ls=0,dfs(*pt),*pt=build(1,ls,old);
		}
	}
	inline bool inc(ld a,ld b,ld c){
		const static double EPS=1e-5;
		return a<b+EPS&&b<c+EPS;
	}
	inline node ask(node x,node pt,ld r2){
		if(x==&null){
			return 0;
		}
		if(x->id&&isz((*x-*pt).d2()-r2)){
			return x;
		}
		const static double EPS=1e-4;
		ld far=0,near=0;
		for(int i=0;i<3;i++){
			ld tmp1=sqr(pt->x[i]-x->mn[i]),tmp2=sqr(pt->x[i]-x->mx[i]);
			far+=max(tmp1,tmp2);
			if(!inc(x->mn[i],pt->x[i],x->mx[i])){
				near+=min(tmp1,tmp2);
			}
		}
		if(far<r2-EPS||near>r2+EPS){
			return 0;
		}
		node ans=ask(x->lson,pt,r2);
		if(ans){
			return ans;
		}
		return ask(x->rson,pt,r2);
	}
}
T::node pt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ex_kcnum2.in","r",stdin);
	freopen("kcnum.out","w",stdout);
#endif
	int n=ni,tot=ni;
	faca=nd(),facb=nd();
	for(int i=1;i<=n;i++){
		T::lst[i]=pt[i]=T::nn();
		*pt[i]=(T::Node){nd(),nd(),nd()};
		pt[i]->id=i;
	}
	T::rt=T::build(1,n,0);
	while(tot--){
		if(ni){
			T::Node pt=(T::Node){parse_nd(),parse_nd(),parse_nd()};
			ld r=parse_nd();
			int id=T::ask(T::rt,&pt,r*r)->id;
			ans=id;
			printf("%d\n",id);
		}else{
			int i=parse_nd()+1e-5;
			T::node p=T::nn();
			*p=(T::Node){parse_nd(),parse_nd(),parse_nd()};
			pt[i]->id=0;
			p->id=i;
			T::ins(pt[i]=p);
		}
	}
	return 0;
}
