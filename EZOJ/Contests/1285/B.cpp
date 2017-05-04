#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=100010,E=N*2,D=N*2;
struct ColorSeg{
	int lc,rc,cnt;
	inline friend ColorSeg operator + (const ColorSeg &a,const ColorSeg &b){
		ColorSeg c;
		c.lc=a.lc,c.rc=b.rc,c.cnt=a.cnt+b.cnt;
		if(a.rc==b.lc){
			c.cnt--;
		}
		return c;
	}
};
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid;
	ColorSeg info;
	node *lson,*rson;
	void build(int l,int r){
		static node *n=new SegmentTree[D];
		lend=l,rend=r,mid=(l+r)>>1;
		if(l==r){
			lson=rson=0;
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	void set(int x,int c){
		assert(lend<=x&&x<=rend);
		if(lend==rend){
			info.lc=info.rc=c;
			info.cnt=1;
		}else{
			(x<=mid?lson:rson)->set(x,c);
			info=lson->info+rson->info;
		}
	}
	ColorSeg ask(int l,int r){
		assert(l<=r);
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			return info;
		}
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return lson->ask(l,mid)+rson->ask(mid+1,r);
	}
}seg;
int color[N],ccnt[N];
struct Tree{
	typedef int info[N];
	int to[E],bro[E],head[N],etop;
	Tree(){
		fa[1]=dep[1]=size[0]=etop=tim=0;
		top[1]=1;
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
	}
	inline void add_edge(int u,int v){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	int tim;
	info fa,son,size,dep,top,dfn;
	void dfs1(int x,int f){
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs1(v,x);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
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
	}
	inline int ask1(int u,int v){
		ColorSeg fromu,fromv;
		bool setu=false,setv=false;
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]]){
				if(setu){
					fromu=seg.ask(dfn[top[u]],dfn[u])+fromu;
				}else{
					setu=true;
					fromu=seg.ask(dfn[top[u]],dfn[u]);
					u=fa[top[u]];
				}
			}else{
				if(setv){
					fromv=seg.ask(dfn[top[v]],dfn[v])+fromv;
				}else{
					setv=true;
					fromv=seg.ask(dfn[top[v]],dfn[v]);
					v=fa[top[v]];
				}
			}
		}
		if(dep[u]>dep[v]){
			if(setu){
				fromu=seg.ask(dfn[v],dfn[u])+fromu;
			}else{
				setu=true;
				fromu=seg.ask(dfn[v],dfn[u]);
			}
		}else{
			if(setv){
				fromv=seg.ask(dfn[u],dfn[v])+fromv;
			}else{
				setv=true;
				fromv=seg.ask(dfn[u],dfn[v]);
			}
		}
		if(setu&&setv){
			return fromu.cnt+fromv.cnt-(fromu.lc==fromv.lc);
		}else{
			assert(setu||setv);
			if(setu){
				return fromu.cnt;
			}else{
				return fromv.cnt;
			}
		}
	}
	inline int ask2(int u,int v){
		memset(ccnt,0,sizeof(ccnt));
		while(u!=v){
			if(dep[u]>dep[v]){
				ccnt[color[u]]++;
				u=fa[u];
			}else{
				ccnt[color[v]]++;
				v=fa[v];
			}
		}
		ccnt[color[u]]++;
		int ans=0;
		for(int i=0;i<N;i++){
			apmax(ans,ccnt[i]);
		}
		return ans;
	}
}T;
int main(){
	int n=ni(),tot=ni();
	for(int i=1;i<=n;i++){
		color[i]=ni();
	}
	for(int i=1;i<n;i++){
		int u=ni(),v=ni();
		T.add_edge(u,v);
		T.add_edge(v,u);
	}
	T.dfs1(1,0),T.dfs2(1,0);
	seg.build(1,n);
	for(int i=1;i<=n;i++){
		seg.set(T.dfn[i],color[i]);
	}
	while(tot--){
		switch(ni()){
			case 1:{
				int i=ni();
				color[i]=ni();
				seg.set(T.dfn[i],color[i]);
				break;
			}
			case 2:{
				printf("%d\n",T.ask1(ni(),ni()));
				break;
			}
			case 3:{
				printf("%d\n",T.ask2(ni(),ni()));
				break;
			}
		}
	}
}
