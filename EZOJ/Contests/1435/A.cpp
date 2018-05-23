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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010;
int pval[N],ans[N];
namespace BIT{
	int c[N],n;
	inline void init(int _n){
		mset(c+1,0,n=_n);
	}
	inline void add(int x,int v){
		++x;
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		++x;
		int a=0;
		for(apmin(x,n);x;a+=c[x],x^=x&-x);
		return a;
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	bool vis[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(vis+1,0,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int rad[N];
	void dfs1(int x,int fa){
		rad[x]=fa?rad[fa]+1:0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs1(v,x);
			}
		}
	}
	int g;
	int size[N];
	void gcen(int x,int n){
		assert(!vis[x]);
		vis[x]=true;
		size[x]=1;
		int bal=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				gcen(v,n);
				size[x]+=size[v];
				apmax(bal,size[v]);
			}
		}
		apmax(bal,n-size[x]);
		if((bal<<1)<=n){
			g=x;
		}
		vis[x]=false;
	}
	void addsum(int x,int d,int t){
		assert(!vis[x]);
		vis[x]=true;
		BIT::add(d,pval[x]*t);
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				addsum(v,d+1,t);
			}
		}
		vis[x]=false;
	}
	void upd_ans(int x,int d){
		assert(!vis[x]);
		vis[x]=true;
		if(rad[x]>=d){
			ans[x]+=BIT::sum(rad[x]-d);
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				upd_ans(v,d+1);
			}
		}
		vis[x]=false;
	}
	void solve(int x,int n){
		gcen(x,n),x=g;
		BIT::init(n+1);
		addsum(x,0,1);
		ans[x]+=BIT::sum(rad[x]);
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				addsum(v,1,-1);
				upd_ans(v,1);
				addsum(v,1,1);
			}
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				solve(v,size[v]>size[x]?n-size[x]:size[v]);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("escape.in","r",stdin);
	freopen("escape.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1,0);
	mset(ans+1,0,n);
	T::solve(1,n);
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
