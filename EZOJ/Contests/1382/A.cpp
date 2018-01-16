#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <limits>
#include <map>
#include <cstdlib>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
const int N=200010,O=1000000007;
inline ull grand(){
	const static int n=numeric_limits<ull>().max()/RAND_MAX;
	ull num=0;
	for(int i=0;i<n;i++){
		num=num*RAND_MAX+rand();
	}
	return num;
}
namespace G{
	const int E=200010*2;
	int to[E],bro[E],head[N],e=0;
	ull val[E];
	int dfn[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	ull dfs(int x,int e){
		dfn[x]=++tim;
		ull tmp=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(i==e)continue;
			if(dfn[v=to[i]]){
				if(dfn[v]<dfn[x]){
					tmp^=val[i]=val[i^1]=grand();
				}else{
					tmp^=val[i];
				}
			}else{
				tmp^=val[i]=val[i^1]=dfs(v,i^1);
			}
		}
		return tmp;
	}
}
map<ull,int>cnt;
int pw2[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("euler.in","r",stdin);
	freopen("euler.out","w",stdout);
#endif
	G::init();
	int n=ni,m=ni,c=0;
	pw2[0]=1;
	for(int i=1;i<=m;i++){
		G::add(ni,ni);
		pw2[i]=(pw2[i-1]<<1)%O;
	}
	for(int i=1;i<=n;i++){
		if(G::dfn[i]==0){
			c++;
			G::dfs(i,-1);
		}
	}
	lint ans=0;
	for(int i=0;i<G::e;i+=2){
		cnt[G::val[i]]++;
		ans+=pw2[(m-1)-n+c+(G::val[i]==0)];
	}
	ans=(O-ans%O)*m*2%O;
	int cnt0=cnt[0];
	for(int i=0;i<G::e;i+=2){
		using namespace G;
		if(val[i]){//not bridge
			//i & i
			ans+=pw2[(m-1)-n+c];
			//i & bridge
			ans+=(lint)pw2[(m-2)-n+c+1]*cnt0%O;
			//i & not bridge
			int cntv=cnt[val[i]];
			//cut
			ans+=(lint)pw2[(m-2)-n+c+1]*(cntv-1)%O;
			//remain
			ans+=(lint)pw2[(m-2)-n+c]*(m-cnt0-cntv)%O;
		}else{//is bridge
			//i & i
			ans+=pw2[(m-1)-n+c+1];
			//i & bridge
			ans+=(lint)pw2[(m-2)-n+c+2]*(cnt0-1)%O;
			//i & not bridge
			ans+=(lint)pw2[(m-2)-n+c+1]*(m-cnt0)%O;
		}
	}
	printf("%lld\n",(ans%O+(lint)pw2[m-n+c]*m%O*m%O)%O);
	return 0;
}
