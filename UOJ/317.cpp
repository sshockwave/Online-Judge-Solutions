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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=50010,D=10,E=100010;
namespace G2{
	const int N=50010*3;
	int to[E+N/3*2+48],bro[E+N/3*2+48],head[N],headbad[N],e=0;
	int deg[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(headbad,-1,sizeof(headbad));
		memset(deg,0,sizeof(deg));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++,deg[v]++;
	}
	inline void aebad(int u,int v){
		to[e]=v,bro[e]=headbad[u],headbad[u]=e++;
	}
	int lst[N],ls=0;
	inline void pushnode(int x){
		lst[++ls]=x;
	}
	int stat[N],ind[N];
	inline void markbad(int x){
		if(stat[x]==-1){
			return;
		}
		assert(stat[x]==0);
		stat[x]=-1;
		for(int i=head[x],v;~i;i=bro[i]){
			assert(stat[to[i]]<=0);
			if(stat[v=to[i]]==0){
				markbad(v);
			}
		}
	}
	inline void reset(){
		for(int i=1,x;i<=ls;i++){
			x=lst[i],stat[x]=0,ind[x]=deg[x];
		}
	}
	int que[N];
	inline void work(){
		int qh=0,qt=0;
		for(int i=1,x;i<=ls;i++){
			x=lst[i];
			if(ind[x]==0&&~stat[x]){
				que[qt++]=x;
			}
		}
		while(qh<qt){
			int x=que[qh++];
			assert(stat[x]<=0);
			if(stat[x]){
				continue;
			}
			stat[x]=1;
			for(int i=headbad[x];~i;i=bro[i]){
				markbad(to[i]);
			}
			for(int i=head[x],v;~i;i=bro[i]){
				assert(stat[to[i]]<=0);
				if(stat[v=to[i]]==0&&(--ind[v])==0){
					que[qt++]=v;
				}
			}
		}
	}
}
namespace G1{
	const int N=50010*3;
	int to[E],bro[E],head[N],e=0,n=0;
	int dfn[N],low[N],bln[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	inline int nn(){
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(instk,0,sizeof(instk));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				if(instk[v]){
					apmin(low[x],low[v]);
				}
			}else{
				tarjan(v);
				apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--ss];
				instk[v]=false;
				bln[v]=x;
			}while(x!=v);
		}
	}
	inline void work(){
		for(int i=1;i<=n;i++){
			if(dfn[i]==0){
				tarjan(i);
			}
			if(bln[i]==i){
				G2::pushnode(i);
			}
		}
		for(int x=1;x<=n;x++){
			for(int i=head[x];~i;i=bro[i]){
				G2::ae(bln[to[i]],bln[x]);
			}
		}
	}
}
int node[N][3],selct[N];
int lst[D],ls=0,n;
bool ban[G1::N];
inline bool check(){
	G2::reset();
	for(int i=1;i<=G1::n;i++){
		if(ban[i]){
			G2::markbad(G1::bln[i]);
		}
	}
	G2::work();
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=0;j<3;j++){
			if(G2::stat[node[i][j]]==1){
				cnt++;
				selct[i]=j;
			}
		}
		if(cnt!=1){
			return false;
		}
	}
	return true;
}
bool dfs(int i){
	if(i>ls){
		return check();
	}
	for(int j=0;j<3;j++){
		ban[node[lst[i]][j]]=true;
		if(dfs(i+1)){
			return true;
		}
		ban[node[lst[i]][j]]=false;
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	n=ni,ni;
	memset(ban,0,sizeof(ban));
	G1::init(),G2::init();;
	for(int i=1;i<=n;i++){
		char c=nc();
		node[i][0]=G1::nn();
		node[i][1]=G1::nn();
		node[i][2]=G1::nn();
		if(c=='x'){
			lst[++ls]=i;
		}else{
			ban[node[i][c-'a']]=true;
		}
	}
	for(int tot=ni;tot--;){
		int u,v;
		char cu,cv;
		u=ni,cu=nc(),v=ni,cv=nc();
		G1::ae(node[u][cu-'A'],node[v][cv-'A']);
	}
	G1::work();
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){
			if(!ban[node[i][j]]){
				for(int k=0;k<3;k++){
					if(j!=k&&!ban[node[i][k]]){
						G2::aebad(G1::bln[node[i][j]],node[i][k]);
					}
				}
			}
		}
	}
	if(dfs(1)){
		for(int i=1;i<=n;i++){
			putchar(selct[i]+'A');
		}
		putchar('\n');
	}else{
		puts("-1");
	}
	return 0;
}
