#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=500010;
struct Edge{
	int to,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
};
typedef vector<Edge>ve;
ve e[N];
int fr[N];
int bestx,bestp;
void dfs(int x){
	for(int i=0,ti=e[x].size();i<ti;i++){
		int v=e[x][i].to;
		if(v==fr[x])continue;
		if(fr[v]==x){
			dfs(v);
		}else{
			if(bestx==-1||e[x][i].w<e[bestx][bestp].w){
				bestx=x,bestp=i;
			}
			break;
		}
	}
}
void alt(int x,int p){
	if(fr[x]){
		alt(fr[x],x);
	}
	fr[x]=p;
}
int lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
#endif
	const int n=ni;
	for(int tot=ni;tot--;){
		const int u=ni,v=ni,c=ni;
		e[u].push_back((Edge){v,c});
		e[v].push_back((Edge){u,c});
	}
	for(int i=1;i<=n;i++){
		fr[i]=0;
		lst[i]=i;
		sort(e[i].begin(),e[i].end());
	}
	random_shuffle(lst+1,lst+n+1);
	lint ans=0;
	for(int i=1;i<=n;i++){
		bestx=-1,bestp=-1;
		dfs(i);
		if(bestx==-1){
			puts("No");
			return 0;
		}
		ans+=e[bestx][bestp].w;
		alt(bestx,e[bestx][bestp].to);
	}
	printf("%lld\n",ans);
	return 0;
}
