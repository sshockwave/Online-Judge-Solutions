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
const int N=100010,E=100010;
namespace G{
	int to[E],bro[E],val[E],head[N],e=1;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	int que[N],con[N];
	inline void spfa(){
		int qh=0,qt=0;
		que[qt++]=1;
		con[1]=-1;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(con[v=to[i]]==0){
					con[v]=i;
					que[qt++]=v;
				}else if(val[i]<val[con[v]]){
					con[v]=i;
				}
			}
		}
	}
}
bool okay[E];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n=ni;
	G::init();
	for(int tot=ni,u,v;tot--;u=ni,v=ni,G::ae(u,v,ni));
	G::spfa();
	int cnt=0;
	for(int i=2;i<=n;i++){
		if(G::con[i]==0){
			puts("-1");
			return 0;
		}
		if(G::val[G::con[i]]){
			cnt++;
			okay[G::con[i]]=true;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<G::e;i++){
		if(okay[i]){
			printf("%d ",i);
		}
	}
	putchar('\n');
	return 0;
}
