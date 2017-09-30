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
	const static double EPS=1e-5;
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
		ld x[3];
		node lson,rson;
		int d,size,id;
		inline void up(){
			size=lson->size+rson->size+1;
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
	}*rt,null=(Node){0,0,0,0,0,0,0,0};
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
			n->size=1;
			n->lson=n->rson=&null;
			x=n;
			return;
		}
		if(n->x[d]<x->x[d]){
			ins(x->lson,n,nxt[d]);
		}else{
			ins(x->rson,n,nxt[d]);
		}
		x->size++;
		if(!x->bal()){
			pt=&x;
		}
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
		return a<=b&&b<=c;
	}
	inline node ask(node x,node pt,ld r2,node lb,node ub){
		if(x==&null){
			return 0;
		}
		if(x->id&&isz((*x-*pt).d2()-r2)){
			return x;
		}
		//validity check
		const static ld EPS=1e-8;
		double x0=sqr(pt->x[0]-lb->x[0]),x1=sqr(pt->x[0]-ub->x[0]);
		double y0=sqr(pt->x[1]-lb->x[1]),y1=sqr(pt->x[1]-ub->x[1]);
		double z0=sqr(pt->x[2]-lb->x[2]),z1=sqr(pt->x[2]-ub->x[2]);
		if(max(x0,x1)+max(y0,y1)+max(z0,z1)<r2-EPS){
			return 0;
		}
		if(min(x0,x1)+min(y0,y1)+min(z0,z1)>r2+EPS&&
				!inc(lb->x[0],pt->x[0],ub->x[0])&&
				!inc(lb->x[1],pt->x[1],ub->x[1])&&
				!inc(lb->x[2],pt->x[2],ub->x[2])){
			return 0;
		}
		bool flag=sqr(x->x[x->d]-pt->x[x->d])<r2+EPS;
		bool side=pt->x[x->d]>x->x[x->d];
		if(!side||flag){
			ld oldVal=ub->x[x->d];
			ub->x[x->d]=x->x[x->d];
			node ans=ask(x->lson,pt,r2,lb,ub);
			ub->x[x->d]=oldVal;
			if(ans){
				return ans;
			}
		}
		if(side||flag){
			ld oldVal=lb->x[x->d];
			lb->x[x->d]=x->x[x->d];
			node ans=ask(x->rson,pt,r2,lb,ub);
			lb->x[x->d]=oldVal;
			if(ans){
				return ans;
			}
		}
		return 0;
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
			static T::Node lb=(T::Node){-N,-N,-N},ub=(T::Node){N,N,N};
			int id=T::ask(T::rt,&pt,r*r,&lb,&ub)->id;
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
