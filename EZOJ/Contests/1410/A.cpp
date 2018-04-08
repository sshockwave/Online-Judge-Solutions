#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=100010;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,mx,dt;
		inline void addv(int v){
			mn+=v,mx+=v,dt+=v;
		}
		inline void down(){
			if(dt){
				lson->addv(dt);
				rson->addv(dt);
				dt=0;
			}
		}
		inline void up(){
			mn=min(lson->mn,rson->mn);
			mx=max(lson->mx,rson->mx);
		}
	};
	node build(int l,int r){
		static node n=new Node[N];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->mn=x->mx=x->dt=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	int ask(node x,int p){
		if(x->l==x->r)return x->mn;
		x->down();
		return ask(p<=x->m?x->lson:x->rson,p);
	}
	void add(node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->addv(v);
		x->down();
		if(r<=x->m){
			add(x->lson,l,r,v);
		}else if(l>x->m){
			add(x->rson,l,r,v);
		}else{
			add(x->lson,l,x->m,v);
			add(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	int find_fir(node x,int l,int dt){//find fir <= 0
		if(x->mn+dt>0)return x->r+1;
		if(x->l==x->r)return l;
		x->down();
		if(l>x->m)return find_fir(x->rson,l,dt);
		int ans=find_fir(x->lson,l,dt);
		return ans<=x->m?ans:find_fir(x->rson,x->m+1,dt);
	}
	int find_las(node x){//find las =0 returns end+i
		if(x->mx==0)return 0;
		if(x->l==x->r)return x->mx+x->l;
		x->down();
		return find_las(x->rson->mx?x->rson:x->lson);
	}
}
int dep[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ant.in","r",stdin);
	freopen("ant.out","w",stdout);
#endif
	int n=ni,tot=ni,mx=dep[1]=0;
	for(int i=2;i<=n;i++){
		apmax(mx,dep[i]=dep[ni]+1);
	}
	seg::node rt=seg::build(0,mx);
	while(tot--){
		int op=3-(ni<<1),x=dep[ni];
		if(x){
			seg::add(rt,x,min(seg::find_fir(rt,x,min(op,0)),mx),op);
		}
		printf("%d\n",seg::find_las(rt));
	}
	return 0;
}
