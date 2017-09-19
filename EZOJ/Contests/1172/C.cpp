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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=100010;
int pval[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],dep[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		fa[1]=0,dep[1]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs(int x){
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs(v);
			}
		}
	}
	inline int lca(int u,int v){
		while(u!=v){
			if(dep[u]>dep[v]){
				u=fa[u];
			}else{
				v=fa[v];
			}
		}
		return u;
	}
	inline int work(int u,int v,int k){
		int w=lca(u,v),ans=0,cnt=0;
		for(;u!=w;u=fa[u]){
			cnt++;
			if(cnt%k==0){
				apmax(ans,pval[u]);
			}
		}
		int cnt2=0,cnt3=0;
		for(int x=v;x!=w;x=fa[x],cnt2++);
		for(;v!=w;v=fa[v],cnt3++){
			if(((cnt2-cnt3)+cnt+1)%k==0){
				apmax(ans,pval[v]);
			}
		}
		cnt++;
		if(cnt%k==0){
			apmax(ans,pval[w]);
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(1);
	while(tot--){
		int u=ni,v=ni,k=ni;
		printf("%d\n",T::work(u,v,k));
	}
	return 0;
}

