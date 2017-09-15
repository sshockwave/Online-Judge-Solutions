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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=300010;
const lint LINF=0x7f7f7f7f7f7f;
#define BLACK 0
#define WHITE 1
#define GREY 2
int col[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	lint val[E];
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	lint f[N],g[N],h[N];
	void dfs(int x,int fa){
		f[x]=g[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				f[x]+=min(f[v],min(g[v],h[v])+val[i]);
				g[x]+=min(g[v],min(f[v],h[v])+val[i]);
			}
		}
		if(col[x]==BLACK){
			f[x]=LINF;
		}else if(col[x]==WHITE){
			h[x]=g[x];
			g[x]=LINF;
		}
		if(col[x]!=WHITE){
			h[x]=LINF;
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa){
					if(h[v]<LINF){
						apmin(h[x],g[x]-min(g[v],min(f[v],h[v])+val[i])+h[v]);
					}
				}
			}
		}
	}
}
inline lint Main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		col[i]=ni;
	}
	T::init(n);
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v,ni);
	}
	T::dfs(1,0);
	return min(T::f[1],min(T::g[1],T::h[1]));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("hard.in","r",stdin);
	freopen("hard.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
