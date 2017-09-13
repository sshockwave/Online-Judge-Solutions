#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=1010,INF=0x7f7f7f7f;
namespace G{
	const int E=N*2;
	int to[E],bro[E],len[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],len[e]=w,head[u]=e++;
	}
	int dis[N],que[N],cnt[N];
	bool inque[N];
	inline int spfa(int s,int t,int n){
		memset(dis+1,127,n<<2);
		memset(cnt+1,0,n<<2);
		memset(inque+1,0,n);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s,inque[s]=true,cnt[s]++;
		while(qh!=qt){
			int x=que[qh++];
			if(cnt[x]>n){
				return -1;
			}
			if(qh==N){
				qh=0;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>dis[x]+len[i]){
					dis[v]=dis[x]+len[i];
					if(!inque[v]){
						que[qt++]=v,inque[v]=true,cnt[v]++;
						if(qt==N){
							qt=0;
						}
					}
				}
			}
			inque[x]=false;
		}
		return dis[t]==INF?-1:dis[t];
	}
}
int h[N],lst[N];
inline bool lcmp(int a,int b){
	return h[a]<h[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("monkey.in","r",stdin);
	freopen("monkey.out","w",stdout);
#endif
	int n,d;
	while(n=ni,d=ni,n||d){
		G::init(n);
		for(int i=1;i<=n;i++){
			h[i]=ni;
			lst[i]=i;
		}
		sort(lst+1,lst+n+1,lcmp);
		if(lst[1]>lst[n]){
			reverse(h+1,h+n+1);
			for(int i=1;i<=n;i++){
				lst[i]=n+1-lst[i];
			}
		}
		for(int i=1;i<n;i++){
			G::ae(i+1,i,-1);
			if(lst[i+1]>lst[i]){
				G::ae(lst[i],lst[i+1],d);
			}else{
				G::ae(lst[i+1],lst[i],d);
			}
		}
		printf("%d\n",G::spfa(lst[1],lst[n],n));
	}
	return 0;
}
