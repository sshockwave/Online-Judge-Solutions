#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <ctime>
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
	if(b<a){a=b;}
}
const int n=ni,k=ni,N=10010,K=5,INF=0x7f7f7f7f;
int col[N];
bool vis[N];
namespace T{
	const int E=N*2;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int &u,const int &v){
		ae(u,v),ae(v,u);
	}
	int f[N][1<<K],cmap[N];
	inline void dfs(int x,int e){
		int *F=f[x];
		F[0]=0,F[cmap[col[x]]]=1;
		const static int tot=1<<k;
		for(int i=head[x],v;~i;i=bro[i]){
			if(i!=e){
				dfs(v=to[i],i^1);
				int *G=f[v];
				for(int s=0;s<tot;s++){
					for(int t=s;t;t=(t-1)&s){
						if(F[t]<INF&&G[s^t]<INF){
							apmin(F[s],F[t]+G[s^t]);
						}
					}
				}
			}
		}
		for(int s=0;s<tot;s++){
			for(int t=s;t;t=(t-1)&s){
				apmin(F[t],F[s]);
			}
		}
	}
	inline bool gen(){
		int s=0;
		for(int i=1;i<=n;i++){
			if(vis[i]){
				s|=cmap[i]=1<<rand()%k;
			}
		}
		return s+1==(1<<k);
	}
	inline int work(){
		while(!gen());
		memset(f,127,sizeof(f));
		dfs(1,-1);
		int ans=INF;
		for(int i=1,top=(1<<k)-1;i<=n;i++){
			apmin(ans,f[i][top]);
		}
		return ans;
	}
}
int main(){
	T::init();
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		vis[col[i]=ni]=true;
	}
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	int ans=INF;
	for(int tot=40;tot--;){
		apmin(ans,T::work());
	}
	printf("%d\n",ans);
}
