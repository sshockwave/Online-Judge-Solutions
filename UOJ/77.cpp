#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=5010,D=73000,E=D*4,INF=0x7f7f7f7f;
int ntop;
struct Graph{
	int to[E],cap[E],bro[E],head[D];
	Graph(){
		memset(head,-1,sizeof(head));
	}
	inline void add_edge(int u,int v,int c){
		static int etop=0;
		to[etop]=v;
		cap[etop]=c;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	int s,t;
	inline void add(int u,int v,int c){
		add_edge(u,v,c);
		add_edge(v,u,0);
	}
	int dis[D],que[D];
	inline bool bfs(){
		memset(dis,-1,ntop<<1);
		int qhead=0,qtail=0;
		dis[s]=0;
		que[qtail++]=s;
		while(qhead<qtail){
			int x=que[qhead++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==-1){
					dis[v]=dis[x]+1;
					if(v==t){
						return true;
					}
					que[qtail++]=v;
				}
			}
		}
		return false;
	}
	int aug(int x,int alloc){
		if(x==t){
			return alloc;
		}
		int rest=alloc,delta;
		for(int i=head[x],v;(~i)&&rest;i=bro[i]){
			v=to[i];
			if(cap[i]&&dis[v]==dis[x]+1){
				delta=aug(v,min(rest,cap[i]));
				cap[i]-=delta,cap[i^1]+=delta;
				rest-=delta;
			}
		}
		if(rest){
			dis[x]=-1;
		}
		return alloc-rest;
	}
	inline int dinic(){
		int flow=0;
		while(bfs()){
			flow+=aug(s,INF);
		}
		return flow;
	}
}G;
struct SegmentTree{
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int son[D][2];
	SegmentTree(){
		memset(son,-1,sizeof(son));
	}
	inline int renew(int x){
		if(~x){
			G.add(x,ntop,INF);
			lson(ntop)=lson(x),rson(ntop)=rson(x);
		}
		return ntop++;
	}
	int put(int x,int p,int node,int l,int r){
		assert(l<=p&&p<=r);
		if(l==r){
			if(~x){
				G.add(x,node,INF);
			}
			return node;
		}
		if(~x){
			G.add(x,ntop,INF);
			lson(ntop)=lson(x),rson(ntop)=rson(x);
		}
		x=ntop++;
		int mid=(l+r)>>1;
		if(p<=mid){
			G.add(lson(x)=put(lson(x),p,node,l,mid),x,INF);
		}else{
			G.add(rson(x)=put(rson(x),p,node,mid+1,r),x,INF);
		}
		return x;
	}
	void ask(int x,int node,int lend,int rend,int l,int r){
		assert(l<=r);
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			G.add(x,node,INF);
			return;
		}
		int mid=(lend+rend)>>1;
		if(r<=mid){
			ask(lson(x),node,lend,mid,l,r);
		}else if(l>mid){
			ask(rson(x),node,mid+1,rend,l,r);
		}else{
			ask(lson(x),node,lend,mid,l,mid);
			ask(rson(x),node,mid+1,rend,mid+1,r);
		}
	}
}seg;
struct Info{
	int a,b,w,l,r,p;
}info[N];
int *vals[N];
inline bool valcmp(int *a,int *b){
	return (*a)<(*b);
}
inline int putval(int n){
	int p=1;
	for(int i=0,l1=INF,l2;i<n;i++){
		l2=*vals[i];
		(*vals[i])=l1==l2?p:++p;
		l1=l2;
	}
	return p;
}
int main(){
	int n=ni(),vtop=0;
	for(int i=1;i<=n;i++){
		info[i]=(Info){ni(),ni(),ni(),ni(),ni(),ni()};
		vals[vtop++]=&info[i].a;
		vals[vtop++]=&info[i].l;
		vals[vtop++]=&info[i].r;
	}
	sort(vals,vals+vtop,valcmp);
	int mx=putval(vtop);
	G.s=0,G.t=(n<<1)|1,ntop=(n+1)<<1;
	int ans=0,root=-1;
	for(int i=1;i<=n;i++){
		ans+=info[i].w+info[i].b;
		G.add(G.s,i,info[i].w);
		G.add(i,G.t,info[i].b);
		G.add(i+n,i,info[i].p);
		seg.ask(root,i+n,1,mx,info[i].l,info[i].r);
		root=seg.put(root,info[i].a,i,1,mx);
	}
	printf("%d\n",ans-G.dinic());
}
