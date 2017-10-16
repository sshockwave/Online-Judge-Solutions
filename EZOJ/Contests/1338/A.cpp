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
const int N=2000010;
int errcnt=0;
namespace G{
	const int E=4000010;
	int to[E],bro[E],head[N],e=0;
	int col[N],dfn[N];
	bool okay[E>>1];
	int f[N],g[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(col,0,sizeof(col));
		memset(dfn,0,sizeof(dfn));
		memset(okay,0,sizeof(okay));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void mark(int x){
		for(int i=head[x],v;~i;i=bro[i]){
			if(col[v=to[i]]){
				errcnt+=col[v]==col[x];
			}else{
				col[v]=-col[x];
				mark(v);
			}
		}
	}
	int tim=0;
	lint dfs(int x,int e){
		dfn[x]=++tim;
		lint f=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((i>>1)==e){
				continue;
			}
			if(dfn[v=to[i]]==0){
				f+=dfs(v,i>>1);
			}else{
				f+=(dfn[v]<dfn[x]?1ll:-1ll)<<(col[v]==col[x]?0:32);
				if(errcnt==1&&col[v]==col[x]){
					okay[i>>1]=true;
				}
			}
		}
		okay[e]=f==errcnt;
		return f;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fairy.in","r",stdin);
	freopen("fairy.out","w",stdout);
#endif
	int n=ni,tot=ni;
	G::init();
	for(int i=1;i<=tot;i++){
		G::add(ni,ni);
	}
	for(int i=1;i<=n;i++){
		if(G::col[i]==0){
			G::col[i]=1;
			G::mark(i);
		}
	}
	if(errcnt==0){
		printf("%d\n",tot);
		for(int i=1;i<=tot;i++){
			printf("%d ",i);
		}
		putchar('\n');
		return 0;
	}
	errcnt>>=1;
	for(int i=1;i<=n;i++){
		if(G::dfn[i]==0){
			G::dfs(i,0);
		}
	}
	int anscnt=0;
	for(int i=0;i<tot;i++){
		anscnt+=G::okay[i];
	}
	printf("%d\n",anscnt);
	for(int i=0;i<tot;i++){
		if(G::okay[i]){
			printf("%d ",i+1);
		}
	}
	putchar('\n');
	return 0;
}
