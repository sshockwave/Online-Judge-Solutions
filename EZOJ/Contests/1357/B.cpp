#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=200010,INF=0x7f7f7f7f;
int a[N];
inline int pamin(int x,int y){
	return x==-1?y:y==-1?x:a[x]<a[y]?x:y;
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int val[2];
		inline void up(){
			val[0]=pamin(lson->val[0],rson->val[0]);
			val[1]=pamin(lson->val[1],rson->val[1]);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->val[l&1]=l;
			x->val[!(l&1)]=-1;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	int ask(node x,int l,int r,bool d){
		if(x->l==l&&x->r==r){
			return x->val[d];
		}
		if(r<=x->m){
			return ask(x->lson,l,r,d);
		}
		if(l>x->m){
			return ask(x->rson,l,r,d);
		}
		return pamin(ask(x->lson,l,x->m,d),ask(x->rson,x->m+1,r,d));
	}
}
int iteml[N],itemr[N],items=0;
namespace G{
	const int E=N+(N>>1);
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		if(~v){
			to[e]=v,bro[e]=head[u],head[u]=e++;
		}
	}
	struct icmp{
		inline bool operator () (const int &x,const int &y){
			return a[iteml[x]]!=a[iteml[y]]?a[iteml[x]]>a[iteml[y]]:a[itemr[x]]>a[itemr[y]];
		}
	};
	void bfs(int s){//+output
		priority_queue<int,vector<int>,icmp>q;
		q.push(s);
		while(!q.empty()){
			int x=q.top();
			q.pop();
			printf("%d %d ",a[iteml[x]],a[itemr[x]]);
			for(int i=head[x];~i;i=bro[i]){
				q.push(to[i]);
			}
		}
	}
}
int solve(int l,int r){
	if(l>r){
		return -1;
	}
	assert((l&1)!=(r&1));
	int x=++items;
	iteml[x]=seg::ask(seg::rt,l,r,l&1);
	itemr[x]=seg::ask(seg::rt,iteml[x]+1,r,!(l&1));
	G::ae(x,solve(l,iteml[x]-1));
	G::ae(x,solve(iteml[x]+1,itemr[x]-1));
	G::ae(x,solve(itemr[x]+1,r));
	return x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("parlor.in","r",stdin);
	freopen("parlor.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	seg::rt=seg::build(1,n);
	G::init();
	int s=solve(1,n);
	assert(items==(n>>1));
	G::bfs(s);
	putchar('\n');
	return 0;
}
