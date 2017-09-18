#include <iostream>
#include <cstdio>
#include <cstring>
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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=200010,D=20;
inline int revbit(int x){
	int ret=0;
	for(int i=0;i<D;i++){
		ret=(ret<<1)|(x&1),x>>=1;
	}
	return ret;
}
namespace Trie{
	const int N=200010*D;
	int son[N][20],tag[N],n;
	bool isfull[N];
	inline void init(){
		n=0,isfull[0]=false;
	}
	inline int chain(int val){
		int x=++n;
		son[x][0]=son[x][1]=tag[x]=0,isfull[x]=true;
		for(int i=0;i<D;i++,val>>=1){
			n++;
			son[n][val&1]=x;
			son[n][!(val&1)]=0;
			tag[n]=0;
			isfull[n]=false;
			x=n;
		}
		return x;
	}
	inline void mark(int x,int v){
		tag[x]^=v;
		if(v&1){
			swap(son[x][0],son[x][1]);
		}
	}
	inline void down(int x){
		if(son[x][0]){
			mark(son[x][0],tag[x]>>1);
		}
		if(son[x][1]){
			mark(son[x][1],tag[x]>>1);
		}
		tag[x]=0;
	}
	inline void up(int x){
		isfull[x]=
			(isfull[son[x][0]]&&isfull[son[x][1]])
			||(son[x][0]==0&&son[x][1]==0);
	}
	inline int merge(int u,int v){
		if(u==0||v==0){
			return u|v;
		}
		down(u),down(v);
		son[u][0]=merge(son[u][0],son[v][0]);
		son[u][1]=merge(son[u][1],son[v][1]);
		up(u);
		return u;
	}
	inline int sg(int x){
		down(x);
		assert(!isfull[x]);
		if(son[x][0]==0&&son[x][1]==0){
			return 0;
		}
		if(son[x][0]&&!isfull[son[x][0]]){
			return sg(son[x][0])<<1;
		}else{
			return ((sg(son[x][1]))<<1)|1;
		}
	}
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	bool vis[N];
	inline void init(int n){
		memset(head+1,-1,n<<2);
		memset(vis+1,0,n);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int f[N],rt[N];
	void dfs(int x,int fa){
		vis[x]=true;
		f[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				f[x]^=f[v];
			}
		}
		rt[x]=Trie::chain(f[x]);
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				Trie::mark(rt[v],revbit(f[x]^f[v]));
				rt[x]=Trie::merge(rt[x],rt[v]);
			}
		}
		f[x]=revbit(Trie::sg(rt[x]));
	}
}
inline int Main(){
	int n=ni;
	Trie::init(),T::init(n);
	for(int tot=ni;tot--;){
		T::add(ni,ni);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(!T::vis[i]){
			T::dfs(i,0);
			ans^=T::f[i];
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	for(int tot=ni;tot--;puts(Main()?"Alice":"Bob"));
	return 0;
}
