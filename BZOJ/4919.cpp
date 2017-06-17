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
const int N=200010;
int pval[N];
namespace G{
	int to[N],bro[N],head[N],e=0;
	int fa[N],f[N],g[N];//f:can choose g:mustn't choose
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void dfs(int x){
		f[x]=1,g[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			if(pval[x]>pval[v]){
				f[x]+=f[v];
			}else{
				f[x]+=g[v];
			}
			g[x]+=f[v];
		}
		apmax(f[x],g[x]);
	}
}
int main(){
	int n=ni;
	G::init();
	for(int i=1;i<=n;i++){
		pval[i]=ni,G::fa[i]=ni;
		G::ae(G::fa[i],i);
	}
	G::dfs(1);
	printf("%d\n",G::f[1]);
}