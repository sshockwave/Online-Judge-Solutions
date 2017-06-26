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
const int N=200010;
namespace G{
	const int E=N*2;
	int to[E],bro[E],head[N],e;
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int &u,const int &v){
		ae(u,v),ae(v,u);
	}
	int con[N],dfn[N],id[N],tim;
	void dfs(int x){
		id[dfn[x]=++tim]=x;
		for(int i=head[x];~i;i=bro[i]){
			if((i&1)==0&&dfn[to[i]]==0){
				con[to[i]]=i;
				dfs(dfn[to[i]]);
			}
		}
	}
	inline void apdfn(int &a,const int &b){
		if(dfn[b]<dfn[a]){
			a=b;
		}
	}
	int idom[N],sdom[N];
	namespace B{
		const int E=N;
		int to[E],bro[E],head[N],e;
		inline void init(int n){
			memset(head+1,-1,n<<2);
			e=0;
		}
		inline void ae(const int &u,const int &v){
			to[e]=v,bro[e]=head[u],head[u]=e++;
		}
		inline void work(int);
	}
	int fa[N],val[N];
	int root(int x){
		if(fa[x]==x){
			return x;
		}
		int rt=root(fa[x]);
		apdfn(val[x],val[fa[x]]);
		return fa[x]=rt;
	}
	inline int eval(int x){
		root(x);
		return val[x];
	}
	inline void B::work(int x){
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			assert(sdom[v]==x);
			idom[v]=x==eval(v)?x:val[v];
			assert(eval(v)==val[v]);
		}
	}
	inline void dominate(int n){
		dfs(1);
		assert(id[1]==1);
		for(int i=1;i<=n;i++){
			idom[i]=sdom[i]=fa[i]=val[i]=i;
		}
		for(int _=tim;_>1;_--){
			int x=id[_];
			for(int i=head[x];~i;i=bro[i]){
				if(i&1){
					apdfn(sdom[x],eval(to[i]));
				}
			}
			B::work(x),B::ae(sdom[x],x);
			fa[x]=to[con[x]^1];
		}
		for(int _=1;_<=tim;_++){
			int x=id[_];
			if(idom[x]!=sdom[x]){
				idom[x]=idom[idom[x]];
			}
		}
	}
	inline void init(int n){
		e=tim=0;
		memset(head+1,-1,n<<2);
		memset(dfn+1,0,n<<2);
		B::init(n);
	}
}
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e,cnt;
	bool vis[N],mark[E];
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void dfs(int x){
		vis[x]=true;
		for(int i=G::head[x],v;~i;i=G::bro[i]){
			if((i&1)==0&&!vis[v=G::to[i]]){
				cnt++;
				mark[i>>1]=true;
			}
		}
		for(int i=head[x];~i;i=bro[i]){
			dfs(to[i]);
		}
		vis[x]=false;
	}
	inline void init(int n,int tot){
		cnt=e=0;
		memset(head+1,-1,n<<2);
		memset(mark,0,tot);
	}
}
int main(){
	for(int n,tot;scanf("%d%d",&n,&tot)!=EOF;){
		G::init(n),T::init(n,tot);
		for(int u,v;tot--;){
			u=ni,v=ni;
			G::add(u,v);
		}
		G::dominate(n);
		for(int _=1;_<=G::tim;_++){
			int x=G::id[_];
			T::ae(G::idom[x],x);
		}
		T::dfs(1);
		printf("%d\n",T::cnt);
		for(int i=0,e=G::e>>1;i<e;i++){
			if(T::mark[i]){
				printf("%d ",i+1);
			}
		}
		putchar('\n');
	}
}
