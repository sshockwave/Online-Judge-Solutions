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
const int N=100010;
struct SegmentTree{
	typedef SegmentTree node;
	static const int D=N*2;
	int lend,rend,mid,sum;
	node *lson,*rson;
	inline void up(){
		assert(lend!=rend);
		sum=lson->sum+rson->sum;
	}
	void build(int l,int r){
		static node *n=new node[D];
		lend=l,rend=r,mid=(l+r)>>1,sum=0;
		if(l!=r){
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	void add(int x,int v){
		assert(lend<=x&&x<=rend);
		if(lend==rend){
			sum+=v;
		}else{
			(x<=mid?lson:rson)->add(x,v);
			up();
		}
	}
	int pre(int x){
		assert(lend<=x&&x<=rend);
		if(lend==rend){
			return sum;
		}
		if(x<=mid){
			return lson->pre(x);
		}
		return rson->pre(x)+lson->sum;
	}
	int mxpre(int l,int r){
		assert(lend<=l&&r<=rend);
		if(lend==rend){
			return sum;
		}
		if(r<=mid){
			return lson->mxpre(l,r);
		}
		if(l>mid){
			return rson->mxpre(l,r)+lson->sum;
		}
		return max(lson->mxpre(l,mid),rson->mxpre(mid+1,r)+lson->sum);
	}
	//debug
	int operator [] (int i){
		if(lend==rend){
			return sum;
		}else{
			return (i<=mid?lson:rson)->operator [] (i);
		}
	}
}seg;
struct Tree{
	typedef int info[N];
	static const int E=N*2;
	int to[E],bro[E],head[N];
	Tree(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		size[0]=dep[1]=tim=0;
		top[1]=1;
	}
	inline void add_edge(int u,int v){
		static int etop=0;
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
	info top,dfn,dfe;
	int tim;
	void dfs2(int x,int f){
		dfn[x]=++tim;
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
		dfe[x]=tim;
	}
	inline int lca(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	}
	inline int ask(int u,int v){
		return seg.pre(dfn[u])+seg.pre(dfn[v])-(seg.pre(dfn[lca(u,v)])<<1)+1;
	}
	inline void alter(int x,int v){
		seg.add(dfn[x],v);
		if(dfe[x]<tim){
			seg.add(dfe[x]+1,-v);
		}
	}
}T;
struct LinkCutTree{
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int fa[N],son[N][2],side[N],top[N];
	LinkCutTree(){
		memset(side,-1,sizeof(side));
		memset(son,0,sizeof(son));
	}
	inline void up(int x){
		top[x]=lson(x)?top[lson(x)]:x;
	}
	inline void rotate(int x){
		bool d=!side[x];
		assert(~d);
		if(son[x][d]){
			fa[son[x][d]]=fa[x];
			side[son[x][d]]=!d;
		}
		son[fa[x]][!d]=son[x][d];
		side[x]=side[fa[x]];
		side[fa[x]]=d;
		son[x][d]=fa[x];
		fa[x]=fa[fa[x]];
		fa[son[x][d]]=x;
		if(~side[x]){
			son[fa[x]][side[x]]=x;
		}
		up(son[x][d]),up(x);
	}
	inline void splay(int x){
		static const int ROOT=-1;
		while(side[x]!=ROOT){
			if(side[fa[x]]==ROOT){
				rotate(x);
			}else if(side[x]==side[fa[x]]){
				rotate(fa[x]),rotate(x);
			}else{
				rotate(x),rotate(x);
			}
		}
	}
	inline void access(int x){
		splay(x);
		if(rson(x)){
			T.alter(top[rson(x)],1);
			side[rson(x)]=-1;
			rson(x)=0;
		}
		for(int f,s;splay(x),f=fa[x];x=f){
			splay(f);
			if(rson(f)){
				side[rson(f)]=-1;
				T.alter(top[rson(f)],1);
			}
			T.alter(top[x],-1);
			rson(f)=x;
			side[x]=1;
		}
	}
}lct;
int main(){
	int n=ni,tot=ni;
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T.add_edge(u,v);
		T.add_edge(v,u);
	}
	seg.build(1,n);
	T.dfs1(1,0),T.dfs2(1,0);
	for(int i=1;i<=n;i++){
		lct.fa[i]=T.fa[i];
		lct.top[i]=i;
		T.alter(i,1);
	}
	while(tot--){
		switch(ni){
			case 1:{
				lct.access(ni);
				break;
			}
			case 2:{
				printf("%d\n",T.ask(ni,ni));
				break;
			}
			case 3:{
				int x=ni;
				printf("%d\n",seg.mxpre(T.dfn[x],T.dfe[x]));
				break;
			}
		}
	}
}
