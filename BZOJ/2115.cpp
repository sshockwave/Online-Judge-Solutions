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
const int N=50010,E=200010;
namespace LB{
	const int N=64;
	lint a[N];
	inline void init(){
		memset(a,0,sizeof(a));
	}
	inline bool add(lint x){
		for(int i=N-1;x;i--){
			if((x>>i)&1){
				if(a[i]){x^=a[i];}
				else{
					a[i]=x;
					return true;
				}
			}
		}
		return false;
	}
	inline lint ask(lint base){
		for(int i=N-1;i>=0;i--){
			apmax(base,base^a[i]);
		}
		return base;
	}
}
namespace G{
	bool vis[N];
	int to[E],bro[E],head[N],e=0;
	lint val[E],dis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
	}
	inline void ae(int u,int v,lint w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,lint w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs(int x){
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]]){LB::add(dis[x]^dis[v]^val[i]);}
			else{
				dis[v]=dis[x]^val[i];
				dfs(v);
			}
		}
	}
}
int main(){
	int n=ni;
	G::init(),LB::init();
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G::add(u,v,nl);
	}
	G::dfs(1);
	printf("%lld\n",LB::ask(G::dis[n]));
}