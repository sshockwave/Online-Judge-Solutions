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
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=50010;
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e;
	inline void init(){
		e=0;
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int len[N];
	void dfs(int x){
		len[x]+=x;
		for(int i=head[x];~i;i=bro[i]){
			len[to[i]]=len[x];
			dfs(to[i]);
		}
	}
}
namespace G{
	const int E=200010;
	int to[E],bro[E],head[N],e;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dfn[N],id[N],tim;
	void dfs(int x){
		id[dfn[x]=++tim]=x;
		for(int i=head[x];~i;i=bro[i]){
			if((i&1)==0&&dfn[to[i]]==0){
				dfs(to[i]);
			}
		}
	}
	int fa[N],val[N];
	int root(int x){
		if(fa[x]==0){
			return x;
		}
		int rt=root(fa[x]);
		apmin(val[x],val[fa[x]]);
		return fa[x]=rt;
	}
	inline int mindfn(const int &a,const int &b){
		return dfn[a]<dfn[b]?a:b;
	}
	inline void apdfn(int &a,const int &b){
		if(dfn[b]<dfn[a]){
			a=b;
		}
	}
	inline int eval(int x){
		if(fa[x]==0){
			return val[x];
		}
		root(x);
		return mindfn(val[x],val[fa[x]]);
	}
	int idom[N],sdom[N];
	namespace B{
		int to[N],bro[N],head[N],e;
		inline void init(){
			memset(head,-1,sizeof(head));
			e=0;
		}
		inline void ae(int u,int v){
			to[e]=v,bro[e]=head[u],head[u]=e++;
		}
		inline void deal(int x){
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				int u=eval(v);
				idom[v]=sdom[u]==sdom[v]?sdom[v]:u;
			}
		}
	}
	inline void work(int n){
		dfs(n);
		memset(fa+1,0,n<<2);
		for(int i=1;i<=n;i++){
			sdom[i]=val[i]=i;
		}
		for(int p=n;p>=1;p--){//get sdom
			int x=id[p];
			B::deal(x);
			for(int i=head[x],v;~i;i=bro[i]){
				if(i&1){
					v=to[i];
					apdfn(sdom[x],eval(v));
				}else if(dfn[v]>dfn[x]){
					assert(fa[v]==0);
					fa[v]=x;
				}
			}
			val[x]=sdom[x];
			B::ae(sdom[x],x);
		}
		for(int i=1;i<=n;i++){
			int x=id[i];
			if(idom[x]!=sdom[x]){
				idom[x]=idom[idom[x]];
			}
		}
	}
	inline void init(){
		tim=e=0;
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		B::init();
	}
}
int main(){
	for(int n,tot;scanf("%d%d",&n,&tot)!=EOF;){
		G::init(),T::init();
		while(tot--){
			int u=ni,v=ni;
			G::add(u,v);
		}
		G::work(n);
		for(int i=1;i<n;i++){
			T::ae(G::idom[i],i);
		}
		T::len[n]=0,T::dfs(n);
		for(int i=1;i<=n;i++){
			printf("%d%c",T::len[i]," \n"[i==n]);
		}
	}
}
