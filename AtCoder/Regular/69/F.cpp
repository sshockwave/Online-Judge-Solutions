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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=20010;
int n,cup;
int x[N],lst[N];
namespace G{
	const int N=20010*4,E=(N<<3)+N*40;//todo
	int to[E],bro[E],head[N],e,n;
	int dfn[N],low[N],bln[N],tim;
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head+1,-1,n<<2);
		memset(dfn+1,0,n<<2);
		e=tim=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int stk[N],ss=0;
	bool instk[N];
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				if(instk[v]){
					apmin(low[x],dfn[v]);
				}
			}else{
				tarjan(v);
				apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--ss];
				instk[v]=false;
				bln[v]=x;
			}while(v!=x);
		}
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int p[2];
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->p[0]=lst[l],x->p[1]=cup-lst[l];
		}else{
			x->p[0]=G::nn(),x->p[1]=G::nn();
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void putedge(node x){
		if(x->l!=x->r){
			G::ae(x->p[1],x->lson->p[1]);
			G::ae(x->lson->p[0],x->p[0]);
			G::ae(x->p[1],x->rson->p[1]);
			G::ae(x->rson->p[0],x->p[0]);
			putedge(x->lson);
			putedge(x->rson);
		}
	}
	void ae(node x,int p,int l,int r){
		if(x->l==l&&x->r==r){
			G::ae(p,x->p[1]);
			G::ae(x->p[0],cup-p);
		}else if(r<=x->m){
			ae(x->lson,p,l,r);
		}else if(x->m<l){
			ae(x->rson,p,l,r);
		}else{
			ae(x->lson,p,l,x->m);
			ae(x->rson,p,x->m+1,r);
		}
	}
}
inline bool judge(int d){
	G::init();
	seg::putedge(seg::rt);
	for(int i=1,j=i;i<cup;i++){
		for(;x[lst[i]]-x[lst[j]]>=d;j++);
		if(j<i){
			seg::ae(seg::rt,lst[i],j,i-1);
		}
	}
	for(int i=cup-1,j=i;i>=1;i--){
		for(;x[lst[j]]-x[lst[i]]>=d;j--);
		if(i<j){
			seg::ae(seg::rt,lst[i],i+1,j);
		}
	}
	for(int i=1;i<=G::n;i++){
		if(G::dfn[i]==0){
			G::tarjan(i);
		}
	}
	for(int i=1;i<cup;i++){
		if(G::bln[i]==G::bln[cup-i])return false;
	}
	for(int i=cup;i<=G::n;i++){
		if(G::bln[i]==G::bln[i+1])return false;
	}
	return true;
}
inline bool lcmp(int a,int b){
	return x[a]<x[b];
}
inline int Main(){
	n=ni,cup=(n<<1)+1;
	for(int i=1;i<=n;i++){
		x[i]=ni,x[cup-i]=ni;
	}
	for(int i=1;i<cup;i++){
		lst[i]=i;
	}
	sort(lst+1,lst+cup,lcmp);
	G::n=n<<1;
	seg::rt=seg::build(1,n<<1);
	int l=0,r=x[lst[cup-1]]-x[lst[1]];
	while(l<r){
		int m=((l+r)>>1)+1;
		if(judge(m)){
			l=m;
		}else{
			r=m-1;
		}
	}
	return l;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
