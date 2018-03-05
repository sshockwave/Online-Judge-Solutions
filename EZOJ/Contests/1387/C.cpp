#include <iostream>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=200010;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N],dfn[N],idx[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		fa[1]=son[0]=size[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		son[x]=0,size[x]=1,dep[x]=dep[fa[x]]+1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	void dfs2(int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		idx[dfn[x]=++tim]=x;
		if(son[x]==0)return;
		dfs2(son[x]);
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]&&v!=son[x]){
				dfs2(v);
			}
		}
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline int dist(int u,int v){
		return dep[u]+dep[v]-(dep[lca(u,v)]<<1);
	}
	inline int fly(int x,int n){
		for(int d;d=dep[x]-dep[fa[top[x]]],d<=n;n-=d,x=fa[top[x]]);
		return idx[dfn[x]-n];
	}
	struct diam{
		int u,v,d;
		inline void calc(){
			d=dist(u,v);
		}
		inline int eval(int x){
			return max(dist(u,x),dist(v,x));
		}
		inline friend bool operator < (const diam &a,const diam &b){
			return a.d<b.d;
		}
		inline friend bool operator == (const diam &a,const diam &b){
			return (a.u==b.u&&a.v==b.v)||(a.u==b.v&&a.v==b.u);
		}
		inline friend bool operator != (const diam &a,const diam &b){
			return !(a==b);
		}
	}f[E];
	int far[E];
	int con[N];
	void dfs3(int x,int e){
		con[x]=e;
		f[e]=(diam){x,x,0};
		far[e]=x;
		int far2=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				dfs3(v,i);
				apmax(f[e],f[i]);
				if(dep[far[i]]>dep[far[e]]){
					far2=far[e],far[e]=far[i];
				}else if(dep[far[i]]>dep[far2]){
					far2=far[i];
				}
			}
		}
		apmax(f[e],(diam){far[e],far2,dep[far[e]]+dep[far2]-(dep[x]<<1)});
	}
	void dfs4(int x){
		int far1=x,far2=x,far3=x;
		int vf1=0,vf2=0,vf3=0;
		diam f1=(diam){x,x,0},f2=(diam){x,x,0};
		for(int i=head[x];~i;i=bro[i]){
			int curv=dist(x,far[i]);
			if(curv>vf1){
				far3=far2,far2=far1,far1=far[i];
				vf3=vf2,vf2=vf1,vf1=curv;
			}else if(curv>vf2){
				far3=far2,far2=far[i];
				vf3=vf2,vf2=curv;
			}else if(curv>vf3){
				far3=far[i];
				vf3=curv;
			}
			if(f1<f[i]){
				f2=f1,f1=f[i];
			}else if(f2<f[i]){
				f2=f[i];
			}
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				far[i^1]=far1!=far[i]?far1:far2;
				f[i^1]=far1==far[i]?(diam){far2,far3}:far2==far[i]?(diam){far1,far3}:(diam){far1,far2};
				f[i^1].calc();
				apmax(f[i^1],f1!=f[i]?f1:f2);
				dfs4(v);
			}
		}
	}
}
inline bool chase(int u,int v,int len1,int len2){
	using namespace T;
	int w=lca(u,v),d=dep[u]+dep[v]-(dep[w]<<1);
	assert(w);
	if(d<=len1)return true;
	int e;
	if(len1<dep[u]-dep[w]){
		e=con[fly(u,len1)]^1;
	}else{
		e=con[fly(v,(dep[v]-dep[w])-(len1-(dep[u]-dep[w]))-1)];
	}
	return f[e].eval(v)<len2;
}
inline int Main(){
	int a=ni,b=ni,k=ni;
	int d=T::dist(a,b);
	if(d>k)return k&1;
	if(k&1){
		if(d&1)return chase(a,b,(k+1)>>1,(k-1)>>1)?2:1;
		else return 1;
	}else{
		if(d&1)return 0;
		else return chase(b,a,k>>1,k>>1)?-1:0;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("alice.in","r",stdin);
	freopen("alice.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1),T::dfs3(1,T::e),T::dfs4(1);
	while(tot--){
		printf("%d\n",Main());
	}
	return 0;
}
