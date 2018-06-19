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
const int N=1010,E=N<<1,INF=0x7f7f7f7f;
int st[N],len[N];
int ans;
inline int transf(const int a,const int b){
	const int t=st[b]-(st[a]+len[a])%24;
	return t<0?t+24:t;
}
namespace G{
	const int N=::N<<1,E=N<<1;
	int n;
	int to[E],bro[E],val[E],head[N],e=0;
	bool vis[N];
	inline void init(int _n){
		n=_n;
		mset(head+1,-1,n);
		mset(vis+1,0,n);
	}
	inline void ae(int u,int v){
		assert(u&&v);
		to[e]=v,bro[e]=head[u],val[e]=transf(u,v),head[u]=e++;
	}
	void dfs(int x,int cnt=0,int sum=0){
		if(sum>=ans)return;
		if(vis[x]){
			if(cnt==n){
				ans=sum;
			}
			return;
		}
		++cnt;
		vis[x]=true;
		for(int i=head[x];~i;i=bro[i]){
			dfs(to[i],cnt,sum+val[i]);
		}
		vis[x]=false;
	}
}
int pe[N][2][2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("yist.in","r",stdin);
	freopen("yist.out","w",stdout);
#endif
	int n=ni;
	memset(pe,0,sizeof(pe));
	for(int i=1;i<=n*2;i++){
		const int u=(i+1)>>1,v=ni;
		if(pe[u][0][0]==0){
			pe[u][0][0]=i;
		}else{
			assert(pe[u][0][1]==0);
			pe[u][0][1]=i;
		}
		if(pe[v][1][0]==0){
			pe[v][1][0]=i;
		}else{
			assert(pe[v][1][1]==0);
			pe[v][1][1]=i;
		}
		st[i]=ni;
		len[i]=ni;
	}
	G::init(n*2);
	for(int i=1;i<=n;i++){
		G::ae(pe[i][1][0],pe[i][0][0]);
		G::ae(pe[i][1][0],pe[i][0][1]);
		G::ae(pe[i][1][1],pe[i][0][0]);
		G::ae(pe[i][1][1],pe[i][0][1]);
	}
	int ans=INF;
	{
		::ans=INF;
		const int t0=G::val[0],t2=G::val[2];
		G::val[0]=G::val[2]=st[pe[1][0][0]];
		G::dfs(pe[1][0][0]);
		G::val[0]=t0,G::val[2]=t2;
		apmin(ans,::ans);
	}
	{
		::ans=INF;
		const int t1=G::val[1],t3=G::val[3];
		G::val[1]=G::val[3]=st[pe[1][0][1]];
		G::dfs(pe[1][0][1]);
		G::val[1]=t1,G::val[3]=t3;
		apmin(ans,::ans);
	}
	for(int i=1;i<=n*2;i++){
		ans+=len[i];
	}
	printf("%d\n",ans);
	return 0;
}
