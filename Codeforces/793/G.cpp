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
const int N=10010,INF=0x7f7f7f7f;
namespace G{
	const int N=10010*60,E=N*5;
	int to[E],bro[E],cap[E],head[N],e=0,n=0,s,t;
	bool upd[N];
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(upd,0,sizeof(upd));
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],tag[N],tim=0;
	int que[N];
	inline void bfs(){
		tim++;
		int qh=0,qt=0;
		tag[t]=tim,dis[t]=0,que[qt++]=t;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i^1]&&tag[v=to[i]]<tim){
					tag[v]=tim,dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t){
			return a;
		}
		int r=a,d;
		for(int i=head[x],v;r&&~i;i=bro[i]){
			if(cap[i]&&tag[v=to[i]]==tim&&dis[v]==dis[x]-1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		if(r){
			tag[x]=0;
		}
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),tag[s]==tim;flow+=aug(s,INF));
		return flow;
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	int tim=0;
	struct Node{
		int l,m,r;
		node lson,rson;
		int tag,cur,bak;
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->tag=0,x->cur=x->bak=G::nn();
		G::upd[x->cur]=true;
		if(l==r){
			G::add(x->cur,G::t,1);
		}else{
			G::add(x->cur,(x->lson=build(l,x->m))->cur,INF);
			G::add(x->cur,(x->rson=build(x->m+1,r))->cur,INF);
		}
		return x;
	}
	void enable(node x,int l,int r){
		if(x->cur==x->bak){
			return;
		}
		if(x->l==l&&x->r==r){
			x->cur=x->bak;
			x->tag=tim-1;
			return;
		}
		if(r<=x->m){
			enable(x->lson,l,r);
		}else if(l>x->m){
			enable(x->rson,l,r);
		}else{
			enable(x->lson,l,x->m);
			enable(x->rson,x->m+1,r);
		}
		if(x->lson->cur==x->lson->bak&&x->rson->cur==x->rson->bak){
			x->cur=x->bak;
			x->tag=tim-1;
		}else if(x->lson->cur==0||x->rson->cur==0){
			x->cur=x->lson->cur|x->rson->cur;
			x->tag=tim-1;
		}else if(x->tag!=tim){
			x->cur=G::nn();
			x->tag=tim;
		}
	}
	void disable(node x,int l,int r){
		if(x->cur==0){
			return;
		}
		if(x->l==l&&x->r==r){
			x->cur=0;
			x->tag=tim-1;
			return;
		}
		if(r<=x->m){
			disable(x->lson,l,r);
		}else if(l>x->m){
			disable(x->rson,l,r);
		}else{
			disable(x->lson,l,x->m);
			disable(x->rson,x->m+1,r);
		}
		if(x->lson->cur==0||x->rson->cur==0){
			x->cur=x->lson->cur|x->rson->cur;
			x->tag=tim-1;
		}else if(x->tag!=tim){
			x->cur=G::nn();
			x->tag=tim;
		}
	}
	void addedge(node x){
		assert(x->cur);
		if(G::upd[x->cur]){
			return;
		}
		if(x->cur==x->lson->cur){
			addedge(x->lson);
			return;
		}
		if(x->cur==x->rson->cur){
			addedge(x->rson);
			return;
		}
		G::upd[x->cur]=true;
		if(x->lson->cur){
			G::add(x->cur,x->lson->cur,INF);
			addedge(x->lson);
		}
		if(x->rson->cur){
			G::add(x->cur,x->rson->cur,INF);
			addedge(x->rson);
		}
	}
}
struct Event{
	int x,l,r,tp;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.x!=b.x?a.x<b.x:a.tp<b.tp;
	}
	inline void apply(){
		if(tp==1){
			seg::disable(seg::rt,l,r);
		}else{
			seg::enable(seg::rt,l,r);
		}
	}
}ev[N<<1];
int es=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
#endif
	int n=ni,tot=ni;
	G::init(),seg::rt=seg::build(1,n);
	while(tot--){
		int x1=ni,y1=ni,x2=ni,y2=ni;
		ev[es++]=(Event){x1,y1,y2,1};
		if(x2<n){
			ev[es++]=(Event){x2+1,y1,y2,-1};
		}
	}
	sort(ev,ev+es);
	int x=1;
	for(int i=0;i<es;){
		using namespace seg;
		if(x!=ev[i].x){
			if(rt->cur){
				G::add(G::s,rt->cur,ev[i].x-x);
			}
			x=ev[i].x;
		}
		tim++;
		for(;i<es&&ev[i].x==x;ev[i].apply(),i++);
		if(rt->cur){
			addedge(rt);
		}
	}
	if(seg::rt->cur){
		G::add(G::s,seg::rt->cur,n+1-x);
	}
	printf("%d\n",G::dinic());
	return 0;
}
