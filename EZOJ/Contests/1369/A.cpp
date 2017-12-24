#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
#include <queue>
#include <vector>
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
const int N=100010;
int leaf,mxdep=0;
vector<int>vec[N];
namespace B{
	int c[N],tag[N],tim=0,n;
	inline void init(int _n){
		memset(tag+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;x+=x&-x){
			if(tag[x]<tim){
				tag[x]=tim;
				c[x]=0;
			}
			c[x]+=v;
		}
	}
	inline int sum(int x){
		int a=1;
		for(;x;x^=x&-x){
			a+=tag[x]==tim?c[x]:0;
		}
		return a;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],dfe[N],idx[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		size[0]=fa[1]=dep[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		dep[x]=dep[fa[x]]+1;
		apmax(mxdep,dep[x]);
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				if(size[son[x]]<size[v]){
					son[x]=v;
				}
			}
		}
	}
	int f[N];
	void dfs2(int x){
		idx[dfn[x]=++tim]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]){
			dfs2(son[x]);
			f[x]=f[son[x]]+1;
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					dfs2(v);
					apmin(f[x],f[v]+1);
				}
			}
			vec[f[x]].push_back(x);
		}else{
			leaf++,f[x]=0;
		}
		dfe[x]=tim;
	}
	inline int fly(int x,int n){
		assert(dep[x]>n);
		for(int d;d=dep[x]-dep[fa[top[x]]],n>=d;n-=d,x=fa[top[x]]);
		return idx[dfn[x]-n];
	}
	inline void addchain(int u,int v,int w){//u ==> v
		if(u!=1){
			B::add(dfn[fa[u]],-w);
		}
		B::add(dfn[v],w);
	}
	inline int askpoint(int x){
		return B::ask(dfn[x],dfe[x]);
	}
}
int ans[N];
struct dcmp{
	inline bool operator () (int a,int b){
		return T::dep[a]<T::dep[b];
	}
};
priority_queue<int,vector<int>,dcmp>q;
inline int getans(int len){
	for(int i=0,ti=vec[len].size();i<ti;i++){
		q.push(vec[len][i]);
	}
	int ans=0;
	B::tim++;
	while(!q.empty()){
		int x=q.top();
		q.pop();
		if(T::f[x]<len||T::askpoint(x))continue;
		ans++;
		int y=T::dep[x]>len?T::fly(x,len-1):1;
		T::addchain(y,x,1);
		if(y!=1){
			q.push(T::fa[y]);
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	B::init(n);
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	ans[1]=n;
	for(int i=2;i<=mxdep;i++){
		ans[i]=getans(i)+leaf;
	}
	for(int tot=ni;tot--;){
		printf("%d\n",ans[min(ni,mxdep)]);
	}
	return 0;
}
