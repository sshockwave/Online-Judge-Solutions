#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int INF=0x7f7f7f7f,N=10010,E=N*2;
struct Edge{
	int u,v,w;
}e[N];
int pos[N];
struct SegmentTree{
	typedef SegmentTree node;
	static const int D=N*2;
	int lend,rend,mid,val;
	node *lson,*rson;
	static node *n;
	inline void reset(){
		static node *pool=new node[D];
		n=pool;
	}
	inline void up(){
		assert(lend!=rend);
		val=max(lson->val,rson->val);
	}
	void build(int l,int r){
		lend=l,rend=r,mid=(l+r)>>1;
		if(l!=r){
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	void set(int x,int v){
		if(lend==rend){
			val=v;
		}else{
			(x<=mid?lson:rson)->set(x,v);
			up();
		}
	}
	int ask(int l,int r){
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			return val;
		}
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return max(lson->ask(l,mid),rson->ask(mid+1,r));
	}
}seg;
SegmentTree* SegmentTree::n;
struct Tree{
	typedef int info[N];
	int to[E],bro[E],head[N];
	inline void reset(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		tim=size[0]=con[1]=dep[1]=0;
		top[1]=1;
	}
	inline void add_edge(int eid,int u,int v){
		to[eid]=v;
		bro[eid]=head[u];
		head[u]=eid;
	}
	info fa,son,size,dep,con;
	void dfs1(int x,int f){
		fa[x]=f;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				dep[v]=dep[x]+1;
				con[v]=i>>1;
				dfs1(v,x);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	info top;
	int tim;
	void dfs2(int x,int f){
		pos[con[x]]=tim++;
		if(son[x]){
			top[son[x]]=top[x];
			dfs2(son[x],x);
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(v!=f&&v!=son[x]){
					top[v]=v;
					dfs2(v,x);
				}
			}
		}
	}
	int ask(int u,int v){
		int ans=-INF;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
			apmax(ans,seg.ask(pos[con[top[u]]],pos[con[u]]));
			u=fa[top[u]];
		}
		if(u==v){
			return ans;
		}
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		return max(ans,seg.ask(pos[con[v]]+1,pos[con[u]]));
	}
}T;
int main(){
	for(int tot=ni;tot--;){
		T.reset(),seg.reset();
		int n=ni;
		for(int i=1;i<n;i++){
			e[i]=(Edge){ni,ni,ni};
			T.add_edge(i<<1,e[i].u,e[i].v);
			T.add_edge((i<<1)|1,e[i].v,e[i].u);
		}
		seg.build(1,n-1);
		T.dfs1(1,0),T.dfs2(1,0);
		for(int i=1;i<n;i++){
			seg.set(pos[i],e[i].w);
		}
		char op[10];
		while(scanf("%s",op),op[0]!='D'){
			if(op[0]=='C'){
				int eid=ni;
				seg.set(pos[eid],ni);
			}else{
				printf("%d\n",T.ask(ni,ni));
			}
		}
	}
}
