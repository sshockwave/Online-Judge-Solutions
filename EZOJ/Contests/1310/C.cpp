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
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=1000010,E=N*2;
lint f[E],g[E];
namespace G{
	int to[E],bro[E],val[E],head[N],e=0;
	bool vis[E];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs(int e){
		vis[e]=true;
		int x=to[e];
		for(int i=head[x];~i;i=bro[i]){
			if((e^i)!=1){
				if(!vis[i]){
					dfs(i);
				}
				apmax(g[e],g[i]);
				apmax(g[e],f[e]+f[i]+val[i]);
				apmax(f[e],f[i]+val[i]);
			}
		}
		apmax(g[e],f[e]);
	}
}
int main(){
	int n=ni;
	G::init();
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		G::add(u,v,ni);
	}
	for(int i=0;i<G::e;i++){
		if(!G::vis[i]){
			G::dfs(i);
		}
	}
	lint sum=0;
	for(int i=1;i<n;i++){
		lint p=g[(i<<1)-2],q=g[(i<<1)-1];
		static const lint MOD=2333333333333333ll;
		(sum+=max(p,q)*23333%MOD)%=MOD;
		(sum+=min(p,q)*2333%MOD)%=MOD;
		(sum+=233ll*i*i+23*i+2)%=MOD;
	}
	printf("%lld\n",sum);
}