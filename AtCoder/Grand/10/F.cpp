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
const int N=3010;
int a[N],win[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int deg[N],que[N],qh=0,qt=0;
	inline void bfs(int n){
		memset(deg,0,sizeof(deg));
		for(int x=1;x<=n;x++){
			for(int i=head[x];~i;i=bro[i]){
				deg[x]+=a[to[i]]<a[x];
			}
			if(deg[x]==0){
				win[x]=-1,que[qt++]=x;
			}
		}
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(win[v=to[i]]==0){
					if(win[x]==1){
						if(a[x]<a[v]){
							deg[v]--;
						}
						if(deg[v]==0){
							win[v]=-1,que[qt++]=v;
						}
					}else if(a[x]<a[v]){
						win[v]=1,que[qt++]=v;
					}
				}
			}
		}
	}
}
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	memset(win,0,sizeof(win));
	T::bfs(n);
	for(int i=1;i<=n;i++){
		assert(win[i]);
		if(win[i]==1){
			printf("%d ",i);
		}
	}
	putchar('\n');
	return 0;
}
