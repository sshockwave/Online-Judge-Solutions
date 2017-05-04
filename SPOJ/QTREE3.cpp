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
inline void apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
const int N=100010,INF=0x7f7f7f7f;
struct SegmentTree{
	static const int D=N*2;
	typedef SegmentTree node;
	int lend,rend,mid,val;
	node *lson,*rson;
	inline void up(){
		assert(lend!=rend);
		val=min(lson->val,rson->val);
	}
	void build(int l,int r){
		static node *n=new node[D];
		lend=l,rend=r,mid=(l+r)>>1;
		val=INF;
		if(l!=r){
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	void toggle(int x){
		assert(lend<=x&&x<=rend);
		if(lend==rend){
			val^=lend^INF;
		}else{
			(x<=mid?lson:rson)->toggle(x);
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
		return min(lson->ask(l,mid),rson->ask(mid+1,r));
	}
}seg;
struct Tree{
	typedef int info[N];
	static const int E=N*2;
	int to[E],bro[E],head[N],etop;
	inline void reset(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		tim=fa[1]=etop=size[0]=dep[1]=0;
		top[1]=1;
	}
	inline void add_edge(int u,int v){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	info fa,son,size,dep;
	void dfs1(int x,int f){
		fa[x]=f;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				dep[v]=dep[x]+1;
				dfs1(v,x);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	info top,dfn,id;
	int tim;
	void dfs2(int x,int f){
		id[dfn[x]=++tim]=x;
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
	inline int ask(int x){
		int ans=INF;
		while(top[x]!=1){
			apmin(ans,seg.ask(dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		assert(dfn[1]==1);
		return min(ans,seg.ask(1,dfn[x]));
	}
}T;
int main(){
	T.reset();
	int n=ni,tot=ni;
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T.add_edge(u,v);
		T.add_edge(v,u);
	}
	T.dfs1(1,0),T.dfs2(1,0);
	seg.build(1,n);
	while(tot--){
		if(ni){
			int ans=T.ask(ni);
			printf("%d\n",ans==INF?-1:T.id[ans]);
		}else{
			seg.toggle(T.dfn[ni]);
		}
	}
}
