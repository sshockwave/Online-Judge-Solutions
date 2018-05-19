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
const int N=1010,INF=0x7f7f7f7f;
int col[N];
bool ban[N];
int ans=INF;
int n;
namespace G{
	int dis[N][N];
	inline void init(){
		memset(dis,127,sizeof(dis));
	}
	inline void ae(int u,int v,int w){
		apmin(dis[u][v],w);
	}
	inline void dij(){
		lint val=0;
		int last=0;
		for(int i=1;i<=n;i++){
			if(ban[col[i]])continue;
			val+=dis[last][i];
			if(val>=ans)return;
			last=i;
		}
		assert(val<ans);
		ans=val;
	}
}
int colcnt[N];
int collst[N];
void dfs(int x){
	if(x==0)return G::dij();
	ban[collst[x]]=true;
	dfs(x-1);
	ban[collst[x]]=false;
	dfs(x-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
#endif
	n=ni;
	int m=ni;
	col[0]=col[n]=0;
	memset(colcnt,0,sizeof(colcnt));
	int ls=0;
	for(int i=1;i<n;i++){
		col[i]=ni;
		if(colcnt[col[i]]++==0){
			collst[++ls]=col[i];
		}
	}
	G::init();
	for(int i=1;i<=m;i++){
		int u=ni,v=ni;
		G::ae(u,v,ni);
	}
	dfs(ls);
	printf("%d\n",ans!=INF?ans:-1);
	return 0;
}
