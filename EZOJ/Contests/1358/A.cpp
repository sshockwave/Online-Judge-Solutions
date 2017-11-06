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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
namespace G{
	const int E=100010*2;
	int to[E],bro[E],head[N],deg[N],e=0;
	int dfn[N],low[N],tim=0;
	bool istan[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(deg,0,sizeof(deg));
		memset(istan,0,sizeof(istan));
		memset(dfn,0,sizeof(dfn));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++,deg[u]++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void tarjan(int x,int fa){
		dfn[x]=low[x]=++tim;
		int cnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				apmin(low[x],dfn[v]);
			}else{
				cnt++;
				tarjan(v,x);
				if(low[v]==dfn[x]){
					istan[x]=true;
				}else apmin(low[x],low[v]);
			}
		}
		if(fa==0){
			istan[x]=cnt>1;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni,m=ni;
	G::init();
	for(int tot=m;tot--;G::add(ni,ni));
	G::tarjan(1,0);
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(!G::istan[i]&&m-G::deg[i]==n-2){
			cnt++;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		if(!G::istan[i]&&m-G::deg[i]==n-2){
			printf("%d ",i);
		}
	}
	putchar('\n');
	return 0;
}
