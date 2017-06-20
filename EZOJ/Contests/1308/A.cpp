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
	if(a>b){a=b;}
}
const int N=100010,E=N*2;
namespace G{
	int to[E],bro[E],head[N],deg[N],e;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		deg[u]++,deg[v]++;
		ae(u,v),ae(v,u);
	}
	bool vis[E];
	inline void build(int n){
		memset(head+1,-1,n<<2);
		memset(deg+1,0,n<<2);
		memset(vis,0,sizeof(vis));
		e=0;
		for(int i=1;i<n;i++){
			add(ni,ni);
		}
	}
	int f[E],g[E],h[E];//s->t:from t,pass t,ignore t
	void dfs(int e){
		int x=to[e];
		vis[e]=true;
		f[e]=0,g[e]=deg[x]-1,h[e]=0;
		for(int i=head[x];~i;i=bro[i]){
			if((i^1)!=e){
				if(!vis[i]){
					dfs(i);
				}
				apmax(h[e],max(g[i],h[i]));
				apmax(g[e],f[e]+f[i]-1);
				apmax(f[e],f[i]+deg[x]-2);
			}
		}
		apmax(f[e],deg[x]-1);
		apmax(g[e],f[e]);
	}
	inline int work(int n){
		int ans=0;
		for(int i=0;i<e;i+=2){
			apmax(ans,g[i]+g[i^1]);
			apmax(ans,h[i]+h[i^1]+1);
		}
		for(int x=1;x<=n;x++){
			int mxg=0,f1=0,f2=0,f3=0;
			for(int i=head[x];~i;i=bro[i]){
				apmax(ans,mxg+g[i]+1);
				apmax(mxg,g[i]);
				apmax(ans,f1+f2+f3+f[i]+deg[x]-4);
				if(f[i]>f1){
					f3=f2,f2=f1,f1=f[i];
				}else if(f[i]>f2){
					f3=f2,f2=f[i];
				}else if(f[i]>f3){
					f3=f[i];
				}
			}
			apmax(ans,deg[x]);
			apmax(ans,f1+deg[x]-1);
			apmax(ans,f1+f2+deg[x]-2);
			apmax(ans,f1+f2+f3+deg[x]-3);
		}
		return ans;
	}
}
int main(){
	for(int tot=ni,x=ni;tot--;){
		int n=ni;
		if(x){
			ni,ni;
			if(x==2){
				ni,ni;
			}
		}
		G::build(n);
		for(int i=0;i<G::e;i++){
			if(!G::vis[i]){
				G::dfs(i);
			}
		}
		printf("%d\n",G::work(n));
	}
}