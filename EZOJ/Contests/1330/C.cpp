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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=100010;
struct Pt{
	int x,y,t;
}pt[N<<1];
int n,m,ps=0;
int ans[N];
inline bool xcmp(const Pt &a,const Pt &b){
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
inline bool ycmp(const Pt &a,const Pt &b){
	return a.y!=b.y?a.y<b.y:a.x<b.x;
}
namespace seg{
	struct Node;
	typedef Node* node;
	int tim=0;
	struct Node{
		int l,m,r;
		node lson,rson;
		int tag,mx;
		lint sum,diff;
		inline lint all(lint val){
			return val*(r-l+1);
		}
		inline void renew(){
			if(tag!=tim){
				mx=sum=diff=0,tag=tim;
			}
		}
		inline void up();
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->tag=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	lint ask(node x,lint val){
		x->renew();
		if(x->mx<=val){
			return x->all(val);
		}
		if(x->l==x->r){
			return x->mx;
		}
		if(val>=x->rson->mx){
			return ask(x->lson,val)+x->rson->all(val);
		}else{
			return x->lson->sum+x->diff+ask(x->rson,val);
		}
	}
	lint val;
	lint ask(node x,int l,int r){
		x->renew();
		if(x->l==l&&x->r==r){
			lint ans=ask(x,val);
			apmax(val,x->mx);
			return ans;
		}
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		lint ans=ask(x->rson,x->m+1,r);
		ans+=ask(x->lson,l,x->m);
		return ans;
	}
	inline void Node::up(){
		lson->renew(),rson->renew();
		mx=max(lson->mx,rson->mx);
		sum=ask(lson,rson->mx);
		diff=sum-lson->sum;
		sum+=rson->sum;
		tag=tim;
	}
	void set(node x,int p,int v){
		if(x->l==x->r){
			x->mx=v;
			x->tag=tim;
		}else{
			set(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
}
inline void work(bool flag){
	seg::tim++;
	sort(pt,pt+ps,ycmp);
	for(int i=0;i<ps;i++){
		if(pt[i].t==-1){
			seg::set(seg::rt,pt[i].x,pt[i].y);
		}else{
			seg::val=0;
			seg::val=0;
			ans[pt[i].t]+=(lint)pt[i].x*pt[i].y-seg::ask(seg::rt,1,pt[i].x);
		}
	}
	if(flag){
		for(int i=0,x,y=0;i<ps;i++){
			if(pt[i].y!=y){
				x=0,y=pt[i].y;
			}
			if(pt[i].t==-1){
				x=pt[i].x;
			}else{
				ans[pt[i].t]-=pt[i].x-x;
			}
		}
		sort(pt,pt+ps,xcmp);
		for(int i=0,x=0,y;i<ps;i++){
			if(pt[i].x!=x){
				x=pt[i].x,y=0;
			}
			if(pt[i].t==-1){
				y=pt[i].y;
			}else{
				ans[pt[i].t]-=pt[i].y-y;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
#endif
	n=ni,m=ni;
	int tot1=ni,tot2=ni;
	while(tot1--){
		pt[ps++]=(Pt){ni,ni,-1};
	}
	for(int i=1;i<=tot2;i++){
		pt[ps++]=(Pt){ni,ni,i};
	}
	seg::rt=seg::build(1,n);
	work(true);
	for(int i=0;i<ps;i++){
		pt[i].y=m+1-pt[i].y;
	}
	work(false);
	for(int i=0;i<ps;i++){
		pt[i].x=n+1-pt[i].x;
	}
	work(true);
	for(int i=0;i<ps;i++){
		pt[i].y=m+1-pt[i].y;
	}
	work(false);
	for(int i=1;i<=tot2;i++){
		printf("%d\n",ans[i]+1);
	}
	return 0;
}
