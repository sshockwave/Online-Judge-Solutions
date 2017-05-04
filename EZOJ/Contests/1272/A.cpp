#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=30010,E=N*2,SHIFT=14,INF=0x7f7f7f7f,logN=16;
int pval[N];
lint ans=0;
struct Tree{
	typedef int info[N];
	int to[E],bro[E],val[E],head[N];
	info fa,son,size,dep,top,bal;
	lint len[N],all[N],sub[N],cdis[SHIFT][N],dsub[SHIFT][N];
	bool vis[N];
	int bln[N][logN],c[SHIFT][N];
	Tree(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		memset(vis,0,sizeof(vis));
		memset(bal,0,sizeof(bal));
		memset(all,0,sizeof(all));
		memset(cdis,0,sizeof(cdis));
		len[1]=0;
		top[1]=dep[1]=1;
		bal[0]=INF;
	}
	inline void add_edge(int u,int v,int w){
		static int etop=0;
		to[etop]=v;
		bro[etop]=head[u];
		val[etop]=w;
		head[u]=etop++;
	}
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
			if(dep[top[u]]>dep[top[v]]){
				u=fa[top[u]];
			}else{
				v=fa[top[v]];
			}
		}
		if(u==v){
			return u;
		}
		return dep[u]<dep[v]?u:v;
	}
	inline lint dis(int u,int v){
		return len[u]+len[v]-len[lca(u,v)]*2;
	}
	int gcenter(int x,int n){
		static int g=0;
		size[x]=1;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(!vis[v]){
				gcenter(v,n);
				apmax(bal[x],size[v]);
			}
		}
		apmax(bal[x],n-size[x]);
		if(bal[x]<bal[g]){
			g=x;
		}
		vis[x]=false;
		return g;
	}
	void dfs3(int x){
		vis[x]=true;
		for(int i=0;i<SHIFT;i++){
			c[i][x]=(pval[x]>>i)&1;
		}
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(!vis[v]){
				dfs3(v);
				size[x]+=size[v];
				all[x]+=all[v]+(lint)size[v]*val[i];
				for(int j=0;j<SHIFT;j++){
					c[j][x]+=c[j][v];
					cdis[j][x]+=cdis[j][v]+(lint)c[j][v]*val[i];
				}
			}
		}
		vis[x]=false;
	}
	int pdiv(int x,int n,int dep){
		static int stk[logN];
		stk[dep++]=x;
		x=gcenter(x,n);
		dfs3(x);
		vis[x]=true;
		if(n==1){
			memcpy(bln[x],stk,dep<<2);
		}else for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(!vis[v]){
				lint tdsub[SHIFT],tsub=all[v];
				for(int i=0;i<SHIFT;i++){
					tdsub[i]=cdis[i][v];
				}
				v=pdiv(v,size[v],dep);
				sub[v]=tsub;
				for(int i=0;i<SHIFT;i++){
					dsub[i][v]=tdsub[i];
					ans+=(tdsub[i]*((size[x]-c[i][x])-(size[v]-c[i][v])))<<i;
					ans+=((tsub-tdsub[i])*(c[i][x]-c[i][v]))<<i;
				}
			}
		}
		return x;
	}
	inline void change(int x,int v){
		int cur=pval[x],diff=cur^v,*stk=bln[x];
		for(int i=0;i<SHIFT;i++,diff>>=1){
			if(diff&1){
				int d=((v>>1)&1)-((cur>>1)&1);
				for(int j=0;stk[j]!=x;j++){
					int rt=stk[j],son=stk[j+1],dist=dis(rt,x);
					//    son's 1s' dis  other's 0s' cnt
					ans-=(dsub[i][son]*((size[rt]-c[i][rt])-(size[son]-c[i][son])))<<i;
					//    son's 0s' dis           other's 1s' cnt
					ans-=((sub[son]-dsub[i][son])*(c[i][rt]-c[i][son]))<<i;
					c[i][rt]+=d,dsub[i][son]+=d*dist;
					ans+=(dsub[i][son]*((size[rt]-c[i][rt])-(size[son]-c[i][son])))<<i;
					ans+=((sub[son]-dsub[i][son])*(c[i][rt]-c[i][son]))<<i;
				}
			}
		}
	}
}T;
int main(){
	int n=ni();
	for(int i=1;i<=n;i++){
		pval[i]=ni();
	}
	for(int i=1,u,v,w;i<n;i++){
		u=ni(),v=ni(),w=ni();
		T.add_edge(u,v,w);
		T.add_edge(v,u,w);
	}
	T.dfs1(1,0),T.dfs2(1,0);
	T.pdiv(1,n,0);
	for(int tot=ni(),x,v;tot--;){
		x=ni(),v=ni();
		T.change(x,v);
		printf("%d\n",ans);
	}
}
