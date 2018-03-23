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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int INF=0x7f7f7f7f;
int n,m;
namespace G{
	const int N=10010,E=100010;
	int fr[E],to[E],bro[E],idx[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int i){
		fr[e]=u,to[e]=v,bro[e]=head[u],idx[e]=i,head[u]=e++;
	}
}
namespace task1{
	const int N=18;
	int f[N][1<<N];//[at][S]
	int bitcnt[1<<N];
	vector<int>sset[N+1];
	inline int main(){
		memset(f,127,sizeof(f));
		int sn=1<<m;
		for(int i=0;i<sn;i++){
			bitcnt[i]=i?bitcnt[i^(i&-i)]+1:0;
			sset[bitcnt[i]].push_back(i);
		}
		for(int i=0;i<n;i++){
			f[0][0]=1;
		}
		for(int b=0;b<m;b++){
			for(vector<int>::iterator it=sset[b].begin();it!=sset[b].end();it++){
				int s=*it;
				int curans=INF;
				for(int x=0;x<n;x++){
					apmin(curans,f[x][s]);
				}
				for(int x=0;x<n;x++){
					apmin(f[x][s],curans+1);
				}
				for(int e=0;e<G::e;e++){
					if(((s>>(G::idx[e]-1))&1)==0){
						apmin(f[G::to[e]-1][s|(1<<(G::idx[e]-1))],f[G::fr[e]-1][s]);
					}
				}
			}
		}
		int ans=INF;
		for(int i=0;i<n;i++){
			apmin(ans,f[i][sn-1]);
		}
		return ans;
	}
}
namespace task3{
	using G::N;
	bool vis[N];
	int cur;
	int cnt;
	void dfs(int x){
		if(vis[x])return;
		cnt++;
		vis[x]=true;
		using namespace G;
		bool r=false;
		for(int i=head[x];~i;i=bro[i]){
			r^=1;
			dfs(to[i]);
		}
		cur+=r;
	}
	inline int main(){
		memset(vis,0,sizeof(vis));
		int ans=0;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				cur=0,cnt=0;
				dfs(i);
				ans+=max(cnt>1?1:0,cur>>1);
			}
		}
		return ans;
	}
}
namespace task4{
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("draw.in","r",stdin);
	freopen("draw.out","w",stdout);
#endif
	n=ni,m=ni;
	bool dir=true,undir=true;
	G::init();
	for(int i=1;i<=m;i++){
		int u=ni,v=ni,c=ni;
		dir&=c==0;
		undir&=c==1;
		if(c){
			G::ae(u,v,i);
			G::ae(v,u,i);
		}else{
			G::ae(u,v,i);
		}
	}
	if(undir){
		printf("%d\n",task3::main());
	}else{
		printf("%d\n",task1::main());
	}
	return 0;
}
