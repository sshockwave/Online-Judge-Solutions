#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=100010,INF=0x7f7f7f7f;
struct Tree{
	typedef int info[N];
	static const int E=N*2;
	int to[E],bro[E],val[E],head[N],etop;
	inline void reset(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		memset(son,0,sizeof(son));
		size[0]=etop=dep[1]=len[1]=0;
		top[1]=1;
		bal[0]=INF;
	}
	inline void add_edge(int u,int v,int w){
		to[etop]=v;
		bro[etop]=head[u];
		val[etop]=w;
		head[u]=etop++;
	}
	info fa,son,size,dep,len;
	void dfs1(int x,int f){
		fa[x]=f;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				dep[v]=dep[x]+1;
				len[v]=len[x]+val[i];
				dfs1(v,x);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	info top;
	void dfs2(int x,int f){
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
	inline int lca(int u,int v){
		while(top[u]!=top[v]){
			dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]);
		}
		return dep[u]<dep[v]?u:v;
	}
	inline int dist(int u,int v){
		return len[u]+len[v]-len[lca(u,v)]*2;
	}
	info bal;
	int g;
	bool vis[N];
	void gcenter(int x,int n){
		vis[x]=true;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				gcenter(v,n);
				size[x]+=size[v];
				apmax(bal[x],size[v]);
			}
		}
		apmax(bal[x],n-size[x]);
		if(bal[x]<bal[g]){
			g=x;
		}
		vis[x]=false;
	}
	info bln;
	int solve(int x,int n){
		g=0,gcenter(x,n),x=g;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				bln[solve(v,size[v]>size[x]?n-size[x]:size[v])]=x;
			}
		}
		return x;
	}
	map<int,int>cover[N];
	inline void alter(int x,int len,int c){
		for(int v=x;v;v=bln[v]){
			int rad=len-dist(x,v);
			if(rad>=0){
				for(;!cover[v].empty()&&cover[v].begin()->first<rad;cover[v].erase(cover[v].begin()));
				cover[v][rad]=c;
			}
		}
	}
	inline int ask(int x){
		int ans=0;
		for(int v=x;v;v=bln[v]){
			int len=dist(x,v);
			map<int,int>::iterator it=cover[v].find(len);
			if(it==cover[v].end()){
				it=cover[v].upper_bound(len);
			}
			if(it!=cover[v].end()){
				apmax(ans,it->second);
			}
		}
		return ans;
	}
}T;
int color[N];
int main(){
	int n=ni;
	T.reset();
	for(int i=1;i<n;i++){
		int u=ni,v=ni,w=ni;
		T.add_edge(u,v,w);
		T.add_edge(v,u,w);
	}
	T.dfs1(1,0),T.dfs2(1,0),T.bln[T.solve(1,n)]=0;
	for(int tot=ni;tot--;){
		if(ni==1){
			static int q=0;
			int u=ni,d=ni;
			color[++q]=ni;
			T.alter(u,d,q);
		}else{
			printf("%d\n",color[T.ask(ni)]);
		}
	}
}
