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
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
const int N=250010,logN=20,INF=0x7f7f7f7f;
struct Tree{
	static const int E=N*2;
	int to[E],bro[E],val[E],head[N],etop;
};
struct Virtual:Tree{
	Virtual(){
		memset(tag,0,sizeof(tag));
		memset(vis,0,sizeof(vis));
		tim=0;
	}
	int tag[N],tim;
	inline void add_edge(int,int);
	int vis[N];
	lint f[N];
	void dfs(int x){
		f[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]]==tim){
				f[x]+=val[i];
			}else{
				dfs(v);
				f[x]+=min(f[v],(lint)val[i]);
			}
		}
	}
}V;
int dfn[N];
inline bool dfncmp(const int &a,const int &b){
	return dfn[a]<dfn[b];
}
struct Actual:Tree{
	int fa[N][logN],len[N][logN],dep[N],ldep[N];
	inline void reset(){
		memset(head,-1,sizeof(head));
		memset(len,127,sizeof(len));
		memset(fa,0,sizeof(fa));
		etop=tim=dep[1]=ldep[1]=0;
		dep[0]=-1;
	}
	inline void add_edge(int u,int v,int w){
		to[etop]=v;
		bro[etop]=head[u];
		val[etop]=w;
		head[u]=etop++;
	}
	int tim;
	void dfs(int x,int f){
		dfn[x]=++tim;
		fa[x][0]=f;
		for(int &j=ldep[x];fa[x][j+1]=fa[fa[x][j]][j];j++){
			len[x][j+1]=min(len[x][j],len[fa[x][j]][j]);
		}
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				dep[v]=dep[x]+1;
				len[v][0]=val[i];
				dfs(v,x);
			}
		}
	}
	inline int lca(int u,int v){
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		for(int j=ldep[u];j>=0;j--){
			if(dep[fa[u][j]]>=dep[v]){
				u=fa[u][j];
			}
		}
		if(u==v){
			return u;
		}
		for(int j=min(ldep[u],ldep[v]);j>=0;j--){
			if(fa[u][j]!=fa[v][j]){
				u=fa[u][j],v=fa[v][j];
			}
		}
		assert(fa[u][0]==fa[v][0]);
		return fa[u][0];
	}
	inline int dist(int u,int v){
		int ans=INF;
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		for(int j=ldep[u];j>=0;j--){
			if(dep[fa[u][j]]>=dep[v]){
				apmin(ans,len[u][j]);
				u=fa[u][j];
			}
		}
		if(u==v){
			return ans;
		}
		for(int j=min(ldep[u],ldep[v]);j>=0;j--){
			if(fa[u][j]!=fa[v][j]){
				apmin(ans,min(len[u][j],len[v][j]));
				u=fa[u][j],v=fa[v][j];
			}
		}
		assert(fa[u][0]==fa[v][0]);
		return ans;
	}
	int seq[N],stk[N];
	inline int work(int n){
		V.tim++;
		V.etop=0;
		for(int i=0;i<n;i++){
			V.vis[seq[i]=ni]=V.tim;
		}
		sort(seq,seq+n,dfncmp);
		int stop=0;
		stk[++stop]=1;
		for(int i=0;i<n;i++){
			int x=seq[i],f=x;
			for(int v=stk[stop];v!=f&&dep[f=lca(x,v)]<dep[v];v=stk[stop]){
				if(dep[f]>dep[stk[--stop]]){
					stk[++stop]=f;
				}
				V.add_edge(stk[stop],v);
			}
			assert(stk[stop]==f);
			assert(stk[stop]!=x);
			stk[++stop]=x;
		}
		for(;stop>1;stop--){
			V.add_edge(stk[stop-1],stk[stop]);
		}
		V.dfs(1);
		return V.f[1];
	}
}T;
inline void Virtual::add_edge(int u,int v){
	if(tag[u]<tim){
		tag[u]=tim;
		head[u]=-1;
	}
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=T.dist(u,v);
	head[u]=etop++;
}
int main(){
	T.reset();
	int n=ni;
	for(int i=1;i<n;i++){
		int u=ni,v=ni,w=ni;
		T.add_edge(u,v,w);
		T.add_edge(v,u,w);
	}
	T.dfs(1,0);
	for(int tot=ni;tot--;){
		printf("%d\n",T.work(ni));
	}
}
