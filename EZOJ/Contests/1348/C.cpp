#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
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
const int N=30010,INF=0x7f7f7f7f;
namespace B{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=x&-x);
		return ans;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
int gx,gy;
struct SegTree{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int x,y,px,py,dx,dy;
		inline void reset(){
			x=y=-INF,px=py=l,dx=0,dy=0;
		}
		inline void down(){
			if(dx){
				lson->x+=dx,lson->dx+=dx;
				rson->x+=dx,rson->dx+=dx;
				dx=0;
			}
			if(dy){
				lson->y+=dy,lson->dy+=dy;
				rson->y+=dy,rson->dy+=dy;
				dy=0;
			}
		}
		inline void up(){
			if(lson->x>rson->x){
				x=lson->x,px=lson->px;
			}else{
				x=rson->x,px=rson->px;
			}
			if(lson->y>rson->y){
				y=lson->y,py=lson->py;
			}else{
				y=rson->y,py=rson->py;
			}
		}
	}pool[N<<1],*n,*rt;
	node build(int l,int r){
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->reset();
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	inline void init(int _n){
		n=pool;
		rt=build(1,_n);
	}
	void ins(node x,int p,int vx,int vy){
		if(x->l==x->r){
			x->x=vx,x->y=vy;
		}else{
			x->down();
			ins(p<=x->m?x->lson:x->rson,p,vx,vy);
			x->up();
		}
	}
	void del(node x,int p){
		if(x->l==x->r){
			gx=x->x,gy=x->y;
			x->reset();
		}else{
			x->down();
			del(p<=x->m?x->lson:x->rson,p);
			x->up();
		}
	}
	void add(node x,int l,int r,int op,int v){
		if(x->l==l&&x->r==r){
			(op==1?x->x:x->y)+=v;
			(op==1?x->dx:x->dy)+=v;
			return;
		}
		x->down();
		if(r<=x->m){
			add(x->lson,l,r,op,v);
		}else if(l>x->m){
			add(x->rson,l,r,op,v);
		}else{
			add(x->lson,l,x->m,op,v);
			add(x->rson,x->m+1,r,op,v);
		}
		x->up();
	}
}seg[2][2];
int x1,y1,x2,y2;
inline void putpt(int p,int x,int y){
	if(x<x2&&y<y2){
		seg[x>=x1][y>=y1].ins(seg[x>=x1][y>=y1].rt,p,x,y);
		if(x>=x1&&y>=y1){
			B::add(p,1);
		}
	}
}
vector<int>plst,xlst,ylst;
inline void addval(SegTree &seg,int op,int l,int r,int d,int lim,bool flag=false){
	seg.add(seg.rt,l,r,op,d);
	int &cur=op==1?seg.rt->x:seg.rt->y;
	int &curp=op==1?seg.rt->px:seg.rt->py;
	while(cur>=lim){
		int tmp=curp;
		if(flag){
			B::add(tmp,-1);
		}
		seg.del(seg.rt,tmp);
		plst.push_back(tmp);
		xlst.push_back(gx);
		ylst.push_back(gy);
	}
}
inline void Main(){
	int n=ni;
	x1=ni,y1=ni,x2=ni+1,y2=ni+1;
	B::init(n);
	seg[0][0].init(n);
	seg[1][0].init(n);
	seg[0][1].init(n);
	seg[1][1].init(n);
	for(int i=1,x,y;i<=n;x=ni,y=ni,putpt(i,x,y),i++);
	for(int tot=ni;tot--;){
		int op=ni,l=ni,r=ni;
		if(op==3){
			printf("%d\n",B::ask(l,r));
		}else{
			int d=ni;
			plst.clear(),xlst.clear(),ylst.clear();
			addval(seg[0][0],op,l,r,d,op==1?x1:y1);
			addval(seg[0][1],op,l,r,d,op==1?x1:y2);
			addval(seg[1][0],op,l,r,d,op==1?x2:y1);
			addval(seg[1][1],op,l,r,d,op==1?x2:y2,true);
			for(int i=0,n=plst.size();i<n;i++){
				putpt(plst[i],xlst[i],ylst[i]);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fish.in","r",stdin);
	freopen("fish.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
