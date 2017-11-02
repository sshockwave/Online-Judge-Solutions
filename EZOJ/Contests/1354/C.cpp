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
const int N=500010,O=1000000007;
namespace trie{
	const int N=500010*25;
	int son[N][2],size[N],xorsum[N],n=0;
	inline void init(){
		memset(son,0,sizeof(son));
		size[0]=xorsum[0]=0;
	}
	inline int nn(){
		return ++n;
	}
	inline void up(int x){
		xorsum[x]=((xorsum[son[x][0]]^xorsum[son[x][1]])<<1)^(size[son[x][1]]&1);
	}
	void add(int &x,int num,int v){
		if(x==0){
			x=nn();
		}
		size[x]+=v;
		if(size[x]==0){
			x=0;
			return;
		}
		assert(size[x]>0);
		if(num==0){
			return;
		}
		add(son[x][num&1],num>>1,v);
		up(x);
	}
	inline void addone(int &x){
		if(x==0){
			return;
		}
		assert(size[x]);
		int lsz=size[x]-size[son[x][1]];
		assert(lsz>=size[son[x][0]]);
		if(lsz){
			if(son[x][0]==0){
				son[x][0]=nn();
			}
			size[son[x][0]]=lsz;
		}
		swap(son[x][0],son[x][1]);
		addone(son[x][0]);
		up(x);
	}
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],pval[N],hits[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(pval,0,sizeof(pval));
		memset(hits,0,sizeof(hits));
		fa[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int rt[N];
	void dfs(int x){
		int cnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				cnt++;
				dfs(v);
			}
		}
		if(cnt){
			rt[x]=trie::nn();
			trie::size[rt[x]]=cnt;
		}
	}
	inline int eval(int x){
		return pval[x]+hits[fa[x]];
	}
	inline int work(int x){
		if(fa[x]){
			if(fa[fa[x]]){
				trie::add(rt[fa[fa[x]]],eval(fa[x]),-1);
			}
			pval[fa[x]]++;
			if(fa[fa[x]]){
				trie::add(rt[fa[fa[x]]],eval(fa[x]),1);
			}
		}
		hits[x]++;
		trie::addone(rt[x]);
		assert(eval(0)==0);
		return trie::xorsum[rt[x]]^eval(fa[x]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("struct.in","r",stdin);
	freopen("struct.out","w",stdout);
#endif
	int n=ni,tot=ni;
	trie::init(),T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	T::dfs(1);
	lint ans=0;
	for(int i=1;i<=tot;i++){
		ans+=(lint)T::work(ni)*i%O*(i+1)%O;
	}
	printf("%lld\n",ans%O);
	return 0;
}
