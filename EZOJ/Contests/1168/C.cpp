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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=100010,INF=0x7f7f7f7f;
namespace bit{
	int c[N<<1],n;
	inline void init(int _n){
		memset(c,0,((n=_n+1)+1)<<2);
	}
	inline int lb(int x){
		return x&(-x);
	}
	inline void add(int x,int v){
		x++;
		for(;x<=n;c[x]+=v,x+=lb(x));
	}
	inline int sum(int x){
		x++;
		apmin(x,n);
		int ans=0;
		for(;x;ans+=c[x],x^=lb(x));
		return ans;
	}
	inline int geq(int x){
		x++;
		return sum(n-1)-sum(max(0,x-1)-1);
	}
}
lint ans=0;
int lst[N],ls=0,rn;
bool vis[N];
int K;
namespace G{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int bal[N],g,gbal;
	inline int gg(int x,int n){
		vis[x]=true;
		int sz=1;
		bal[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				int t=gg(v,n);
				apmax(bal[x],t);
				sz+=t;
			}
		}
		apmax(bal[x],n-sz);
		if(bal[x]<gbal){
			g=x,gbal=bal[x];
		}
		vis[x]=false;
		return sz;
	}
	void putdep(int x,int dep,int d){
		bit::add(dep,d);
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				putdep(v,dep+1,d);
			}
		}
		vis[x]=false;
	}
	int offset;
	void putans(int x,int dep){
		ans+=bit::geq(offset-dep);
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				putans(v,dep+1);
			}
		}
		vis[x]=false;
	}
	int getsize(int x){
		int sz=1;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				sz+=getsize(v);
			}
		}
		vis[x]=false;
		return sz;
	}
	void pdiv(int x,int n){
		gbal=INF,gg(x,n),x=g;
		bit::init(n);
		offset=K;
		vis[x]=true;
		bit::add(0,1);
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				putans(v,1);
				putdep(v,1,1);
			}
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				pdiv(v,getsize(v));
			}
		}
	}
	bool ring(int x,int f){
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=f){
				if(vis[v]||ring(v,x)){
					lst[++ls]=v;
					if(lst[1]==x){
						rn=ls;
					}
					return true;
				}
			}
		}
		vis[x]=false;
		return false;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni,e=ni;
	K=ni-1;//K edges
	G::init();
	for(int i=1;i<=e;i++){
		G::add(ni,ni);
	}
	if(n==e){
		G::ring(1,0);
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=rn;i++){
			vis[lst[i]]=true;
		}
		for(int i=1;i<=rn;i++){
			int x=lst[i];
			vis[x]=false;
			G::pdiv(x,G::getsize(x));
			assert(vis[x]);
		}
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=rn;i++){
			vis[lst[i]]=true;
		}
		bit::init(rn<<1);
		for(int i=1;i<=rn;i++){
			G::putdep(lst[i],2*rn-i,1);
			vis[lst[i]]=true;
		}
		for(int i=1;i<=rn;i++){
			G::putdep(lst[i],2*rn-i,-1);
			G::offset=rn+K-i;
			G::putans(lst[i],0);
			G::putdep(lst[i],rn-i,1);
			vis[lst[i]]=true;
		}
	}else{
		G::pdiv(1,n);
	}
	printf("%lld\n",ans);
	return 0;
}
