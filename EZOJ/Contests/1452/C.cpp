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
const int N=310,O=998244353;
namespace G{
	const int E=310;
	int to[E],bro[E],col[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],col[e]=w,head[u]=e++;
	}
	bool vis[E];
	int seq[E];
	inline int calc_seq(){
		int ans=0;
		for(int i=1;i<e;i++){
			ans+=col[seq[i]]==col[seq[i-1]];
		}
		ans+=col[seq[0]]==col[seq[e-1]];
		return ans;
	}
	int tourcnt=0;
	lint sum=0;
	void dfs(int x,int cnt){
		if(cnt==e)return ++tourcnt,sum+=calc_seq(),void();
		for(int &i=seq[cnt]=head[x];~i;i=bro[i]){
			if(vis[i])continue;
			vis[i]=true;
			dfs(to[i],cnt+1);
			vis[i]=false;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	const int n=ni,m=ni;
	G::init(n);
	for(int i=1;i<=m;i++){
		const int x=ni,a=ni,b=ni;
		G::ae(a,b,x);
	}
	G::vis[G::seq[0]=0]=true,G::dfs(G::to[0],1);
	printf("%lld\n",G::sum%O);
	return 0;
}
