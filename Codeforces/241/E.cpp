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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=1010;
namespace G{
	const int E=5010*2;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v,-1),ae(v,u,2);
	}
	void mark(int x,bool vis[],bool flag){
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if((i&1)==flag&&!vis[v=to[i]]){
				mark(v,vis,flag);
			}
		}
	}
	bool mark1[N],mark2[N];
	int dis[N],qcnt[N],que[N],qh=0,qt=0;
	bool inque[N];
	inline void psh(int x,int d){
		if(mark1[x]&&mark2[x]&&dis[x]>d){
			dis[x]=d;
			if(!inque[x]){
				inque[x]=true;
				que[qt++]=x;
				if(qt==N){
					qt=0;
				}
			}
		}
	}
	inline void spfa(int s){
		memset(qcnt,0,sizeof(qcnt));
		memset(dis,127,sizeof(dis));
		psh(s,0);
		while(qh!=qt){
			int x=que[qh++];
			if(qh==N){
				qh=0;
			}
			if(++qcnt[x]>s+1){
				throw true;
			}
			inque[x]=false;
			for(int i=head[x];~i;i=bro[i]){
				psh(to[i],dis[x]+val[i]);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flight.in","r",stdin);
	freopen("flight.out","w",stdout);
#endif
	int n=ni;
	G::init();
	for(int tot=ni,u,v;tot--;u=ni,v=ni,G::add(u,v));
	G::mark(1,G::mark1,0);
	G::mark(n,G::mark2,1);
	try{
		G::spfa(n);
	}catch(bool fail){
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=0;i<G::e;i+=2){
		bool ok1=G::mark1[G::to[i]]&&G::mark1[G::to[i|1]];
		bool ok2=G::mark2[G::to[i]]&&G::mark2[G::to[i|1]];
		putchar((ok1&&ok2?G::dis[G::to[i|1]]-G::dis[G::to[i]]:1)+'0');
		putchar('\n');
	}
	return 0;
}
