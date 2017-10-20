#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=1010;
int n,ans;
namespace T{
	const int E=N<<1;
	int fa[N],dfn[N],tim;
	bool qury[N][N],have[N][N];
	vector<int>e[N];
	inline void init(int n){
		tim=0;
		for(int i=1;i<=n;i++){
			e[i].clear();
			fa[i]=i;
			dfn[i]=0;
			memset(qury[i]+1,0,n);
			memset(have[i]+1,0,n);
		}
	}
	inline void add(int u,int v){
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int root(int x){
		return fa[x]==x?x:(fa[x]=root(fa[x]));
	}
	int lnk[N];
	vector<int>mate[N];
	int mvvis[N],mvtim=0;
	bool vacmv(int x){
		mvvis[x]=mvtim;
		for(int i=0,ti=mate[x].size();i<ti;i++){
			int v=mate[x][i];
			if(lnk[v]==-1){
				lnk[v]=x;
				lnk[x]=v;
				return true;
			}else if(mvvis[lnk[v]]<mvtim){
				int w=lnk[v];
				lnk[v]=x;
				lnk[x]=v;
				lnk[w]=-1;
				if(vacmv(w)){
					return true;
				}
				lnk[w]=v;
				lnk[v]=w;
				lnk[x]=-1;
			}
		}
		return false;
	}
	bool avail[N];
	void gavail(int x){
		avail[x]=true;
		for(int i=0,ti=mate[x].size();i<ti;i++){
			int v=mate[x][i];
			if(lnk[v]!=-1&&!avail[lnk[v]]){
				gavail(lnk[v]);
			}
		}
	}
	void dfs(int x,int f){
		dfn[x]=++tim;
		for(int i=0,ti=e[x].size();i<ti;i++){
			int v=e[x][i];
			if(v!=f){
				dfs(v,x);
				mate[v].clear();
				lnk[v]=-1;
				if(qury[v][x]){
					ans++;
					continue;
				}
				for(int u=1;u<=n;u++){
					if(qury[v][u]&&dfn[u]>=dfn[x]){
						int w=root(u);
						if(have[w][u]&&!qury[w][x]){
							mate[w].push_back(v);
							mate[v].push_back(w);
						}
					}
				}
				mvtim++,ans+=vacmv(v);
			}
		}
		for(int i=0,ti=e[x].size();i<ti;i++){
			int v=e[x][i];
			if(v!=f){
				fa[v]=x;
				avail[v]=false;
				if(!qury[v][x]&&lnk[v]==-1){
					gavail(v);
				}
			}
		}
		for(int i=0,ti=e[x].size();i<ti;i++){
			int v=e[x][i];
			if(v!=f&&avail[v]){
				for(int u=1;u<=n;u++){
					assert(!have[v][u]||!qury[v][u]);
					have[x][u]|=have[v][u];
					qury[x][u]|=qury[v][u];
				}
			}
		}
		have[x][x]=true;
		for(int u=1;u<=n;u++){
			if(dfn[u]==0||dfn[u]>=dfn[x]){
				qury[x][u]=false;
			}
		}
	}
}
inline int Main(){
	n=ni,ans=0;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		T::qury[u][v]=true;
		T::qury[v][u]=true;
	}
	T::dfs(1,0);
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("parade.in","r",stdin);
	freopen("parade.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
