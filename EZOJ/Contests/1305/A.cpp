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
const int N=110;
namespace G{
	const int E=N*2;
	int to[E],bro[E],head[N],e=0;
	int f[N][N],g[N][N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(f,-1,sizeof(f));
		memset(g,-1,sizeof(g));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs(int x,int fa,int n){
		int *F=f[x],*G=g[x];
		F[0]=G[0]=1;
		if(n==0){
			return;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=fa){
				dfs(v,x,n-1);
				for(int k=n;k>=2;k--){
					for(int j=k-2;j>=0;j--){
						if(~F[k-j-1]&&~g[v][j]){
							apmax(G[k],F[k-j-1]+g[v][j]);
						}
						if(~f[v][j]){
							if(~F[k-j-2]){
								apmax(F[k],F[k-j-2]+f[v][j]);
							}
							if(~G[k-j-2]){
								apmax(G[k],G[k-j-2]+f[v][j]);
							}
						}
					}
				}
				for(int j=0;j<n;j++){
					if(~g[v][j]){
						apmax(G[j+1],F[0]+g[v][j]);
					}
				}
			}
		}
	}
}
int main(){
	int n=ni,step=ni;
	G::init();
	for(int i=1;i<n;i++){
		G::add(ni,ni);
	}
	G::dfs(0,-1,step);
	int ans=0;
	for(int i=0;i<=step;i++){
		apmax(ans,G::f[0][i]);
		apmax(ans,G::g[0][i]);
	}
	printf("%d\n",ans);
}