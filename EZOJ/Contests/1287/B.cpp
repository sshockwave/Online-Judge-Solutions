#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int INF=0x7f7f7f7f,N=200010,M=110;
int n,m,liml,limr,ans=-INF;
int cval[N];
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid,val;
	bool tag;
	node *lson,*rson;
	inline void up(){
		assert(lend!=rend);
		val=max(lson->val,rson->val);
	}
	inline void down(){
		assert(lend!=rend);
		if(tag){
			assert(val==INF);
			lson->clear();
			rson->clear();
			tag=false;
		}
	}
	void build(int l,int r){
		static node pool[N*2],*n=pool;
		lend=l,rend=r,mid=(l+r)>>1;
		tag=false;
		if(l!=r){
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	inline void clear(){
		tag=true;
		val=-INF;
	}
	void set(int x,int v){
		assert(lend<=x&&x<=rend);
		if(lend==rend){
			tag=false;
			apmax(val,v);
		}else{
			down();
			(x<=mid?lson:rson)->set(x,v);
			up();
		}
	}
	int ask(int l,int r){
		assert(l<=r);
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			return val;
		}
		down();
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return max(lson->ask(l,mid),rson->ask(mid+1,r));
	}
}seg;
inline bool ccmp(int,int);
struct Tree{
	typedef int info[N];
	static const int E=N*2;
	int to[E],bro[E],color[E],head[N];
	Tree(){
		memset(vis,0,sizeof(vis));
		memset(head,-1,sizeof(head));
		bal[0]=INF;
	}
	inline void add_edge(int u,int v,int c){
		static int etop=0;
		to[etop]=v;
		bro[etop]=head[u];
		color[etop]=c;
		head[u]=etop++;
	}
	int g;
	bool vis[N];
	info size,bal;
	void dfs1(int x,int n){
		bal[x]=0;
		size[x]=1;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				dfs1(v,n);
				size[x]+=size[v];
				apmax(bal[x],size[v]);
			}
		}
		apmax(bal[x],n-size[x]);
		if(bal[x]>bal[g]){
			g=x;
		}
		vis[x]=false;
	}
	info dep,len,type;
	int mxdep;
	info pt;
	int pcnt;
	void dfs2(int x,int c){
		pt[pcnt++]=x;
		if(dep[x]>=liml&&dep[x]<=limr){
			apmax(ans,len[x]);
		}
		apmax(mxdep,dep[x]);
		size[x]=1;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				type[v]=type[x]?type[x]:color[i];
				len[v]=len[x];
				if(color[i]!=c){
					len[v]+=cval[color[i]];
				}
				dep[v]=dep[x]+1;
				dfs2(v,color[i]);
				size[x]+=size[v];
			}
		}
		vis[x]=false;
	}
	void dfs3(int x){
		int l=max(0,liml-dep[x]),r=min(mxdep,limr-dep[x]);
		if(l<=r){
			apmax(ans,seg.ask(l,r)+len[x]-cval[type[x]]);
		}
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				dfs3(v);
			}
		}
		vis[x]=false;
	}
	void dfs4(int x){
		seg.set(dep[x],len[x]);
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				dfs4(v);
			}
		}
		vis[x]=false;
	}
	void solve(int x,int n){
		g=0,dfs1(x,n),x=g;
		dep[x]=pcnt=len[x]=type[x]=0;
		dfs2(x,0);
		assert(pcnt==n);
		sort(pt+1,pt+n,ccmp);
		color[0]=color[1];
		int last=1;
		seg.clear();
		for(int i=1;i<n;i++){
			int x=pt[i];
			if(color[x]!=color[pt[i-1]]){
				for(;last<=i;last++){
					seg.set(dep[pt[last]],len[pt[last]]);
				}
			}
			int l=max(0,liml-dep[x]),r=min(mxdep,limr-dep[x]);
			if(l<=r){
				apmax(ans,seg.ask(l,r)+len[x]);
			}
		}
		pcnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				pt[pcnt++]=v;
			}
		}
		sort(pt,pt+pcnt,ccmp);
		for(int i=0;i<pcnt;i++){
			int x=pt[i];
			if(color[x]==color[pt[i-1]]){
				dfs3(x),dfs4(x);
			}else{
				seg.clear();
			}
		}
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				solve(v,size[v]);
			}
		}
	}
}T;
inline bool ccmp(int a,int b){
	return T.type[a]<T.type[b];
}
int main(){
	n=ni,m=ni,liml=ni,limr=ni;
	for(int i=1;i<=n;i++){
		cval[i]=ni;
	}
	for(int i=1;i<n;i++){
		int u=ni,v=ni,c=ni;
		T.add_edge(u,v,c);
		T.add_edge(v,u,c);
	}
	T.solve(1,n);
	printf("%d\n",ans);
}
