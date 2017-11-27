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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=1010,M=5010,INF=0x7f7f7f7f;
int pval[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int f[N],g[N][M];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(f,127,sizeof(f));
		memset(g,0,sizeof(g));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	bool dfs(int x,int fa){
		int *G=g[x],base=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				if(!dfs(v,x))return false;
				int a=pval[v],b=f[v];
				if(a>b){
					swap(a,b);
				}
				base+=a;
				if(base>pval[x])return false;
				for(int j=pval[x]-base;j>=0;j--){
					int tmp=G[j];
					if(tmp<INF){
						G[j]+=b;
						apmin(G[j+b-a],tmp+a);
					}
				}
			}
		}
		for(int i=pval[x]-base;i>=0;i--){
			apmin(f[x],G[i]);
		}
		return true;
	}
}
inline bool Main(){
	int n=ni;
	T::init();
	for(int i=2;i<=n;T::ae(ni,i),i++);
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	return T::dfs(1,0);
}
int main(){
	puts(Main()?"POSSIBLE":"IMPOSSIBLE");
	return 0;
}
