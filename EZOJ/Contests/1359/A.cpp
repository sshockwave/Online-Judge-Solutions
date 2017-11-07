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
const int N=1000010;
namespace G{
	const int E=3000010<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int dis[N];
	int disto[N<<1],disbro[N<<1],dishead[N<<1],de=0;
	inline void setdis(int x,int d){
		if(dis[x]>d){
			dis[x]=d;
			disto[de]=x,disbro[de]=dishead[d],dishead[d]=de++;
		}
	}
	inline int spath(int s,int t){
		memset(dis,127,sizeof(dis));
		memset(dishead,-1,sizeof(dishead));
		setdis(s,0);
		for(int d=0;;d++){
			for(int i=dishead[d];~i;i=disbro[i]){
				int x=disto[i];
				if(dis[x]==d){
					if(x==t){
						return d;
					}
					for(int j=head[x];~j;j=bro[j]){
						setdis(to[j],d+val[j]);
					}
				}
			}
		}
		assert(false);
		return -1;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("short.in","r",stdin);
	freopen("short.out","w",stdout);
#endif
	int n=ni,m=ni,t=ni;
	G::init();
	for(int tot=m,u,v;tot--;u=ni,v=ni,G::add(u,v,ni));
	printf("%d\n",G::spath(1,t));
	return 0;
}
