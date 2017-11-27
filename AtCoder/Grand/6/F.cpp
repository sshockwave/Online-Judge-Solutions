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
const int N=100010;
namespace G{
	const int E=200010;
	int to[E],bro[E],head[N],e=0;
	int col[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(col,-1,sizeof(col));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int pcnt[3],ecnt;
	bool dfs(int x,int c){
		if(~col[x])return col[x]!=c;
		col[x]=c,pcnt[c]++;
		int nxt=(c+1)%3,pre=(c+2)%3;
		bool flag=false;
		for(int i=head[x],v;~i;i=bro[i]){
			ecnt++;
			flag|=dfs(v=to[i],i&1?pre:nxt);
		}
		return flag;
	}
}
int main(){
	G::init();
	int n=ni;
	for(int tot=ni;tot--;G::add(ni,ni));
	lint ans=0;
	for(int i=1;i<=n;i++){
		using namespace G;
		if(col[i]==-1){
			memset(pcnt,0,sizeof(pcnt));
			ecnt=0;
			if(dfs(i,0)){
				int sum=pcnt[0]+pcnt[1]+pcnt[2];
				ans+=(lint)sum*sum;
			}else if(pcnt[0]&&pcnt[1]&&pcnt[2]){
				ans+=(lint)pcnt[0]*pcnt[1]+(lint)pcnt[1]*pcnt[2]+(lint)pcnt[2]*pcnt[0];
			}else{
				ans+=ecnt>>1;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
